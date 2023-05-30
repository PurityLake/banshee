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

#include <stdlib.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

__attribute__((__noreturn__)) void
abort(void)
{
#if defined(__is_libk)
  // TODO: Add proper kernel panic
  terminal_writestring("kernel: panic: abort()\n");
#else
  // TODO: Abnormally terminate the process as if by SIGABRT
#endif
  while(1)
  {
  }
  __builtin_unreachable();
}
