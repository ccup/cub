#ifndef HE04F56DE_D19F_49AA_AB12_B892970271AD
#define HE04F56DE_D19F_49AA_AB12_B892970271AD

#include "cub/cub.h"
#include <type_traits>

CUB_NS_BEGIN

template<typename E>
constexpr auto enum_underlying_cast(E e) noexcept {
	return static_cast<std::underlying_type_t<E>>(e);
}

CUB_NS_END

#endif
