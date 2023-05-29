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
