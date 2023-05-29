#include <string.h>

int
memcmp(const void *ptr1, const void *ptr2, size_t num)
{
  const unsigned char *cptr1 = (const unsigned char *)ptr1;
  const unsigned char *cptr2 = (const unsigned char *)ptr2;
  for(size_t i = 0; i < num; ++i)
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
  return 0;
}
