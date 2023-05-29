#ifndef __H_BANSHEE_STDLIB__
#define __H_BANSHEE_STDLIB__

#ifdef __cplusplus
extern "C"
{
#endif

  __attribute__((__noreturn__)) void abort(void);

  char *itoa(int n, char *buffer, int radix);

#ifdef __cplusplus
}
#endif

#endif /* __H_BANSHEE_STDLIB__ */
