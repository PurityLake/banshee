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

#ifndef __H_BANSHEE_KERNEL_SERIAL__
#define __H_BANSHEE_KERNEL_SERIAL__

#ifdef __cplusplus
extern "C"
{
#endif

#define SERIAL_PORT 0x3F8

  int serial_init(void);
  char serial_read(void);
  void serial_write(char a);

#ifdef __cplusplus
}
#endif

#endif /* __H_BANSHEE_KERNEL_SERIAL__ */
