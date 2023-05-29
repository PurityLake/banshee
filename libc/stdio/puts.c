#include <string.h>

#ifdef __is_libk
#include <kernel/tty.h>
#else
#error "libc is not ready yet"
#endif

int
puts(const char *str)
{
  terminal_writestring(str);
  return 1;
}
