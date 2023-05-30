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

#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

char *
strcpy(char *dest, const char *src)
{
  size_t destlen = strlen(dest);
  size_t srclen = strlen(src);

  if(srclen == 0)
  {
    return dest;
  }

  size_t n = destlen == 0 ? srclen : MIN(destlen, srclen);

  for(size_t i = 0; i <= n; ++i)
  {
    dest[i] = *src++;
  }

  return dest;
}
