#ifndef H38247538_297F_4A80_94D3_8A289788464D
#define H38247538_297F_4A80_94D3_8A289788464D

#include <cub/base/Assertions.h>

#include <new>
#include <string.h>

CUB_NS_BEGIN

template<typename MSG_ALLOCATOR>
struct MsgNewOperator
{
    void* operator new(size_t size) throw()
    {
        void* p = MSG_ALLOCATOR::alloc(size);
        CUB_ASSERT_VALID_PTR_NIL(p);

#ifdef PERFORMANCE_OPTIMIZE
        ::memset(p, 0, size);
#endif
        return p;
    }

    void operator delete(void* p)
    {
        MSG_ALLOCATOR::free(p);
    }

    virtual ~MsgNewOperator() {}
};

CUB_NS_END

#endif

