
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <complex.h>


#define __assume_aligned(x,y) x=__builtin_assume_aligned(x,y)


int main()
{
	float *ptr1 = _mm_malloc(1280 , 64);
	float *ptr2 = _mm_malloc(1280 , 64);
	int storageOffset = 0, j=0;

	for (j=0; j<1280; j++){
		ptr1[j] = 1.2f * j;
		ptr2[j] = 2.2f * j;
		}
	
	float complex *realptr1 = (float complex *)&ptr1[storageOffset];
	float complex *realptr2 = (float complex *)&ptr2[storageOffset];
	
	
  __assume_aligned(realptr1, 64);
  __assume_aligned(realptr2, 64);
//  realptr1 = __builtin_assume_aligned(realptr1, 64);
//  realptr2 = __builtin_assume_aligned(realptr2, 64);

#pragma GCC ivdep
  for (j = 0; j < 512; j++)
  {
  	
  	float complex derSlot0 = realptr1[j] * realptr2[j];
  	float complex derSlot1 = realptr1[j] + realptr2[j];
    realptr1[j] = derSlot0;
    realptr2[j] = derSlot1;
  }
	
	printf("got answer = %d\n",realptr1[0]);
	
	_mm_free(ptr1);
	_mm_free(ptr2);
	return 0;
}
