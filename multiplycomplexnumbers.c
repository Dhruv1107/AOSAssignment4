#include "complexnumbers.h"

void displayComplexNumbers(complexNum *complexNums,int index) {
	for(int i = 0;i<index;i++) {
		printf("%d+i%d\n",complexNums[i].real,complexNums[i].imaginary);
	}
}

void *runner3(void *param) {
	complexNum cn1 = *(complexNum *)param;
	complexNum cn2 = oddComplexNum;
	complexNum *res = malloc(sizeof(complexNum));
	complexNum ans;
	if(cn1.real == cn2.real && cn1.imaginary == cn2.imaginary){
		*res = cn1;
		return (void*) res;
	}
	ans.real = cn1.real * cn2.real - cn1.imaginary * cn2.imaginary;
	ans.imaginary = cn1.real * cn2.imaginary + cn2.real * cn1.imaginary;
	*res = ans;
	return (void*) res;
}

void *runner1(void *param) {
	complexNum cn1 = *(complexNum *)param;
	complexNum cn2 = *(complexNum *)(param + sizeof(complexNum));
	complexNum *res = malloc(sizeof(complexNum));
	complexNum ans;
	ans.real = cn1.real * cn2.real - cn1.imaginary * cn2.imaginary;
	ans.imaginary = cn1.real * cn2.imaginary + cn2.real * cn1.imaginary;
	*res = ans;
	return (void*) res;
}

complexNum createThreads(complexNum *complexNums, int index) {
	complexNum *res,*nextNums;
	//printf("Index:%d\n",index);
	int noOfThreads = index/2;
	
	if(index % 2 == 1 && oddComplexNum.real == 0 && oddComplexNum.imaginary ==0){
		oddComplexNum = complexNums[index-1];
		printf("Last CNO:%d+i%d\n",oddComplexNum.real,oddComplexNum.imaginary);
		//noOfThreads++;
		test = 1;
		
	}
	if(noOfThreads == 1 && test == 1){
		noOfThreads++;
		createExtraThread = 1;
	}
	//printf("No Of threads:%d\n",noOfThreads);
	pthread_t tid[noOfThreads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	

	//printf("No of threads:%d\n",noOfThreads);
	for(int i=0; i< noOfThreads; i++){
		if(i == (noOfThreads-1) && createExtraThread == 1){
			pthread_create(&tid[i],&attr,runner3,&complexNums[i*2]);
			createExtraThread = 0;
			test = 0;
			break;
		}
		if(pthread_create(&tid[i],&attr,runner1,&complexNums[i*2]) != 0){
			perror("Failed to create thread\n");
		}
	}
	int i = 0;
	if(noOfThreads == 1){
		complexNum *res = malloc(sizeof(complexNum));
		if(pthread_join(tid[0],(void**) &res) != 0){
			perror("Failed to create thread\n");
		}
		//printf("Last CNO:%d+i%d\n",oddComplexNum.real,oddComplexNum.imaginary);
		//printf("Res:%d+i%d\n",res->real,res->imaginary);
		if(test){
			test = 0;
			complexNum ans;
			int resReal = res->real;
			int resImag = res->imaginary;
			int lastReal = oddComplexNum.real;
			int lastImag = oddComplexNum.imaginary;
			ans.real = resReal * lastReal - resImag * lastImag;
			ans.imaginary = resImag * lastReal + lastImag * resReal;
			*res = ans;
		}
		return *res;	
	}
	
	nextNums = ( struct complex * ) malloc ((noOfThreads+1)* sizeof (struct complex));
	for(i=0; i< noOfThreads; i++){
		if(pthread_join(tid[i],(void**) &res) != 0){
			perror("Failed to create thread\n");
		}
		nextNums[i].real = res->real;
		nextNums[i].imaginary = res->imaginary;
		printf("Thread %d ans: %d+i%d\n",i,res->real,res->imaginary);
	}
	createThreads(nextNums,i);
}

void multiplyComplexNumbers(complexNum *complexNums, int index) {
	//printf("Index:%d\n",index);
	//displayComplexNumbers(complexNums, index);
	//complexNum optional;
	complexNum ans = createThreads(complexNums, index);
	printf("Ans:%d+i%d\n",ans.real,ans.imaginary);
}
