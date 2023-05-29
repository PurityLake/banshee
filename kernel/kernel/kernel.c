#include <kernel/tty.h>

void
kernel_main(void)
{
  terminal_initialize();
  for(int i = 0; i < 100; ++i)
  {
    terminal_putchar('A' + i);
    terminal_putchar('\n');
  }
}
