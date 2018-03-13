// C Compiler flag:  -fopenmp
#include <stdio.h>
#include <omp.h>

#define N 20

int main(int argc, char *argv[])
{

	int  myid;
	omp_set_dynamic(0);		// запретить библиотеке openmp менять число потоков во время исполнения

	omp_set_num_threads(6); // установить число потоков в 2
	int threadsCount = omp_get_max_threads();
	printf("%d\n",threadsCount);
    #pragma omp parallel if(threadsCount > 1) private(myid, threadsCount)
	{
		myid = omp_get_thread_num();
		threadsCount = omp_get_num_threads();
		printf("Hello, It's parallel and I'm thread number %d from %d\n", myid, threadsCount);
		
	}

	omp_set_num_threads(1);
	threadsCount = omp_get_max_threads();
	#pragma omp parallel if(omp_get_num_threads() > 1) private(myid, threadsCount)
	{
		myid = omp_get_thread_num();
		threadsCount = omp_get_num_threads();
		printf("Hello, it's sequence and I'm thread number %d from %d\n", myid, threadsCount);
		
	}

	return 0;
}
