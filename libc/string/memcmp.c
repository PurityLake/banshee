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

int
memcmp(const void *ptr1, const void *ptr2, size_t len)
{
  if((uintptr_t)ptr1 % sizeof(long) == 0 && (uintptr_t)ptr2 % sizeof(long) == 0
     && len % sizeof(long) == 0)
  {
    const long *lptr1 = (const long *)ptr1;
    const long *lptr2 = (const long *)ptr2;
    for(size_t i = 0; i < len / sizeof(long); ++i)
    {
      if(lptr1[i] > lptr2[i])
      {
        return 1;
      }
      else if(lptr1[i] < lptr2[i])
      {
        return -1;
      }
    }
  }
  else
  {
    const char *cptr1 = (const char *)ptr1;
    const char *cptr2 = (const char *)ptr2;
    for(size_t i = 0; i < len; ++i)
    {
      if(cptr1[i] > cptr2[i])
      {
        return 1;
      }
      else if(cptr1[i] < cptr2[i])
      {
        return -1;
      }
    }
  }
  return 0;
}
