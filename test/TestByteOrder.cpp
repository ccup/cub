#include <cctest/cctest.h>
#include <cub/network/ByteOrder.h>

USING_CUB_NS

FIXTURE(ByteOrder)
{
   TEST("network order of S8 should be equal to the original one")
   {
      S8 v = -2;

      ASSERT_EQ(v, hton(v));
   }

   TEST("network order of U8 should be equal to the original one")
   {
      U8 v = 2;

      ASSERT_EQ(v, hton(v));
   }

   TEST("network order of S16 should be equal to network order")
   {
      S16 v = -274;

      ASSERT_EQ(v, (S16)ntohs(hton(v)));
   }

   TEST("network order of U16 should be equal to network order")
   {
      U16 v = 274;

      ASSERT_EQ(v, ntohs(hton(v)));
   }

   TEST("network order of S32 should be equal to network order")
   {
      S32 v = -274932234;

      ASSERT_EQ(v, ntohl(hton(v)));
   }

   TEST("network order of U32 should be equal to network order")
   {
      U32 v = 274343432;

      ASSERT_EQ(v, ntohl(hton(v)));
   }
};
