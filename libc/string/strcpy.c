#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

char *
strcpy(char *dest, const char *src)
{
  size_t destlen = strlen(dest);
  size_t srclen = strlen(src);

  if(srclen == 0)
  {
    return dest;
  }

  size_t n = destlen == 0 ? srclen : MIN(destlen, srclen);

  for(size_t i = 0; i <= n; ++i)
  {
    dest[i] = *src++;
  }

  return dest;
}
