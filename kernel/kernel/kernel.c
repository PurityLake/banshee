#include <kernel/serial.h>
#include <kernel/tty.h>
#include <stdio.h>
#include <string.h>

void
kernel_main(void)
{
  terminal_initialize();

  puts("Initialize Serial I/O\n");
  if(serial_init() == 0)
  {
    puts("Finished Intiializing Serial I/O\n");

    char message[] = "Hello Serial\n";
    size_t len = strlen(message);

    for(size_t i = 0; i < len; ++i)
    {
      serial_write(message[i]);
    }
  }
  else
  {
    puts("Failed To Initialize Serial I/O\n");
  }
}
