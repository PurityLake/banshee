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
