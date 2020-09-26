#ifndef H05B2224D_B926_4FC0_A936_97B52B8A98DB
#define H05B2224D_B926_4FC0_A936_97B52B8A98DB

#include <cub/cub.h>
#include <cub/base/Default.h>
#include <cub/base/Config.h>

CUB_NS_BEGIN

namespace details
{
   template<typename T>
   struct Interface
   {
      virtual ~Interface() {}
   };
}

#define DEF_INTERFACE(Intf)  struct Intf : ::CUB_NS::details::Interface<Intf>

#define ABSTRACT(...) virtual __VA_ARGS__ = 0

#define OVERRIDE(...) virtual __VA_ARGS__ override

#define EXTENDS(...) , ##__VA_ARGS__
#define IMPLEMENTS(...) EXTENDS(__VA_ARGS__)

CUB_NS_END

#endif

