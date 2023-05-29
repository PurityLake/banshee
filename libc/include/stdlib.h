#ifndef __H_BANSHEE_STDLIB__
#define __H_BANSHEE_STDLIB__

#ifdef __cplusplus
extern "C"
{
#endif

  __attribute__((__noreturn__)) void abort(void);

  char *itoa(int n, char *buffer, int radix);
  char *utoa(unsigned int n, char *buffer, int radix);
  char *ftoa(float f, char *buffer, int after);
  char *dtoa(double d, char *buffer, int after);

#ifdef __cplusplus
}
#endif

#endif /* __H_BANSHEE_STDLIB__ */
