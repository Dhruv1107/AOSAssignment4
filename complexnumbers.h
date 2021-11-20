#ifndef _COMPLEXNUMBERS_HEADER
#define _COMPLEXNUMBERS_HEADER

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct complex
{
    int real;
    int imaginary;
} complexNum;
complexNum *complexNums;

/*
  Pre-condition: index greater than 1, 
  		  the input format should for cNums should be in a+ib or a+i-b
  Post-condition: Recursive function which gives the multiplication result of index number of threads
*/
void multiplyComplexNumbers(complexNum *cNums, int index);

#endif
