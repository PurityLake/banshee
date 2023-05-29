#include <math.h>
#include <stdint.h>

int
isnan(double x)
{
  union
  {
    uint64_t u;
    double f;
  } ieee754;
  ieee754.f = x;
  return ((unsigned)(ieee754.u >> 32) & 0x7FFFFFFF)
             + ((unsigned)(ieee754.u) != 0)
         > 0x7FF00000;
}
