#ifndef __H_BANSHEE_STRING__
#define __H_BANSHEE_STRING__

#include <banshee/cdefs.h>

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

  size_t strlen(const char *str);

  int memcmp(const void *ptr1, const void *ptr2, size_t len);
  void *memcpy(void *dest, const void *src, size_t len);
  void *memset(void *ptr, int value, size_t len);
  void *memmove(void *dest, const void *src, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* __H_BANSHEE_STRING__ */
