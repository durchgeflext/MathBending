#pragma once

#ifndef SSE2_SET
#if defined(__SSE2__) || \
    defined(_M_AMD64) || defined(_M_X64) || \
    (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
#define SSE2_SET
#endif
#endif

