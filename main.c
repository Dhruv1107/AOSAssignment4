#include "complexnumbers.h"

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
		fgets(CNos, 20, f); // read from file
	}
	
	noOfComplexNums = atoi(CNos);
	//complexNum complexNums[noOfComplexNums];
	complexNums = ( struct complex * ) malloc ((noOfComplexNums+1)* sizeof (struct complex));
	//printf("%d\n",noOfComplexNums);
	int index = 0;
	
	while (fgets(str,sizeof str,f) != NULL) {
		token1 = strtok(str,"+");
		token2 = strtok(NULL, "i");
		complexNums[index].real = atoi(token1);
		complexNums[index].imaginary = atoi(token2);
		index++;
	}

	
	multiplyComplexNumbers(complexNums, index);
	return 0;
}
