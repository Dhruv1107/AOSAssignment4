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
	//printf("optional:%d\n",optional.real);
	complexNum *res,*nextNums,lastCno;
	//free(complexNums);
	//res = ( struct complex * ) malloc(sizeof(struct complex));
	int noOfThreads = index/2;
	pthread_t tid[noOfThreads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	int test = 0;
	if(index % 2 == 1){
		//lastCno = ( struct complex * ) malloc(sizeof(struct complex));
		lastCno = complexNums[index-1];
		printf("Last CNO:%d+i%d\n",lastCno.real,lastCno.imaginary);
		test = 1;
		
	}
	//printf("No of threads:%d\n",noOfThreads);
	for(int i=0; i< noOfThreads; i++){
		if(pthread_create(&tid[i],&attr,runner1,&complexNums[i*2]) != 0){
			perror("Failed to create thread\n");
		}
	}
	int i = 0;
	//free(complexNums);
	/*if(optional.real){
		if(noOfThreads == 1){
			nextNums = ( struct complex * ) malloc ((noOfThreads+1)* sizeof (struct complex));
			if(pthread_join(tid[0],(void**) &res) != 0){
				perror("Failed to create thread\n");
			}
			nextNums[i].real = res->real;
			nextNums[i].imaginary = res->imaginary;
			i++;
			nextNums[i] = optional;
			sleep(30);
			createThreads(nextNums,i,optional);
			
			//return;
		}
	}*/
	if(noOfThreads == 1){
		complexNum *res = malloc(sizeof(complexNum));
		if(pthread_join(tid[0],(void**) &res) != 0){
			perror("Failed to create thread\n");
		}
		//printf("Last CNO:%d+i%d\n",lastCno.real,lastCno.imaginary);
		//printf("Res:%d+i%d\n",res->real,res->imaginary);
		if(test){
			test = 0;
			complexNum ans;
			int resReal = res->real;
			int resImag = res->imaginary;
			int lastReal = lastCno.real;
			int lastImag = lastCno.imaginary;
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
