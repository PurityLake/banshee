#include <string.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

void *
memcpy(void *dest, const void *src, size_t num)
{
  unsigned char *cdest = (unsigned char *)dest;
  const unsigned char *csrc = (const unsigned char *)src;

  for(size_t i = 0; i < num; ++i)
  {
    *cdest++ = *csrc++;
  }

  return dest;
}
