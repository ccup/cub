#ifndef H5E28F16B_BEA7_4E11_84A7_03E3D4C29B6B
#define H5E28F16B_BEA7_4E11_84A7_03E3D4C29B6B

#include <cub/cub.h>

CUB_NS_BEGIN

template <typename T>
struct TypeIdGenerator {
  constexpr static char ID = 0;
};

template <typename T>
constexpr char TypeIdGenerator<T>::ID;

using TypeId = const void*;

template <typename T>
constexpr inline TypeId TypeIdOf() {
    return &TypeIdGenerator<T>::ID;
}

CUB_NS_END

#endif
