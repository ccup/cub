#ifndef H02EFDCC6_D840_47A3_868E_91B34F0A1116
#define H02EFDCC6_D840_47A3_868E_91B34F0A1116

#if defined(__GNUC__)
#define __likely(expr)   __builtin_expect(!!(expr), 1)
#define __unlikely(expr) __builtin_expect(!!(expr), 0)
#else
#define __likely(expr)   !!(expr)
#define __unlikely(expr) !!(expr)
#endif


#endif /* H02EFDCC6_D840_47A3_868E_91B34F0A1116 */
