#ifndef H38247538_297F_4A80_94D3_8A289788463C
#define H38247538_297F_4A80_94D3_8A289788463C

#include <cub/cub.h>
#include <stddef.h>

CUB_NS_BEGIN

struct MsgAllocator
{
    static void* alloc(size_t size);
    static void  free(void* p);
    static bool withIn(void* p);
};

CUB_NS_END

#endif

