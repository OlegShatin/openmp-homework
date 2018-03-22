// C Compiler flag:  -fopenmp
#include <stdio.h>
#include <omp.h>

#define N 20

int main(int argc, char *argv[])
{

	
	omp_set_dynamic(0);		// запретить библиотеке openmp менять число потоков во время исполнения

	//omp_set_num_threads(2); // установить число потоков в X
	int threadsCount = omp_get_max_threads();
	printf("Threads count: %d\n",threadsCount);

	int a = 0;
	int b = 0;
	printf("before first section: a: %d ; b: %d\n",a, b);
    #pragma omp parallel private(a) firstprivate(b) num_threads(2)
	{
		int myid = omp_get_thread_num();
		a += myid;
		b += myid;
		printf("in first parallel section: a: %d ; b: %d\n",a, b);
		
	}
	printf("after first section: a: %d ; b: %d\n",a, b);

	#pragma omp parallel shared(a) private(b) num_threads(4)
	{
		int myid = omp_get_thread_num();
		a -= myid;
		b -= myid;
		printf("in second parallel section: a: %d ; b: %d\n",a, b);
		
	}
	printf("after second section: a: %d ; b: %d\n",a, b);

	return 0;
}
