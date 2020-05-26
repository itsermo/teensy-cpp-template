#ifndef IMXRT1062_MEMORY
#define IMXRT1062_MEMORY
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// These functions come from memset.S and memcpy-armv7m.S
// They are "fast" assembly implementations of memset and memcpy
void *memset(void *s, int c, size_t n);
void *memcpy(void *dst, const void *src, size_t count);

#ifdef __cplusplus
}
#endif

#endif