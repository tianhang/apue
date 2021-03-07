#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
#include<list>
#include<pthread.h>
#include<limits.h>

#define NTHR 8
#define NUMNUM 80L
#define TNUM	(NUMNUM/NTHR) 

pthread_mutex_t LOCK = PTHREAD_MUTEX_INITIALIZER;

long num[NUMNUM];

pthread_barrier_t b;

std::vector<std::vector<long>>vl;
std::vector<long>sv;

void * thf(void *arg){

	long idx = (long)arg;
//	std::cout<<"idx arg :"<<idx<<"\n";
//
//	heapsort
	std::vector<long> v(num+idx,num+idx+TNUM);
	std::make_heap(v.begin(),v.end());
	std::sort_heap(v.begin(),v.end());


	pthread_mutex_lock(&LOCK);
	vl.push_back(v);
	pthread_mutex_unlock(&LOCK);

	//std::cout<<"v size :"<<v.size()<<"\n";

	pthread_barrier_wait(&b);
	//std::cout<<vl.size()<<"\n";

	return (void*)(0);
}

void data_init(){
	srandom(1);	
	for(int i=0;i<NUMNUM;i++){
		num[i] = random();
	}

}

void merge(){
	int idx_arr[NTHR];
	memset(&idx_arr,0,sizeof(idx_arr));
	int cnt =0;
	while(cnt < NTHR){
			
		long min_n = LONG_MAX; 
		int min_n_idx = -1 ;
		std::cout<<"cnt:"<<cnt<<"\n";
		for(int i=0;i<vl.size();i++){
		//	std::vector<long> v = vl[i].
			if(idx_arr[i] == TNUM) continue;
			long val = vl[i][idx_arr[i]]; 
		//	long min_n = LONG_MAX; 
		//	std::cout<<val<<"\n";
			if(val < min_n){
				min_n = val;
				min_n_idx = i;
			}
		}



		if(idx_arr[min_n_idx] == TNUM-1){

			cnt++;
		}

		idx_arr[min_n_idx]++;

		std::cout<<min_n<<" - min n \n";
			
		sv.push_back(min_n);	
		
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
	std::cout<<"sv size :"<<sv.size()<<"\n";
	// wait
	//
	// merge
	//
	//show comsumed time
	return 0;
}

