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

#include <kernel/port.h>

unsigned char
inb(uint16_t port)
{
  unsigned char result;
  asm volatile("in %%dx, %%al" : "=a"(result) : "d"(port) : "memory");
  return result;
}

void
outb(uint16_t port, unsigned char data)
{
  asm volatile("out %%al, %%dx" : : "a"(data), "d"(port) : "memory");
}
