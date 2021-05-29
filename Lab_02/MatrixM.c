/* Diana Palafox
	CSE 179
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>
#include <vector>
#include <stdlib.H>

/* this is where we can change our threads*/
#define THREADS 4

/* calcultions are done */
void gemm(double *A, double *x, double *b, int n){
	int i, j,k;
		for (i= 0; i<n; i++){
			for(j=0; j<n; j++){
				double dot = 0;
					for(k=0; k<n; k++){
		dot += A[i*n+k]*x[k*n+j];
	}
	b[i*n+j] = dot;
	}
	}
	}

/* here the function was created using the api output*/

void gemm_omp(double *A, double *x, double *b, int n){

	
	/*for 3.1 question 3*/
	//#pragma omp parallel 
	
	/* for 3.2 question */
	//#pragma omp parallel for schedule(static) num_threads(THREADS)
	#pragma omp parallel for schedule(dynamic) num_threads(THREADS)
	
	
	{
	
		int i, j, k;
			for(i=0;i <n ; i++){
				#pragma omp for
				for (j =0; j<n ; j++){
					double dot = 0;
					for (k = 0; k<n; k++){
						dot += A[i*n+k]*x[k*n+j];

					}
					b[i*n+j] = dot;
				}
			}
	}
}

int main(){
	int i,n;
	double *A,*x,*b,dtime;

	n=512;
	A= (double*)malloc(sizeof(double)*n*n);
	x = (double*)malloc(sizeof(double)*n*n);
	b = (double*)malloc(sizeof(double)*n*n);
	for(i=0; i<n*n; i++) {A[i]=rand()/RAND_MAX; x[i] = rand()/RAND_MAX;}
	
	struct timeval start, end;
	gettimeofday(&start,NULL);
	gemm(A,x,b,n);
	gettimeofday(&end,NULL);
	printf("Serial code takes %ld micro seconds! \n",((end.tv_sec* 1000000 + end.tv_usec)-(start.tv_sec*10000000 + start.tv_usec)));

	gettimeofday(&start,NULL);
	gemm_omp(A,x,b,n);
	gettimeofday(&end,NULL);
	printf("OpenMp code takes %ld micro seconds! \n",((end.tv_sec*1000000 + end.tv_usec)-(start.tv_sec * 1000000 + start.tv_usec)));

	return 0;
}
