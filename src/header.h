#ifndef DANCLER_HEADER_
#define DANCLER_HEADER_ 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

#ifdef PRODUCTION_
    #define DEBUG_ASSERT_(x) /* No runtime check */
    /* In case `static_assert` causes some symbol errors */
    #ifndef static_assert
        #define static_assert(x, msg)
    #endif
#else
    #include <assert.h>
    #define DEBUG_ASSERT_(x) assert(x)
#endif




#endif /* DANCLER_HEADER_ */
