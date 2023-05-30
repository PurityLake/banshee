/* Copyright 2023 Robert O'Shea
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
