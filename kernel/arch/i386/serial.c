#include <kernel/port.h>
#include <kernel/serial.h>

// TODO: Add interrupts at a later time

int
serial_init(void)
{
  outb(SERIAL_PORT + 1, 0x00);
  outb(SERIAL_PORT + 3, 0x80);
  outb(SERIAL_PORT + 0, 0x03);
  outb(SERIAL_PORT + 1, 0x00);
  outb(SERIAL_PORT + 3, 0x03);
  outb(SERIAL_PORT + 2, 0x07);
  outb(SERIAL_PORT + 4, 0x13);
  outb(SERIAL_PORT + 0, 0xAE);

  /* Check if serial if faulty (i.e: not same byte as sent) */
  if(inb(SERIAL_PORT + 0) != 0xAE)
  {
    return 1;
  }

  /* If serial is not faulty set it in normal operation mode
   * (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled) */
  outb(SERIAL_PORT + 4, 0x0F);
  return 0;
}

static int
serial_recevied(void)
{
  return inb(SERIAL_PORT + 5) & 1;
}

char
serial_read(void)
{
  while(serial_recevied() == 0)
    ;

  return inb(SERIAL_PORT);
}

static int
is_transmit_empty(void)
{
  return inb(SERIAL_PORT + 5) & 0x20;
}

void
serial_write(char a)
{
  while(is_transmit_empty() == 0)
    ;

  outb(SERIAL_PORT, a);
}
