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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/serial.h>
#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

void
terminal_initialize(void)
{
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = VGA_MEMORY;
  for(size_t y = 0; y < VGA_HEIGHT; y++)
  {
    for(size_t x = 0; x < VGA_WIDTH; x++)
    {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void
terminal_setcolor(uint8_t color)
{
  terminal_color = color;
}

void
terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
  serial_write(SERIAL_PORT1, c);
}

static void
terminal_scroll()
{
  for(size_t y = 1; y < VGA_HEIGHT; ++y)
  {
    for(size_t x = 0; x < VGA_WIDTH; ++x)
    {
      const size_t index1 = (y - 1) * VGA_WIDTH + x;
      const size_t index2 = y * VGA_WIDTH + x;
      terminal_buffer[index1] = terminal_buffer[index2];
    }
  }

  size_t y = VGA_WIDTH * (VGA_HEIGHT - 1);
  for(size_t x = 0; x < VGA_WIDTH; ++x)
  {
    terminal_buffer[y + x] = vga_entry(' ', terminal_color);
  }
}

void
terminal_putchar(char c)
{
  unsigned char uc = c;
  if(c == '\n')
  {
    serial_write(SERIAL_PORT1, c);
    terminal_column = 0;
    if(terminal_row + 1 == VGA_HEIGHT)
    {
      terminal_scroll();
    }
    else
    {
      terminal_row++;
    }
  }
  else
  {
    terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
    if(++terminal_column == VGA_WIDTH)
    {
      serial_write(SERIAL_PORT1, '\n');
      terminal_column = 0;
      if(terminal_row + 1 == VGA_HEIGHT)
      {
        terminal_scroll();
      }
      else
      {
        ++terminal_row;
      }
    }
  }
}

void
terminal_write(const char *data, size_t size)
{
  for(size_t i = 0; i < size; i++)
  {
    terminal_putchar(data[i]);
  }
}

void
terminal_writestring(const char *data)
{
  terminal_write(data, strlen(data));
}

void
terminal_writeerror(const char *data)
{
  uint8_t prev_color = terminal_color;
  terminal_color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
  terminal_writestring(data);
  terminal_color = prev_color;
}
