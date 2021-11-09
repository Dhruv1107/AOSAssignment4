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

void multiplyComplexNumbers(complexNum *cNums, int index);

#endif
