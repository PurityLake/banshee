#include <string.h>

int
memcmp(const void *ptr1, const void *ptr2, size_t len)
{
  if((uintptr_t)ptr1 % sizeof(long) == 0 && (uintptr_t)ptr2 % sizeof(long) == 0
     && len % sizeof(long) == 0)
  {
    const long *lptr1 = (const long *)ptr1;
    const long *lptr2 = (const long *)ptr2;
    for(size_t i = 0; i < len / sizeof(long); ++i)
    {
      if(lptr1[i] > lptr2[i])
      {
        return 1;
      }
      else if(lptr1[i] < lptr2[i])
      {
        return -1;
      }
    }
  }
  else
  {
    const char *cptr1 = (const char *)ptr1;
    const char *cptr2 = (const char *)ptr2;
    for(size_t i = 0; i < len; ++i)
    {
      if(cptr1[i] > cptr2[i])
      {
        return 1;
      }
      else if(cptr1[i] < cptr2[i])
      {
        return -1;
      }
    }
  }
  return 0;
}
