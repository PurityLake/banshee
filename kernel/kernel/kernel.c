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

#include <kernel/serial.h>
#include <kernel/tty.h>
#include <stdio.h>
#include <string.h>

void
kernel_main(void)
{
  terminal_initialize();

  if(serial_init(SERIAL_PORT1) == 0)
  {
    puts("Attempint to intialize Serial I/O\n");
    puts("Finished intializing Serial I/O\n");

    char message[] = "Hello Serial\n";
    size_t len = strlen(message);

    for(size_t i = 0; i < len; ++i)
    {
      serial_write(SERIAL_PORT1, message[i]);
    }
  }
  else
  {
    terminal_writeerror("Failed to initialize Serial I/O\n");
  }
}
