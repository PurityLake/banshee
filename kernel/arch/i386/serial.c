/* Copyright 2023 Robert O'Shea
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <kernel/port.h>
#include <kernel/serial.h>

// TODO: Add interrupts at a later time

enum uart_register_names
{
  THR_WRITE = 0, /* Transmitter Holder Buffer */
  PBR_READ = 0,  /* Reciever Buffer */
  DLL_RW = 0,    /* Divsor Latch Low Byte */
  IER_RW = 1,    /* Interrupt Enable Register */
  DLH_RW = 1,    /* Divsor Latch High Byte */
  IIR_READ = 2,  /* Interrupt Identification Register */
  FCR_WRITE = 2, /* FIFO Control Register */
  LCR_RW = 3,    /* Line Control Register */
  MCR_RW = 4,    /* Modem Control Register */
  LSR_READ = 5,  /* Line Status Register */
  MSR_READ = 6,  /* Modem Status Register */
  SR_RW = 7,     /* Scratch Register */
};

int
serial_init(uint16_t device)
{
  port_outb(device + IER_RW, 0x00);
  port_outb(device + LCR_RW, 0x80);
  port_outb(device + DLL_RW, 0x03);
  port_outb(device + DLH_RW, 0x00);
  port_outb(device + LCR_RW, 0x03);
  port_outb(device + FCR_WRITE, 0x07);
  port_outb(device + MCR_RW, 0x13);
  port_outb(device + THR_WRITE, 0xAE);

  /* Check if serial if faulty (i.e: not same byte as sent) */
  if(port_inb(device + PBR_READ) != 0xAE)
  {
    return 1;
  }

  /* If serial is not faulty set it in normal operation mode
   * (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled) */
  port_outb(device + MCR_RW, 0x0F);
  return 0;
}

static inline int
serial_recevied(uint16_t device)
{
  return port_inb(device + LSR_READ) & 1;
}

unsigned char
serial_read(uint16_t device)
{
  while(serial_recevied(device) == 0)
    ;

  return port_inb(device + PBR_READ);
}

static inline int
is_transmit_empty(uint16_t device)
{
  return port_inb(device + LSR_READ) & 0x20;
}

void
serial_write(uint16_t device, unsigned char data)
{
  while(is_transmit_empty(device) == 0)
    ;

  port_outb(device + THR_WRITE, data);
}
