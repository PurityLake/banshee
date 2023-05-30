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
