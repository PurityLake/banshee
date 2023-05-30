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

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define SERIAL_PORT1 0x3F8
#define SERIAL_PORT2 0x2F8

  int serial_init(uint16_t device);
  unsigned char serial_read(uint16_t device);
  void serial_write(uint16_t device, unsigned char data);

#ifdef __cplusplus
}
#endif

#endif /* __H_BANSHEE_KERNEL_SERIAL__ */
