#ifndef HAC57EDDB_4C76_4370_876A_05C7A7318E09
#define HAC57EDDB_4C76_4370_876A_05C7A7318E09

#include <cub/cub.h>
#include <cub/utils/Symbol.h>

CUB_NS_BEGIN

template <typename F>
struct ScopeExit
{
    ScopeExit(F f) : f(f)
    {}

    ~ScopeExit()
    { f(); }

private:
    F f;
};

template <typename F>
ScopeExit<F> make_scope_exit(F f)
{
    return ScopeExit<F>(f);
};

#define SCOPE_EXIT(code) \
    auto UNIQUE_NAME(scope_exit_) = CUB_NS::make_scope_exit(code)

CUB_NS_END

#endif
