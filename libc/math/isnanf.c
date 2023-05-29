#include <math.h>
#include <stdint.h>

int
isnanf(float x)
{
  union
  {
    uint32_t u;
    float f;
  } ieee754;
  ieee754.f = x;
  return ((unsigned)(ieee754.u >> 16) & 0x7FFF) + ((unsigned)(ieee754.u) != 0)
         > 0x7FF00;
}
