#include <math.h>
#include <stdlib.h>
#include <string.h>

char *
dtoa(double f, char *buffer, int after)
{
  char int_part[50];
  uint64_t n = (uint64_t)f;
  itoa((int)n, int_part, 10);

  strcpy(buffer, int_part);

  if(after > 0)
  {
    char double_part[50];
    double_part[0] = '.';
    uint64_t pow = 1;
    for(; after > 0; pow *= 10, --after)
      ;
    uint64_t f1 = ((uint64_t)(f * pow)) - (n * pow);
    utoa((int)f1, double_part + 1, 10);
    strcat(buffer, double_part);
  }

  return buffer;
}
