#include <cctest/cctest.h>
#include <cub/mem/ScopeExit.h>

FIXTURE(ScopeExitTest)
{
    TEST("should_execute_the_code_when_exit_scope")
    {
        bool scopeExited = false;

        {
            SCOPE_EXIT([&scopeExited](){ scopeExited = true; });
        }

        ASSERT_TRUE(scopeExited);
    }
};
