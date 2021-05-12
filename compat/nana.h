/* This is a re-implemenation of the small subset of the Nana library that I use */

#ifndef COMPAT_NANA_H
#define COMPAT_NANA_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG
#define I(PRED) \
{ \
    if (!(PRED)) { \
        fprintf(stderr, "assertion \"%s\" failed: file \"%s\", line %d, function \"%s\"\n", # PRED, __FILE__, __LINE__, __FUNCTION__); \
        abort(); \
    } \
}
#else
#define I assert
#endif

#define IP(PRED, MSG) \
{ \
    if (!(PRED)) { \
        fputs((MSG), stderr); \
        fputc('\n', stderr); \
        I(PRED); \
    } \
}

#define VL printf

#define VLG(PRED, ...) \
{ \
    if (PRED) { \
        VL(__VA_ARGS__); \
    } \
}

#endif
