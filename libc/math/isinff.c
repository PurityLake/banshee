#include <math.h>
#include <stdint.h>

int
isinff(float x)
{
  union
  {
    uint64_t u;
    double f;
  } ieee754;
  ieee754.f = x;
  return ((unsigned)(ieee754.u >> 16) & 0x7FFF) == 0x7FF0
         && ((unsigned)(ieee754.u) == 0);
}
