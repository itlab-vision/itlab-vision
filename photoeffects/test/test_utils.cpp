#include "test_utils.hpp"

int suppressAssertionMessage(int, const char *, const char *,
                            const char *, int, void *)
{
    return 0;
}
