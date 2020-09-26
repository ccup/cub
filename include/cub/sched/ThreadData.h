#ifndef H38247538_297F_4A80_94D3_8A28246846EF
#define H38247538_297F_4A80_94D3_8A28246846EF

#include <cub/base/Assertions.h>
#include <cub/log/log.h>

CUB_NS_BEGIN

template<typename T> 
struct ConstThreadDataVisitor
{
    virtual Status visit(const T&) = 0;
    virtual ~ConstThreadDataVisitor(){}
};

///////////////////////////////////////////////////////////
template <typename T, typename THREAD_INFO>
struct ThreadData
{
    enum{ THREAD_NUM = THREAD_INFO::MAX_THREAD_NUM };

    T* operator->()
    {
        return const_cast<T*>(getPointer(THREAD_INFO::getCurrentId()));
    }

    const T* operator->() const
    {
        return getPointer(THREAD_INFO::getCurrentId());
    }

    T& operator*()
    {
        return getValue(THREAD_INFO::getCurrentId());
    }

    const T& operator*() const
    {
        return getValue(THREAD_INFO::getCurrentId());
    }

    T& operator[](unsigned int index)
    {
        return getValue(index);
    }

    const T& operator[](unsigned int index) const
    {
        return getValue(index);
    }

    Status visitAllThreadElems(ConstThreadDataVisitor<T>& visitor)
    {
        for(unsigned int index = 0; index < THREAD_NUM; index++)
        {
            CUB_ASSERT_SUCC_CALL(visitor.visit(t[index]));
        }
        return CUB_SUCCESS;
    }

private:
    const T* getPointer(unsigned int id) const
    {
        if(id < THREAD_NUM)
        {
            return &getValue(id);
        }
        
        DBG_LOG("ThreadData: id(%d) overflow!", id);
        return 0;
    }

    const T& getValue(unsigned int id) const
    {
        return t[id];
    }

    T& getValue(unsigned int id)
    {
        return t[id];
    }
private:
    T  t[THREAD_NUM];
};

CUB_NS_END

#endif

