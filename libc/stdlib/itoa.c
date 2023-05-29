#include <stdlib.h>
#include <string.h>

char *
itoa(int n, char *buffer, int radix)
{
  if(radix < 2)
  {
    return NULL;
  }

  char reverse[50];

  for(size_t i = 0; i < 50; ++i)
  {
    reverse[i] = '0' + (n % radix);
    n /= radix;
    if(n == 0)
    {
      reverse[i + 1] = '\0';
      break;
    }
  }

  int i = strlen(reverse) - 1;
  size_t j = 0;
  for(; i >= 0; --i, ++j)
  {
    buffer[j] = reverse[i];
    if(i == 0)
    {
      buffer[j + 1] = '\0';
    }
  }

  return buffer;
}
