#ifndef H38247538_297F_4A80_94D3_8A28978846EF
#define H38247538_297F_4A80_94D3_8A28978846EF

#include <cub/cub.h>
#include <cub/base/StaticAssert.h>

CUB_NS_BEGIN

template <typename FROM, typename TO>
struct StructWrapper : FROM
{
	static const TO& by(const FROM& from)
	{
	    STATIC_ASSERT(sizeof(FROM) == sizeof(TO));

	    return (const TO&)from;
	}

	static TO& by(FROM& from)
	{
		return (TO&)from;
	}
};

#define STRUCT_WRAPPER(to, from) struct to : StructWrapper<from, to>

CUB_NS_END

#endif 
