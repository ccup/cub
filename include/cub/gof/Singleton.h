#ifndef H671141B2_B247_440B_8E83_476558110FFF
#define H671141B2_B247_440B_8E83_476558110FFF

#include <cub/cub.h>
#include <cub/base/Uncloneable.h>

CUB_NS_BEGIN

// template<typename T>
// struct Singleton
// {
//     static T& getInstance()
//     {
//         static T instance;
//         return instance;
//     }

//     DISALLOW_COPY_AND_ASSIGN(Singleton)

// protected:
//     Singleton() {}
// };

template<typename T>
struct Singleton{
    static T& getInstance() noexcept(std::is_nothrow_constructible<T>::value)
    {
        static T instance{token()};
        return instance;
    }

    virtual ~Singleton() =default;
    DISALLOW_COPY_AND_ASSIGN(Singleton);

protected:
    struct token{};
    Singleton() noexcept=default;
};

#define DEF_SINGLETON(object) struct object : ::CUB_NS::Singleton<object>

#define IMPL_SINGLETON(object)              \
object(token){};                            \
DISALLOW_COPY_AND_ASSIGN(object)

CUB_NS_END

#endif

