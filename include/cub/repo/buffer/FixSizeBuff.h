#ifndef H5712E6CD_DEFF_4A3B_93C0_C074CD80C63B
#define H5712E6CD_DEFF_4A3B_93C0_C074CD80C63B

#include <cub/cub.h>
#include <memory.h>

CUB_NS_BEGIN

template <size_t SIZE>
struct FixSizeBuff
{
    FixSizeBuff()
    {
    }

    explicit FixSizeBuff(const U8* buf)
    {
        memcpy(buff, buf, SIZE);
    }

    FixSizeBuff(const FixSizeBuff& rhs)
    {
        memcpy(buff, rhs.buff, SIZE);
    }

    FixSizeBuff& operator=(const FixSizeBuff& rhs)
    {
        memcpy(buff, rhs.buff, SIZE);
        return *this;
    }

    bool operator==(const FixSizeBuff& rhs) const
    {
        return memcmp(buff, rhs.buff, SIZE) == 0;
    }

    bool operator!=(const FixSizeBuff& rhs) const
    {
        return !(*this == rhs);
    }

    size_t size() const
    {
        return SIZE;
    }

    operator const U8*() const
    {
        return buff;
    }

    operator U8*()
    {
        return buff;
    }

    void update(const U8* buf)
    {
        memcpy(buff, buf, SIZE);
    }

    void copyTo(U8* buffDes) const
    {
        ::memcpy(buffDes, buff, SIZE);
    }

    const U8* getContent() const
    {
        return buff;
    }

    U8* getBuffer() const
    {
        return (U8*)buff;
    }

    bool matches(U8* content) const
    {
        return ::memcmp(content, buff, SIZE) == 0;
    }

protected:
    U8 buff[SIZE];
};

CUB_NS_END

#endif

