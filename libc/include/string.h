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

#ifndef __H_BANSHEE_STRING__
#define __H_BANSHEE_STRING__

#include <banshee/cdefs.h>

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

  size_t strlen(const char *str);

  int memcmp(const void *ptr1, const void *ptr2, size_t len);
  void *memcpy(void *dest, const void *src, size_t len);
  void *memset(void *ptr, int value, size_t len);
  void *memmove(void *dest, const void *src, size_t len);

  char *strcpy(char *dest, const char *src);
  char *strcat(char *dest, const char *src);

#ifdef __cplusplus
}
#endif

#endif /* __H_BANSHEE_STRING__ */
