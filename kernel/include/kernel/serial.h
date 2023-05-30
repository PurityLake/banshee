#ifndef __H_BANSHEE_KERNEL_SERIAL__
#define __H_BANSHEE_KERNEL_SERIAL__

#ifdef __cplusplus
extern "C"
{
#endif

#define SERIAL_PORT 0x3F8

  int serial_init(void);
  char serial_read(void);
  void serial_write(char a);

#ifdef __cplusplus
}
#endif

#endif /* __H_BANSHEE_KERNEL_SERIAL__ */
