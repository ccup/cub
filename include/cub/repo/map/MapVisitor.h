#ifndef H0CBC1D58_7346_4F4B_B281_358825C0504E
#define H0CBC1D58_7346_4F4B_B281_358825C0504E

#include <cub/base/Status.h>

CUB_NS_BEGIN

template <typename K, typename V>
struct MapVisitor
{
    virtual Status visit(const K&, V&) = 0;
    virtual ~MapVisitor(){}

};

template <typename K, typename V>
struct ConstMapVisitor
{
    virtual Status visit(const K&, const V&) = 0;
    virtual ~ConstMapVisitor(){}
};

CUB_NS_END

#endif
