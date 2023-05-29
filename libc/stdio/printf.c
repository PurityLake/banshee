#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __is_libk
#include <kernel/tty.h>
#else
#error "libc is not ready yet"
#endif

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
      else if(*c == 'd')
      {
        int number = va_arg(argp, int);
        char buffer[50];
        itoa(number, buffer, 10);
        puts(buffer);
      }
      else if(*c == 'x' || *c == 'X')
      {
        int number = va_arg(argp, int);
        char buffer[50];
        itoa(number, buffer, 16);
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
    }
    else
    {
      putchar(*c);
    }
    ++c;
  }
  return 1;
}
