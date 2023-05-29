#include <string.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

void *
memcpy(void *dest, const void *src, size_t len)
{
  if((uintptr_t)dest % sizeof(long) == 0 && (uintptr_t)src % sizeof(long) == 0
     && len % sizeof(long))
  {
    long *ldest = (long *)dest;
    const long *lsrc = (const long *)src;

    for(size_t i = 0; i < len / sizeof(long); ++i)
    {
      *ldest++ = *lsrc++;
    }
  }
  else
  {
    char *cdest = (char *)dest;
    const char *csrc = (const char *)src;

    for(size_t i = 0; i < len; ++i)
    {
      *cdest++ = *csrc++;
    }
  }

  return dest;
}
