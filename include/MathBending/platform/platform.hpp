#pragma once

#ifndef SSE2_SET
    #if defined(__SSE2__) || \
        defined(_M_AMD64) || defined(_M_X64) || \
        (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
        #define SSE2_SET
        #define SSE_SET
    #endif
#endif

#ifndef SSE_SET
    #if defined(__SSE__)
        #define SSE_SET
    #endif
#endif

#ifndef AVX512_SET
    #if defined(__AVX512__)
        #define AVX512_SET
        #define AVX2_SET
    #endif
#endif

#ifndef AVX2_SET
#if defined(__AVX2__)
#define AVX2_SET
#endif
#endif


