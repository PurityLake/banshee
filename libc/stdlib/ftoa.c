#include <stdlib.h>
#include <string.h>

char *
ftoa(float f, char *buffer, int after)
{
  char int_part[50];
  int32_t n = (int32_t)f;
  itoa(n, int_part, 10);

  strcpy(buffer, int_part);

  if(after > 0)
  {
    char float_part[50];
    float_part[0] = '.';
    uint32_t pow = 1;
    for(; after > 0; pow *= 10, --after)
      ;
    uint32_t f1 = ((uint32_t)(f * pow)) - (n * pow);
    utoa(f1, float_part + 1, 10);

    strcat(buffer, float_part);
  }

  return buffer;
}
