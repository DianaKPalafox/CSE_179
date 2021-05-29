#include <iostream>

#include "omp.h"

int main() {
	   int nthreads, tid;

	#pragma omp parallel private(nthreads, tid)

    {
	tid = omp_get_thread_num();

	std::cout<<"thread_id is:"<<tid<<"hello world\n";
	if(tid == 0){    

		nthreads = omp_get_num_threads();
		std::cout<<"total number of threads is"<<nthreads<<"thread!:\n";
		}
	}   
 return 0;
    }
