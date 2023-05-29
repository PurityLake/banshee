#include <kernel/tty.h>
#include <stdio.h>

void
kernel_main(void)
{
  terminal_initialize();
  for(int i = 0; i < 10000; ++i)
  {
    printf("%x\n", i);
  }
}
