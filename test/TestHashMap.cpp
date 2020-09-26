#include <cctest/cctest.h>
#include <cub/repo/map/HashMap.h>
#include <cub/base/Keywords.h>
#include <string>

USING_CUB_NS

namespace
{
	struct MultipleValueMapVisitor : MapVisitor<int, int>
	{
		MultipleValueMapVisitor(int times) : times(times)
		{
		}

	private:
		OVERRIDE(Status visit(const int& key, int& value))
		{
			value = times * key;
			return CUB_SUCCESS;
		}

	private:
		const int times;
	}multipleVisitor(3);

    struct PrintMapVisitor : ConstMapVisitor<int, const char*>
    {
        std::string result;

    private:
        OVERRIDE(Status visit(const int& key, const char* const& value))
        {
            std::stringstream ss;
            ss << "map[" << key <<"] = " << value << " \n";
            result += ss.str();
            return CUB_SUCCESS;
        }
    }printVisitor;

    struct Key
    {
        Key(int x, int y)
        : x(x), y(y)
        {
        }

        size_t hash() const
        {
            return (x + y);
        }

        __INLINE_EQUALS(Key)
        {
            return (x == rhs.x) && (y == rhs.y);
        }

    private:
        int x;
        int y;
    };

    struct Value
    {
        Value() : value(__null_ptr){}
        Value(const char* v) : value(v)
        {
        }

        const char* getValue() const
        {
            return value;
        }

        bool operator==(const Value& rhs) const
        {
            return strcmp(value, rhs.value) == 0;
        }

    private:
        const char* value;
    };
}

namespace cub
{
    template<size_t HASH_SIZE>
    struct HashFn<Key, HASH_SIZE>
    {
        size_t operator()(const Key& key) const
        {
            return key.hash();
        }
    };
}

FIXTURE(HashMapTest)
{

	TEST("should be empty when init")
	{
		HashMap<int, int> map;

		ASSERT_TRUE(map.empty());
		ASSERT_FALSE(map.full());
		ASSERT_EQ(0, map.size());
	}

	TEST("should get the value from key when inserted success")
	{
		HashMap<int, int> map;

		map.put(1, 2);
		map[2] = 4;

		ASSERT_FALSE(map.empty());
		ASSERT_FALSE(map.full());
		ASSERT_EQ(2, map.size());
		ASSERT_EQ(2, map[1]);
	}

	TEST("should erase the map correctly when only on node in map")
	{
		HashMap<int, int> map;

		map.put(1, 2);

		map.erase(1);

		ASSERT_TRUE(map.empty());
		ASSERT_EQ(0, map.size());
		ASSERT_EQ(nullptr, map.get(1));
	}

	TEST("should erase the map correctly when muti node in map")
	{
		HashMap<int, int> map;

		map.put(1, 2);
		map.put(2, 4);

		map.erase(2);

		ASSERT_FALSE(map.empty());
		ASSERT_EQ(1, map.size());
		ASSERT_EQ(2, *map.get(1));
		ASSERT_EQ(nullptr, map.get(2));
	}

	TEST("should clear the map correctly")
	{
		HashMap<int, int> map;

		map.put(1, 2);
		map.put(2, 4);

		map.clear();

		ASSERT_TRUE(map.empty());
		ASSERT_EQ(0, map.size());
		ASSERT_EQ(nullptr, map.get(1));
	}

	TEST("should not change the value when same key already in")
	{
		HashMap<int, int> map;

		map.put(1, 2);
		map.put(1, 4);

		ASSERT_EQ(1, map.size());
		ASSERT_EQ(4, map[1]);
	}

	TEST("should be full when reach the max node num")
	{
		HashMap<int, int, 1> map;

		ASSERT_FALSE(__CUB_FAILED(map.put(1, 2)));

		ASSERT_TRUE(map.full());
	}

	TEST("should put fail when map is full")
	{
		HashMap<int, int, 1> map;

		map.put(1, 2);
		ASSERT_TRUE(__CUB_FAILED(map.put(2, 2)));

		ASSERT_EQ(1, map.size());
		ASSERT_EQ(2, map[1]);
	}

	TEST("should put already in success when map is full")
	{
		HashMap<int, int, 1> map;

		map.put(1, 2);
		ASSERT_FALSE(__CUB_FAILED(map.put(1, 4)));

		ASSERT_EQ(1, map.size());
		ASSERT_EQ(4, map[1]);
	}

	TEST("should point to correct node by iterator when map is empty")
	{
		HashMap<int, int> map;

		ASSERT_TRUE(map.begin().isNull());
		ASSERT_TRUE(map.end().isNull());
	}

	TEST("should point to correct node by iterator when map has valid elem")
	{
		HashMap<int, int> map;

		map.put(1, 2);

		ASSERT_FALSE(map.begin().isNull());
		ASSERT_EQ(1, map.begin()->key);
		ASSERT_EQ(2, map.begin()->value);
		ASSERT_TRUE(map.end().isNull());
	}

	TEST("should point to correct node when iterator forward")
	{
		typedef HashMap<int, int> ThisMap;
		ThisMap map;

		map.put(1, 2);
		map.put(3, 6);

		ThisMap::Iterator p(map.begin());
		ASSERT_EQ(map.begin(), p++);
		ASSERT_EQ(3, p.getValue()->key);
		ASSERT_EQ(6, p.getValue()->value);
		ASSERT_EQ(map.end(), ++p);
	}

	TEST("should travel the map by iterator")
	{
		typedef HashMap<int, int, 5, 5> ThisMap;
		ThisMap map;

		map.put(1, 2);
		map.put(3, 6);
		map.put(8, 16);
		map.put(5, 10);

		int keySum = 0;
		int valueSum = 0;

		MAP_FOREACH(ThisMap, i, map)
		{
			keySum += i->key;
			valueSum += i->value;
		}

		ASSERT_EQ(1 + 3 + 8 + 5, keySum);
		ASSERT_EQ(2 + 6 + 16 + 10, valueSum);
	}

	TEST("should put and get when hash string")
	{
		HashMap<const char*, int> map;

		map["hello"] = 5;
		map["ni hao ma"] = 9;

		ASSERT_EQ(2, map.size());
		ASSERT_EQ(5, map["hello"]);
		ASSERT_EQ(9, map["ni hao ma"]);
	}

	TEST("shoud double all value through visitor")
	{
		HashMap<int, int> map;

		map[1] = 1;
		map[2] = 2;

		map.visit(multipleVisitor);

		ASSERT_EQ(3, map[1]);
		ASSERT_EQ(6, map[2]);
	}

	TEST("should dump map through const visitor")
	{
		HashMap<int, const char*> map;

		map[1] = "one";
		map[2] = "two";
		map[3] = "three";

		map.visit(printVisitor);

		ASSERT_EQ(std::string("map[1] = one \nmap[2] = two \nmap[3] = three \n"), printVisitor.result);
	}

	TEST("should work with user defined hash and equal function")
	{
		HashMap<Key, Value> map;

		map.put(Key(1, 3), Value("four"));
		map[Key(2, 3)] = Value("five");

		ASSERT_EQ(Value("four"), map[Key(1, 3)]);
		ASSERT_EQ(Value("five"), *map.get(Key(2, 3)));
		ASSERT_EQ(nullptr, map.get(Key(2, 4)));
	}

	TEST("should store the pointer to value")
	{
		Value v1("one");
		Value v2("two");

		HashMap<Key, Value*> map;

		map.put(Key(0, 1), &v1);
		map[Key(1, 1)] = &v2;

		ASSERT_EQ(&v1, map[Key(0, 1)]);
		ASSERT_EQ(&v2, *map.get(Key(1, 1)));
		ASSERT_EQ(nullptr, map.get(Key(2, 4)));
	}

};




