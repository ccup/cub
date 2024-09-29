#ifndef H05B2224D_B926_4FC0_A123_97B52B8A99DB
#define H05B2224D_B926_4FC0_A123_97B52B8A99DB

#include <cub/cub.h>
#include <string.h>
#include <new>

CUB_NS_BEGIN

template <typename T>
struct Placement
{
    Placement& operator=(const T& rhs)
    {
        assignBy(rhs);
        return *this;
    }

    void* alloc()
    {
        return (void*)&mem;
    }

    void free()
    {
       getObject()->~T();
    }

    T* operator->() const
    {
        return getObject();
    }

    T& operator*() const
    {
        return getRef();
    }

    T* getObject() const
    {
        return (T*)&mem;
    }

    T& getRef() const
    {
        return (T&)mem;
    }

    void destroy()
    {
        getObject()->~T();
    }

private:
    void assignBy(const T& rhs)
    {
        T* p = (T*)alloc();
        *p = rhs;
    }

private:
    std::aligned_storage_t<sizeof(T), alignof(T)> mem;
};

template <typename T>
struct DefaultPlacement : Placement<T>
{
    T* init()
    {
        return new(Placement<T>::alloc()) T();
    }
};

CUB_NS_END

#endif
