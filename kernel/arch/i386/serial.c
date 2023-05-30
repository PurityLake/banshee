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
#include <kernel/serial.h>

// TODO: Add interrupts at a later time

int
serial_init(void)
{
  outb(SERIAL_PORT + 1, 0x00);
  outb(SERIAL_PORT + 3, 0x80);
  outb(SERIAL_PORT + 0, 0x03);
  outb(SERIAL_PORT + 1, 0x00);
  outb(SERIAL_PORT + 3, 0x03);
  outb(SERIAL_PORT + 2, 0x07);
  outb(SERIAL_PORT + 4, 0x13);
  outb(SERIAL_PORT + 0, 0xAE);

  /* Check if serial if faulty (i.e: not same byte as sent) */
  if(inb(SERIAL_PORT + 0) != 0xAE)
  {
    return 1;
  }

  /* If serial is not faulty set it in normal operation mode
   * (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled) */
  outb(SERIAL_PORT + 4, 0x0F);
  return 0;
}

static int
serial_recevied(void)
{
  return inb(SERIAL_PORT + 5) & 1;
}

char
serial_read(void)
{
  while(serial_recevied() == 0)
    ;

  return inb(SERIAL_PORT);
}

static int
is_transmit_empty(void)
{
  return inb(SERIAL_PORT + 5) & 0x20;
}

void
serial_write(char a)
{
  while(is_transmit_empty() == 0)
    ;

  outb(SERIAL_PORT, a);
}
