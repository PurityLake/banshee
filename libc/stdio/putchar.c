#include <stdio.h>

#ifdef __is_libk
#include <kernel/tty.h>
#else
#error "libc is not ready yet"
#endif

int
putchar(char c)
{
  terminal_putchar(c);
  return c;
}
