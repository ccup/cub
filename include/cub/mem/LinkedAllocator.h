#ifndef H05B2224D_B026_4FC1_A936_97B52B8A99DB
#define H05B2224D_B026_4FC1_A936_97B52B8A99DB

#include <cub/repo/list/List.h>
#include <cub/repo/list/ListElem.h>
#include <cub/base/BaseTypes.h>
#include <cub/base/Assertions.h>
#include <cub/algo/max_min.h>

CUB_NS_BEGIN

template<typename T> 
struct AllocatorVisitor
{
    virtual Status visit(T&) = 0;
    virtual ~AllocatorVisitor(){}
};

template<typename T> 
struct ConstAllocatorVisitor
{
    virtual Status visit(const T&)= 0;
    virtual ~ConstAllocatorVisitor(){}
};

//////////////////////////////////////////////////////////////////////////

struct LinkNode : ListElem<LinkNode>
{
    LinkNode() : isUsed(false) {}
    bool isUsed;
};

template<typename T, U16 MAX_SIZE>
struct LinkedAllocator
{
    LinkedAllocator(T* elements, const U16 size)
        :elements(elements), maxSize(__MIN(size, MAX_SIZE))
    {
        for(U16 loop = 0; loop < maxSize; loop++)
        {
            freeList.pushBack(linkNodes[loop]);
        }
    }

    T* alloc()
    {
        if(isFreeListEmpty())    return __null_ptr;

        LinkNode* freeNode = freeList.popFront();
        busyList.pushBack(*freeNode);
        freeNode->isUsed = true;

        return &elements[freeNode - &linkNodes[0]];
    }

    Status dealloc(const T& elem)
    {
        U16 index = (U16)(&elem - elements);

        CUB_ASSERT_TRUE(index <  maxSize);

        if(!linkNodes[index].isUsed)
        {
            return CUB_FAILURE;
        }

        busyList.remove(linkNodes[index]);
        freeList.pushBack(linkNodes[index]);
        linkNodes[index].isUsed = false;      
        
        return CUB_SUCCESS;
    }

    bool isBusyListEmpty() const
    {
        return busyList.isEmpty();
    }

    bool isFreeListEmpty() const
    {
    	return freeList.isEmpty();
    }

    Status visitAllBusyElems(AllocatorVisitor<T>& visitor)
    {
        return access(visitor);
    }

    Status visitAllBusyElems(ConstAllocatorVisitor<T>& visitor) const
    {
        return const_cast<LinkedAllocator&>(*this).access(visitor);
    }

private:
    template<typename VISITOR> 
    Status access(VISITOR& visitor)
    {
        LIST_FOREACH(LinkNode, node, busyList)
        {
            CUB_ASSERT_SUCC_CALL(visitor.visit(elements[&(*node) - &linkNodes[0]]));
        }
        return CUB_SUCCESS;
    }

private:
    List<LinkNode>  freeList;
    List<LinkNode>  busyList;

    LinkNode linkNodes[MAX_SIZE];
    T*    elements; 
    const U16 maxSize;
};

CUB_NS_END

#endif

