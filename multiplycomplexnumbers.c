#include "complexnumbers.h"

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
	//printf("No Of threads:%d\n",noOfThreads);
	pthread_t tid[noOfThreads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	for(int i=0; i< noOfThreads; i++){
		if(pthread_create(&tid[i],&attr,runner1,&complexNums[i*2]) != 0){
			perror("Failed to create thread\n");
		}
	}
	int i = 0;
	
	nextNums = ( struct complex * ) malloc ((noOfThreads+1)* sizeof (struct complex));
	for(i=0; i< noOfThreads; i++) {

		if(noOfThreads == 1) {
			complexNum *res = malloc(sizeof(complexNum));
			if(index%2 == 1) {
				if(pthread_join(tid[0],(void**) &res) != 0){
					perror("Failed to join thread\n");
				}
				
				complexNum temp = complexNums[index-1];
				//printf("TEMP:%d+i%d\n",temp.real,temp.imaginary);
				complexNum ans;
				int resReal = res->real;
				int resImag = res->imaginary;
				int tempReal = temp.real;
				int tempImag = temp.imaginary;
				ans.real = resReal * tempReal - resImag * tempImag;
				ans.imaginary = resImag * tempReal + tempImag * resReal;
				*res = ans;
				return *res;
			}
			else {
				if(pthread_join(tid[0],(void**) &res) != 0){
					perror("Failed to join thread\n");
				}
				return *res;
			}
		}
		if(pthread_join(tid[i],(void**) &res) != 0){
			perror("Failed to create thread\n");
		}
		nextNums[i].real = res->real;
		nextNums[i].imaginary = res->imaginary;
		printf("Thread %d ans: %d+i%d\n",i,res->real,res->imaginary);
	}
	if(index % 2 == 1){
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
