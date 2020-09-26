#include <cctest/cctest.h>
#include <cub/base/Keywords.h>

namespace
{
    DEF_INTERFACE(Shape)
    {
        ABSTRACT(bool isCentrosymmetry() const);
    };

    struct Circle : Shape
    {
    private:
        OVERRIDE(bool isCentrosymmetry() const)
        {
            return true;
        }
    };

    DEF_INTERFACE(Shape2D) EXTENDS(Shape)
    {
        DEFAULT(int, getArea() const);
    };

    struct Rectangle : Shape2D
    {
        Rectangle(int w, int h) : width(w), height(h)
        {
        }

    private:
        OVERRIDE(bool isCentrosymmetry() const)
        {
            return false;
        }

        OVERRIDE(int getArea() const)
        {
            return width * height;
        }

    private:
        int width;
        int height;
    };

    struct Square : Shape2D
    {
        Square(int l) : length(l)
        {
        }

    private:
        OVERRIDE(bool isCentrosymmetry() const)
        {
            return true;
        }

        OVERRIDE(int getArea() const)
        {
            return length * length;
        }

    private:
        int length;
    };

    struct Triangle : Shape2D
    {
    private:
        OVERRIDE(bool isCentrosymmetry() const)
        {
            return false;
        }
    };
}

FIXTURE(KeywordsTest)
{
	TEST("should override the correct interface when inherit the interface")
	{
	    Shape2D *square = new Square(5);
	    Shape2D *rectangle = new Rectangle(2, 3);
	    Shape2D *triangle = new Triangle();

	    ASSERT_EQ(25, square->getArea());
	    ASSERT_EQ(6, rectangle->getArea());
	    ASSERT_EQ(0, triangle->getArea());

	    Shape *r = rectangle;
	    Shape *c = new Circle();

	    ASSERT_FALSE(r->isCentrosymmetry());
	    ASSERT_TRUE(c->isCentrosymmetry());

	    delete r;
	    delete c;
	    delete square;
	    delete triangle;
	}
};

