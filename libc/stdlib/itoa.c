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
  int sign = (n < 0) ? -1 : 0;

  n = (n < 0) ? -n : n;

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

  for(int j = sign; i >= 0; --i, ++j)
  {
    if(j < 0)
    {
      j = 0;
      buffer[j] = '-';
      ++i;
    }
    else
    {
      buffer[j] = reverse[i];
      if(i == 0)
      {
        buffer[j + 1] = '\0';
      }
    }
  }

  return buffer;
}
