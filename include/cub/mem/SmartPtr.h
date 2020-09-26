#ifndef H38247538_297F_4A80_94D3_8A28978E46FA
#define H38247538_297F_4A80_94D3_8A28978E46FA

#include <cub/dci/Role.h>
#include <cub/mem/SharedObject.h>

CUB_NS_BEGIN

template <typename OBJ>
struct SmartPtr
{
    SmartPtr() : p(0) {}
    SmartPtr(const OBJ* p) : p(const_cast<OBJ*>(p)) 
    {
        addRef();
    }

    SmartPtr(const SmartPtr& rhs) 
        : p(rhs.p)
    {
        addRef();
    }

    SmartPtr& operator=(const SmartPtr& rhs) 
    {
        release();

        p = rhs.p;
        addRef();

        return *this;
    }

    ~SmartPtr()
    {
        release();
    }

    bool operator==(const SmartPtr& rhs) const
    {
        return rhs.p == p;
    }

    bool operator!=(const SmartPtr& rhs) const
    {
        return !(*this == rhs);
    }

    OBJ* operator->()
    {
        return p;
    }

    const OBJ* operator->() const
    {
        return p;
    }

    bool isNull() const
    {
        return p == 0;
    }

    OBJ* raw() 
    {
        return p;
    }

    const OBJ* raw() const
    {
        return p;
    }

    OBJ& operator*()
    {
        return *p;
    }

    const OBJ& operator*() const
    {
        return *p;
    }

    void release()
    {
        if(p != 0)
        {
            p->ROLE(SharedObject).subRef();
            p = 0;
        }
    }

private:
    void addRef()
    {
        if(p != 0)
        {
            p->ROLE(SharedObject).addRef();
        }
    }

private:
    OBJ* p;
};

CUB_NS_END

#endif
