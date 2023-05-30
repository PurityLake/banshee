#include <kernel/serial.h>
#include <kernel/tty.h>
#include <stdio.h>
#include <string.h>

void
kernel_main(void)
{
  terminal_initialize();

  if(serial_init() == 0)
  {
    puts("Attempint to intialize Serial I/O\n");
    puts("Finished intializing Serial I/O\n");

    char message[] = "Hello Serial\n";
    size_t len = strlen(message);

    for(size_t i = 0; i < len; ++i)
    {
      serial_write(message[i]);
    }
  }
  else
  {
    terminal_writeerror("Failed to initialize Serial I/O\n");
  }
}
