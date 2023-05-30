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

void *
memmove(void *dest, const void *src, size_t len)
{
  if((uintptr_t)dest % sizeof(long) == 0 && (uintptr_t)src % sizeof(long) == 0
     && len % sizeof(long))
  {
    long *ldest = (long *)dest;
    const long *lsrc = (const long *)src;

    for(size_t i = 0; i < len / sizeof(long); ++i)
    {
      *ldest++ = *lsrc++;
    }
  }
  else
  {
    char *cdest = (char *)dest;
    const char *csrc = (const char *)src;

    for(size_t i = 0; i < len; ++i)
    {
      *cdest++ = *csrc++;
    }
  }

  return dest;
}
