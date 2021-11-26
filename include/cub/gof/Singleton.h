#ifndef H671141B2_B247_440B_8E83_476558110FFF
#define H671141B2_B247_440B_8E83_476558110FFF

#include <cub/cub.h>
#include <cub/base/Uncloneable.h>
#include <type_traits>

CUB_NS_BEGIN

template<typename T>
struct Singleton{
    static T& getInstance() noexcept(std::is_nothrow_constructible<T>::value)
    {
        static T instance{token()};
        return instance;
    }

    virtual ~Singleton() =default;
    DISALLOW_COPY_AND_ASSIGN(Singleton);

protected:
    struct token{};
    Singleton() noexcept=default;
};

#define DEF_SINGLETON(ClassName) struct ClassName : ::CUB_NS::Singleton<ClassName>

#define IMPL_SINGLETON(ClassName)              \
ClassName(token){};                            \
DISALLOW_COPY_AND_ASSIGN(ClassName)

CUB_NS_END

#endif

