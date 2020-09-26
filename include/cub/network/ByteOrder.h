#ifndef H38247538_297F_4A80_94D3_8B289888462A
#define H38247538_297F_4A80_94D3_8B289888462A

#include <cub/cub.h>
#include <cub/base/BaseTypes.h>
#include <arpa/inet.h>

CUB_NS_BEGIN

inline U8  hton(U8  v) { return v;         }
inline U16 hton(U16 v) { return htons(v);  }
inline U32 hton(U32 v) { return htonl(v);  }

inline S8  hton(S8  v) { return v;         }
inline S16 hton(S16 v) { return htons(v);  }
inline S32 hton(S32 v) { return htonl(v);  }

CUB_NS_END

#endif //CUB_BYTEORDER_H_H
