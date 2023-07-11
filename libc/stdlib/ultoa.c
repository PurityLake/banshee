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

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

char *
ultoa(unsigned long n, char *buffer, int radix)
{
  if(radix < 2)
  {
    return NULL;
  }

  char reverse[70];

  int i;
  for(i = 0; i < 70; ++i)
  {
    size_t val = n % radix;
    if(val > 9)
    {
      reverse[i] = 'A' + (val - 10);
    }
    else
    {
      reverse[i] = '0' + val;
    }
    n /= radix;
    if(n == 0)
    {
      reverse[i + 1] = '\0';
      break;
    }
  }

  for(int j = 0; i >= 0; --i, ++j)
  {
    buffer[j] = reverse[i];
    if(i == 0)
    {
      buffer[j + 1] = '\0';
    }
  }

  return buffer;
}
