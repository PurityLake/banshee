#include <kernel/tty.h>
#include <stdio.h>

void
kernel_main(void)
{
  terminal_initialize();
  double f = 129103.105145;
  printf("%f\n", f);
}
