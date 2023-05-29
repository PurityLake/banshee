#include <string.h>

void *
memset(void *ptr, int value, size_t num)
{
  unsigned char *cptr = (unsigned char *)ptr;

  for(size_t i = 0; i < num; ++i)
  {
    *cptr++ = value;
  }

  return ptr;
}
