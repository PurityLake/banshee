#ifndef __H_BANSHEE_KERNEL_PORT__
#define __H_BANSHEE_KERNEL_PORT__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

  unsigned char inb(uint16_t port);
  void outb(uint16_t port, unsigned char data);

#ifdef __cplusplus
}
#endif

#endif /* __H_BANSHEE_KERNEL_PORT__ */
