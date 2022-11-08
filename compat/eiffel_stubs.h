#ifndef COMPAT_EIFFEL_STUBS_H
#define COMPAT_EIFFEL_STUBS_H

#ifdef WITH_NANA
#include "eiffel.h"
#else
#define REQUIRE(x)
#define ENSURE(x)
#endif

#endif
