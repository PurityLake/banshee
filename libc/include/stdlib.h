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

#ifndef __H_BANSHEE_STDLIB__
#define __H_BANSHEE_STDLIB__

#ifdef __cplusplus
extern "C"
{
#endif

  __attribute__((__noreturn__)) void abort(void);

  char *itoa(int n, char *buffer, int radix);
  char *utoa(unsigned int n, char *buffer, int radix);
  char *ftoa(float f, char *buffer, int after);
  char *dtoa(double d, char *buffer, int after);

#ifdef __cplusplus
}
#endif

#endif /* __H_BANSHEE_STDLIB__ */
