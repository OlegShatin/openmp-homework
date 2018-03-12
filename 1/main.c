// C Compiler flag:  -fopenmp
#include <stdio.h>
#include <omp.h>

#define N 20

int main(int argc, char *argv[])
{

	int i, myid;
	omp_set_dynamic(0);		// запретить библиотеке openmp менять число потоков во время исполнения
	omp_set_num_threads(8); // установить число потоков в 2

#pragma omp parallel private(myid)
	{
		myid = omp_get_thread_num();
		int threadsCount = omp_get_num_threads();
		printf("Hello, I'm thread number %d from %d\n", myid, threadsCount);
		
	}

	return 0;
}
