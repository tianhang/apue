#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
#include<list>
#include<pthread.h>
#include<limits.h>

#define NTHR 8
#define NUMNUM 800L
#define TNUM	(NUMNUM/NTHR) 


long num[NUMNUM];

pthread_barrier_t b;

std::vector<std::vector<long>>vl;
std::vector<long>sv;

void * thf(void *arg){

	long idx = (long)arg;
//
//	heapsort
	std::vector<long> v(idx,idx+TNUM-1);
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
	int idx_arr[TNUM];
	memset(&idx_arr,0,sizeof(idx_arr));
	long min_n = LONG_MAX; 
	int cnt =0;
	while(cnt < TNUM){
	
		for(int i=0;i<vl.size();i++){
		//	std::vector<long> v = vl[i].
			int val = vl[i][idx_arr[i]]; 
	//	long min_n = LONG_MAX; 
			std::cout<<val<<"\n";
			if(val < min_n){
				sv.push_back(val);	
				min_n = val;
				idx_arr[i]++;
				std::cout<<val<<"\n";
				if(idx_arr[i] == NUMNUM) cnt++;
			}
		}
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
	merge();
	std::cout<<sv.size()<<"\n";
	// wait
	//
	// merge
	//
	//show comsumed time
	return 0;
}

