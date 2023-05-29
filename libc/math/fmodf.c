#include <math.h>
#include <stdint.h>

float
fmodf(float x, float y)
{
  union
  {
    float f;
    uint32_t i;
  } ux = { x }, uy = { y };

  int ex = ux.i >> 23 & 0xFF;
  int ey = uy.i >> 23 & 0xFF;
  int sx = ux.i & 0x80000000;
  uint32_t i;

  /* should be ux.i but gcc adds float load/store
   * to inner loops, ruining performance ande code size */
  uint32_t uxi = ux.i;

  if(uy.i << 1 == 0 || isnan(y) || ex == 0xFF)
  {
    return (x * y) / (x / y);
  }

  if(uxi << 1 <= uy.i << 1)
  {
    if(uxi << 1 == uy.i << 1)
    {
      return 0 * x;
    }
    return x;
  }

  /* normalize x and y */
  if(!ex)
  {
    for(i = uxi << 9; i >> 31 == 0; --ex, i <<= 1)
      ;
    uxi <<= -ex + 1;
  }
  else
  {
    uxi &= -1ULL >> 9;
    uxi |= 1ULL << 23;
  }

  if(!ey)
  {
    for(i = uy.i << 9; i >> 31 == 0; --ey, i <<= 1)
      ;
    uy.i <<= -ey + 1;
  }
  else
  {
    uy.i &= -1ULL >> 9;
    uy.i |= 1ULL << 23;
  }

  /* x mod y */
  for(; ex > ey; ex--)
  {
    i = uxi - uy.i;
    if(i >> 31 == 0)
    {
      if(i == 0)
      {
        return 0 * x;
      }
      uxi = i;
    }
    uxi <<= 1;
  }
  i = uxi - uy.i;
  if(i >> 31 == 0)
  {
    if(i == 0)
    {
      return 0 * x;
    }
    uxi = i;
  }
  for(; uxi >> 23 == 0; uxi <<= 1, --ex)
    ;

  /* scale result */
  if(ex > 0)
  {
    uxi -= 1ULL << 23;
    uxi |= (uint32_t)ex << 23;
  }
  else
  {
    uxi >>= -ex + 1;
  }
  uxi |= sx << 31;
  ux.i = uxi;
  return ux.f;
}
