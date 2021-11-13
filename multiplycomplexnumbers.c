#include "complexnumbers.h"

void displayComplexNumbers(complexNum *complexNums,int index) {
	for(int i = 0;i<index;i++) {
		printf("%d+i%d\n",complexNums[i].real,complexNums[i].imaginary);
	}
}

void *runner1(void *param) {
	complexNum cn1 = *(complexNum *)param;
	complexNum cn2 = *(complexNum *)(param + sizeof(complexNum));
	//printf("%d+i%d in thread\n",cn1.real,cn1.imaginary);
	//printf("%d+i%d in thread\n",cn2.real,cn2.imaginary);
	complexNum *res = malloc(sizeof(complexNum));
	complexNum ans;
	ans.real = cn1.real * cn2.real - cn1.imaginary * cn2.imaginary;
	ans.imaginary = cn1.real * cn2.imaginary + cn2.real * cn1.imaginary;
	*res = ans;
	return (void*) res;
}

complexNum createThreads(complexNum *complexNums, int index) {
	//printf("Index:%d\n",index);
	complexNum *res,*nextNums;
	int noOfThreads = index/2;
	pthread_t tid[noOfThreads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	//printf("No of threads:%d\n",noOfThreads);
	for(int i=0; i< noOfThreads; i++){
		if(pthread_create(&tid[i],&attr,runner1,&complexNums[i*2]) != 0){
			perror("Failed to create thread\n");
		}
	}
	if(noOfThreads == 1){
		if(pthread_join(tid[0],(void**) &res) != 0){
			perror("Failed to create thread\n");
		}
		return *res;	
	}
	int i;
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
	complexNum ans = createThreads(complexNums, index);
	printf("Ans:%d+i%d\n",ans.real,ans.imaginary);
}
