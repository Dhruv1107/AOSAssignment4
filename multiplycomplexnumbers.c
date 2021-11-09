#include "complexnumbers.h"

void multiplyComplexNumbers(complexNum *complexNums, int index) {
	for(int i = 0;i<index;i++) {
		printf("%d+i%d\n",complexNums[i].real,complexNums[i].imaginary);
	}
}
