#include "complexnumbers.h"

complexNum result;

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

void *runner2(void *param) {
	complexNum cn1 = *(complexNum *)param;
	complexNum cn2 = result;
	complexNum *res = malloc(sizeof(complexNum));
	complexNum ans;
	ans.real = cn1.real * cn2.real - cn1.imaginary * cn2.imaginary;
	ans.imaginary = cn1.real * cn2.imaginary + cn2.real * cn1.imaginary;
	*res = ans;
	return (void*) res;
}

complexNum createThreads(complexNum *complexNums, int index) {
	complexNum *res,*nextNums;
	int noOfThreads = index/2;
	pthread_t tid[noOfThreads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	for(int i=0; i< noOfThreads; i++) {
		if(pthread_create(&tid[i],&attr,runner1,&complexNums[i*2]) != 0)
			perror("Failed to create thread\n");
	}
	int i = 0;
	
	nextNums = ( struct complex * ) malloc ((noOfThreads+1)* sizeof (struct complex));
	pthread_t tempTid;
	for(i=0; i< noOfThreads; i++) {

		if(noOfThreads == 1) {
			complexNum *res = malloc(sizeof(complexNum));
			
			if(index%2 == 1) {
			complexNum *res1 = malloc(sizeof(complexNum));
				if(pthread_join(tid[0],(void**) &res) != 0) 
					perror("Failed to join thread\n");
				result = *res;
				pthread_create(&tempTid,&attr,runner2,&complexNums[index - 1]);
				pthread_join(tempTid,(void**) &res1);
				printf("Thread 0 ans: %d+i%d\n",res1->real,res1->imaginary);
				return *res1;
			}
			
			else {
				if(pthread_join(tid[0],(void**) &res) != 0)
					perror("Failed to join thread\n");
				printf("Thread 0 ans: %d+i%d\n",res->real,res->imaginary);
				return *res;
			}
		}
		if(pthread_join(tid[i],(void**) &res) != 0)
			perror("Failed to create thread\n");
		nextNums[i].real = res->real;
		nextNums[i].imaginary = res->imaginary;
		printf("Thread %d ans: %d+i%d\n",i,res->real,res->imaginary);
	}
	if(index % 2 == 1) {
		nextNums[i].real = complexNums[index-1].real;
		nextNums[i].imaginary = complexNums[index-1].imaginary;
		i++;
	}
	createThreads(nextNums,i);
}

void multiplyComplexNumbers(complexNum *complexNums, int index) {
	complexNum ans = createThreads(complexNums, index);
	printf("Ans:%d+i%d\n",ans.real,ans.imaginary);
}
