#ifndef H5712E60C_DEFF_4A3B_93C0_C074CD80C63B
#define H5712E60C_DEFF_4A3B_93C0_C074CD80C63B

#include <cub/cub.h>
#include <stddef.h>
#include <string.h>

CUB_NS_BEGIN

template <typename T, size_t MAXSIZE>
struct FixSizeArray
{
    FixSizeArray(size_t size = MAXSIZE)
        : actualSize(size < MAXSIZE? size : MAXSIZE)
    {
    }

    void reset()
    {
         memset(object, 0, sizeof(object));
    }

    const size_t capacity() const
    {
        return actualSize;
    }

    const T& operator[](size_t index) const
    {
        return object[index];
    }

    T& operator[](size_t index)
    {
        return object[index];
    }

private:
    size_t actualSize;
    T object[MAXSIZE];
};

CUB_NS_END

#endif

