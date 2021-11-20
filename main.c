#include "complexnumbers.h"

/*
  Expected Command line arguments:
  1) Input file that is to be read
*/
int main(int argc, char **argv){
	int noOfComplexNums;
	char CNos[20];
	char str[20];
	char *token1, *token2;
	
	if(argc != 2){
		printf("Execute it as: #executablename #inputfilename\n");
		exit(1);
	}
	
	FILE *f;
	f = fopen(argv[1], "r");
	
	// if there is an error, exit
	if(f == NULL) {
		perror("Error opening file");
		return(-1); 
	}
	// if there is no error, read the first line which is no of complex nos
	else{ 
		fgets(CNos, 20, f);
	}
	
	noOfComplexNums = atoi(CNos);
	complexNums = ( struct complex * ) malloc ((noOfComplexNums+1)* sizeof (struct complex));
	int index = 0;
	
	while (fgets(str,sizeof str,f) != NULL) {
		//tokenize the string until + and store it in token1
		token1 = strtok(str,"+");
		//tokenize the string until i and store it in token2
		token2 = strtok(NULL, "i");
		if(!token2){
			printf("Check your input format. It is wrong it should be a+i-b or a+ib\n");
			return 1;
		}
		if(atoi(token1) == 0 && atoi(token2) == 0) {
			printf("One of the complex number is 0+0i so the multiplication result would be 0+0i\n");
			return 2;
		}
		complexNums[index].real = atoi(token1);
		complexNums[index].imaginary = atoi(token2);
		index++;
	}
	
	if(index <= 1){
		printf("You need at atleast two numbers for complex number multiplication\n");
		return 3;
	}

	multiplyComplexNumbers(complexNums, index);
	return 0;
}
