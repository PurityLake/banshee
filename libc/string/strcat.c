#include <string.h>

char *
strcat(char *dest, const char *src)
{
  size_t destlen = strlen(dest);
  size_t srclen = strlen(src);
  size_t newlen = destlen - 1 + srclen;

  size_t srcidx = 0;
  for(size_t i = destlen; i <= newlen; ++i)
  {
    dest[i] = src[srcidx++];
  }

  return dest;
}
