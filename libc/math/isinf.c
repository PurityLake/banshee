#include <math.h>
#include <stdint.h>

int
isinf(double x)
{
  union
  {
    uint64_t u;
    double f;
  } ieee754;
  ieee754.f = x;
  return ((unsigned)(ieee754.u >> 32) & 0x7FFFFFFF) == 0x7FF00000
         && ((unsigned)(ieee754.u) == 0);
}
