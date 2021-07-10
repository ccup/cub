#ifndef H162D1982_C2EF_4CE0_B155_7BEE076DA3C5
#define H162D1982_C2EF_4CE0_B155_7BEE076DA3C5

#include "cub/cub.h"
#include <string>

CUB_NS_BEGIN

namespace detail {
	template<std::size_t Len>
	constexpr const char* baseNameImpl(const char(&str)[Len], std::size_t pos)
	{
		return pos==0 ? str : (str[pos] == '/' || str[pos] == '\\') ? str+pos+1 : baseNameImpl(str, --pos);
	}
}

template<std::size_t Len>
constexpr const char* base_name_of(const char(&str)[Len])
{
    return detail::baseNameImpl(str, Len-1);
}

CUB_NS_END

#endif
