#ifndef __H_BANSHEE_MATH__
#define __H_BANSHEE_MATH__

#ifdef __cplusplus
extern "C"
{
#endif

  double fmod(double x, double y);
  float fmodf(float x, float y);

  int isnan(double x);
  int isnanf(float x);

  int isinf(double x);
  int isinff(float x);

#ifdef __cplusplus
}
#endif

#endif /* __H_BANSHEE_MATH__ */
