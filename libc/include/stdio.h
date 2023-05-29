#ifndef __H_BANSHEE_STDIO__
#define __H_BANSHEE_STDIO__

#include <stdarg.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C"
{
#endif

  int putchar(char c);
  int puts(const char *str);
  int printf(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* __H_BANSHEE__STDIO__ */
