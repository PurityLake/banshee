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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __is_libk
#include <kernel/tty.h>
#else
#error "libc is not ready yet"
#endif

// TODO: Add scientific notation
// TODO: Add flags, width, length and precision

int
printf(const char *format, ...)
{
  va_list argp;
  va_start(argp, format);

  const char *c = format;

  while(*c != '\0')
  {
    if(*c == '%')
    {
      ++c;
      if(*c == '%')
      {
        putchar('%');
      }
      else if(*c == 'n')
      {
        // do nothing
      }
      else if(*c == 'c')
      {
        char to_print = va_arg(argp, int);
        putchar(to_print);
      }
      else if(*c == 's')
      {
        char *s = va_arg(argp, char *);
        puts(s);
      }
      else if(*c == 'p')
      {
        uintptr_t addr = va_arg(argp, uintptr_t);
        if(sizeof(addr) > sizeof(int))
        {
          puts("\nNotSupported\n");
        }
        else
        {
          char buffer[50];
          utoa(addr, buffer, 16);
          puts("0x");
          puts(buffer);
        }
      }
      else if(*c == 'd' || *c == 'i')
      {
        int number = va_arg(argp, double);
        char buffer[50];
        itoa(number, buffer, 10);
        puts(buffer);
      }
      else if(*c == 'f')
      {
        double number = va_arg(argp, double);
        char buffer[50];
        dtoa(number, buffer, 5);
        puts(buffer);
      }
      else if(*c == 'u')
      {
        if((*c + 1) == 'l')
        {
          if((*c + 2) == 'l')
          {
            ++c;
          }
          ++c;
        }
        else
        {
          unsigned int number = va_arg(argp, unsigned int);
          char buffer[50];
          utoa(number, buffer, 10);
          puts(buffer);
        }
      }
      else if(*c == 'x' || *c == 'X')
      {
        unsigned int number = va_arg(argp, unsigned int);
        char buffer[50];
        utoa(number, buffer, 16);
        if(*c == 'X')
        {
          puts(buffer);
        }
        else
        {
          for(size_t i = 0; i < strlen(buffer); ++i)
          {
            if(buffer[i] > '9')
            {
              putchar('a' + (buffer[i] - 'A'));
            }
            else
            {
              putchar(buffer[i]);
            }
          }
        }
      }
      else if(*c == 'o')
      {
        int number = va_arg(argp, int);
        char buffer[50];
        itoa(number, buffer, 8);
        puts(buffer);
      }
      else if(*c == 'b')
      {
        int number = va_arg(argp, int);
        char buffer[33];
        for(int i = 0; i < 32; ++i)
        {
          if(number & 1)
          {
            buffer[i] = '1';
          }
          else
          {
            buffer[i] = '0';
          }
          number >>= 1;
        }
        buffer[32] = '\0';
        puts(buffer);
      }
    }
    else if(*c == 'l')
    {
      if(*c == 'l')
      {
        int radix;
        if(*(c + 1) == 'd')
        {
          radix = 10;
        }
        else if(*(c + 1) == 'b')
        {
          radix = 2;
        }
        else if(*(c + 1) == 'o')
        {
          radix = 8;
        }
        else if(*(c + 1) == 'x')
        {
          radix = 16;
        }
        else if(*(c + 1) == 'X')
        {
          radix = 16;
        }
        else
        {
          putchar(*c);
          ++c;
          continue;
        }

        long long number = va_arg(argp, long long);
        char buffer[70];

        if(radix == 16)
        {
          ulltoa(number, buffer, radix);
          if(*(c + 1) == 'X')
          {
            puts(buffer);
          }
          else
          {
            for(size_t i = 0; i < strlen(buffer); ++i)
            {
              if(buffer[i] > '9')
              {
                putchar('a' + (buffer[i] - 'A'));
              }
              else
              {
                putchar(buffer[i]);
              }
            }
          }
        }
        else
        {
          lltoa(number, buffer, radix);
          puts(buffer);
        }
        ++c;
      }
      else
      {
        int radix;
        if(*(c + 1) == 'd')
        {
          radix = 10;
        }
        else if(*(c + 1) == 'b')
        {
          radix = 2;
        }
        else if(*(c + 1) == 'o')
        {
          radix = 8;
        }
        else if(*(c + 1) == 'x')
        {
          radix = 16;
        }
        else if(*(c + 1) == 'X')
        {
          radix = 16;
        }
        else
        {
          putchar(*c);
          ++c;
          continue;
        }

        long number = va_arg(argp, long);
        char buffer[70];

        if(radix == 16)
        {
          ultoa(number, buffer, radix);
          if(*(c + 1) == 'X')
          {
            puts(buffer);
          }
          else
          {
            for(size_t i = 0; i < strlen(buffer); ++i)
            {
              if(buffer[i] > '9')
              {
                putchar('a' + (buffer[i] - 'A'));
              }
              else
              {
                putchar(buffer[i]);
              }
            }
          }
        }
        else
        {
          ltoa(number, buffer, radix);
          puts(buffer);
        }
      }
      ++c;
    }
    else
    {
      putchar(*c);
    }
    ++c;
  }
  return 1;
}
