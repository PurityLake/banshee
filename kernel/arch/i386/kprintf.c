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

#include <kernel/io.h>
#include <kernel/tty.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 128

// TODO: Add scientific notation
// TODO: Add flags, width, length and precision

// forward declarations
static int print_ptr(uintptr_t ptr);
static int print_int(int i, int radix);
static int print_uint(unsigned int i, int radix);
static int print_intbinary(unsigned int i);
static int print_intoctal(unsigned int i);
static int print_inthex(unsigned int i, int capital);
static int print_float(float d);
static int print_double(double d);
static int print_long(long i, size_t radix);
static int print_longhex(unsigned long l, int capital);
static int print_ll(long long i, size_t radix);
static int print_llhex(unsigned long long ll, int capital);
static int print_ul(unsigned long i, size_t radix);
static int print_ull(unsigned long long i, size_t radix);

int
kprintf(const char *format, ...)
{
  va_list argp;
  va_start(argp, format);

  const char *c = format;
  unsigned int chars_printed = 0;

  while(*c != '\0')
  {
    if(*c == '%')
    {
      ++c;
      if(*c == '%')
      {
        chars_printed += kputchar('%');
      }
      else if(*c == 'n')
      {
        // do nothing
      }
      else if(*c == 'c')
      {
        chars_printed += kputchar((char)va_arg(argp, int));
      }
      else if(*c == 's')
      {
        chars_printed += kputs(va_arg(argp, const char *));
      }
      else if(*c == 'p')
      {
        chars_printed += print_ptr(va_arg(argp, uintptr_t));
      }
      else if(*c == 'd' || *c == 'i')
      {
        chars_printed += print_int(va_arg(argp, double), 10);
      }
      else if(*c == 'f')
      {
        chars_printed += print_float((float)va_arg(argp, double));
      }
      else if(*c == 'u')
      {
        if((*c + 1) == 'l')
        {
          ++c;
          if((*c + 1) == 'l')
          {
            chars_printed += print_ull(va_arg(argp, unsigned long long), 10);
          }
          else
          {
            chars_printed += print_ul(va_arg(argp, unsigned long), 10);
          }
        }
        else
        {
          chars_printed += print_uint(va_arg(argp, unsigned int), 10);
        }
      }
      else if(*c == 'x' || *c == 'X')
      {
        chars_printed += print_inthex(va_arg(argp, unsigned int), *c == 'X');
      }
      else if(*c == 'o')
      {
        chars_printed += print_intoctal(va_arg(argp, unsigned int));
      }
      else if(*c == 'b')
      {
        chars_printed += print_intbinary(va_arg(argp, unsigned int));
      }
      else if(*c == 'l')
      {
        ++c;
        if(*c == 'l')
        {
          ++c;
          if(*c == 'f')
          {
            chars_printed += print_double(va_arg(argp, double));
            ++c;
            continue;
          }

          int cont = 0;
          int radix;
          if(*c == 'd')
          {
            radix = 10;
          }
          else if(*c == 'b')
          {
            radix = 2;
          }
          else if(*c == 'o')
          {
            radix = 8;
          }
          else if(*c == 'x')
          {
            radix = 16;
          }
          else if(*c == 'X')
          {
            radix = 16;
          }
          else
          {
            cont = 1;
            radix = 10;
          }

          if(radix == 16)
          {
            chars_printed
                += print_llhex(va_arg(argp, unsigned long long), *c == 'X');
          }
          else
          {
            chars_printed += print_ll(va_arg(argp, long long), radix);
          }

          if(cont)
          {
            continue;
          }
        }
        else
        {
          int cont = 0;
          int radix;
          if(*c == 'd')
          {
            radix = 10;
          }
          else if(*c == 'b')
          {
            radix = 2;
          }
          else if(*c == 'o')
          {
            radix = 8;
          }
          else if(*c == 'x')
          {
            radix = 16;
          }
          else if(*c == 'X')
          {
            radix = 16;
          }
          else
          {
            cont = 1;
            radix = 10;
          }

          if(radix == 16)
          {
            chars_printed
                += print_longhex(va_arg(argp, unsigned long), *c == 'X');
          }
          else
          {
            chars_printed += print_long(va_arg(argp, long), radix);
          }

          if(cont)
          {
            continue;
          }
        }
      }
      else
      {
        chars_printed += kputchar(*c);
      }
    }
    else
    {
      chars_printed += kputchar(*c);
    }
    ++c;
  }
  return chars_printed;
}

static int
print_ptr(uintptr_t ptr)
{
  char buffer[MAX_BUFFER_SIZE];
  ulltoa(ptr, buffer, 16);
  kputs("0x");
  return kputs(buffer) + 2;
}

static int
print_int(int i, int radix)
{
  char buffer[MAX_BUFFER_SIZE];
  itoa(i, buffer, radix);
  return kputs(buffer);
}

static int
print_uint(unsigned int i, int radix)
{
  char buffer[MAX_BUFFER_SIZE];
  utoa(i, buffer, radix);
  return kputs(buffer);
}

static int
print_intbinary(unsigned int i)
{
  char buffer[MAX_BUFFER_SIZE];
  utoa(i, buffer, 2);
  return kputs(buffer);
}

static int
print_intoctal(unsigned int i)
{
  char buffer[MAX_BUFFER_SIZE];
  utoa(i, buffer, 8);
  return kputs(buffer);
}

static int
print_inthex(unsigned int i, int capital)
{
  char buffer[MAX_BUFFER_SIZE];
  utoa(i, buffer, 16);
  if(!capital)
  {
    for(size_t i = 0; i < strlen(buffer); ++i)
    {
      if(buffer[i] > '9')
      {
        kputchar('a' + (buffer[i] - 'A'));
      }
      else
      {
        kputchar(buffer[i]);
      }
    }
  }
  else
  {
    return kputs(buffer);
  }
  return strlen(buffer);
}

static int
print_float(float f)
{
  char buffer[MAX_BUFFER_SIZE];
  ftoa(f, buffer, 10);
  return kputs(buffer);
}

static int
print_double(double d)
{
  char buffer[MAX_BUFFER_SIZE];
  dtoa(d, buffer, 10);
  return kputs(buffer);
}

static int
print_long(long i, size_t radix)
{
  char buffer[MAX_BUFFER_SIZE];
  ltoa(i, buffer, radix);
  return kputs(buffer);
}

static int
print_longhex(unsigned long l, int capital)
{
  char buffer[MAX_BUFFER_SIZE];
  ultoa(l, buffer, 16);
  if(!capital)
  {
    for(size_t i = 0; i < strlen(buffer); ++i)
    {
      if(buffer[i] > '9')
      {
        kputchar('a' + (buffer[i] - 'A'));
      }
      else
      {
        kputchar(buffer[i]);
      }
    }
  }
  else
  {
    return kputs(buffer);
  }
  return strlen(buffer);
}

static int
print_ll(long long i, size_t radix)
{
  char buffer[MAX_BUFFER_SIZE];
  ltoa(i, buffer, radix);
  return kputs(buffer);
}

static int
print_llhex(unsigned long long ll, int capital)
{
  char buffer[MAX_BUFFER_SIZE];
  ulltoa(ll, buffer, 16);
  if(!capital)
  {
    for(size_t i = 0; i < strlen(buffer); ++i)
    {
      if(buffer[i] > '9')
      {
        kputchar('a' + (buffer[i] - 'A'));
      }
      else
      {
        kputchar(buffer[i]);
      }
    }
  }
  else
  {
    return kputs(buffer);
  }
  return strlen(buffer);
}

static int
print_ul(unsigned long i, size_t radix)
{
  char buffer[MAX_BUFFER_SIZE];
  ultoa(i, buffer, radix);
  return kputs(buffer);
}

static int
print_ull(unsigned long long i, size_t radix)
{
  char buffer[MAX_BUFFER_SIZE];
  ulltoa(i, buffer, radix);
  return kputs(buffer);
}
