#include<algorithm>
#include<iostream>
#include<vector>
#include<list>
#include<pthread.h>

#define NTHR 8
#define NUMNUM 8000000L
#define TNUM	(NUMNUM/NTHR) 


long num[NUMNUM];

pthread_barrier_t b;

std::vector<std::list<long>>vl;
std::vector<long>sv;

void * thf(void *arg){

	long idx = (long)arg;
//
//	heapsort
	std::list<long> v(idx,idx+TNUM-1);
	std::make_heap(v.begin(),v.end());
	std::sort_heap(v.begin(),v.end());
	vl.push_back(v);
	pthread_barrier_wait(&b);

	return (void*)(0);
}

void data_init(){
	srandom(1);	
	for(int i=0;i<NUMNUM;i++){
		num[i] = random();
	}

}

void merge(){
	for(int i=0;i<vl.size();i++){
	//	std::vector<long> v = vl[i].

	}
}
int main(){

	// pthread create 
	pthread_t tid;
	data_init();
	pthread_barrier_init(&b,NULL,NTHR+1);
	for(int i=0;i<NTHR;i++){
		long idx =i*TNUM;
		pthread_create(&tid,NULL,thf,(void*)idx);
	}	
	pthread_barrier_wait(&b);
	std::cout<<"----barrier line-----"<<"\n";
	std::cout<<vl.size()<<"\n";
	// wait
	//
	// merge
	//
	//show comsumed time
	return 0;
}

