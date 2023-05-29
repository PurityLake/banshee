#include <stdlib.h>
#include <string.h>

char *
utoa(unsigned int n, char *buffer, int radix)
{
  if(radix < 2)
  {
    return NULL;
  }

  char reverse[50];

  int i;
  for(i = 0; i < 50; ++i)
  {
    size_t val = n % radix;
    if(val > 9)
    {
      reverse[i] = 'A' + (val - 10);
    }
    else
    {
      reverse[i] = '0' + val;
    }
    n /= radix;
    if(n == 0)
    {
      reverse[i + 1] = '\0';
      break;
    }
  }

  for(size_t j = 0; i >= 0; --i, ++j)
  {
    buffer[j] = reverse[i];
    if(i == 0)
    {
      buffer[j + 1] = '\0';
    }
  }

  return buffer;
}
