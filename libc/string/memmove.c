#include <string.h>

void *
memmove(void *dest, const void *src, size_t num)
{
  unsigned char *cdest = (unsigned char *)dest;
  const unsigned char *csrc = (const unsigned char *)src;

  for(size_t i = 0; i < num; ++i)
  {
    *cdest++ = *csrc++;
  }

  return dest;
}
