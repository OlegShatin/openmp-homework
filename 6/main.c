// C Compiler flag:  -fopenmp
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 20

int main(int argc, char *argv[])
{	
	int threadsCount = omp_get_max_threads();
	printf("Threads count: %d\n", threadsCount);

	int a[10] = {5, 5, 5, 5, 5, 5, 6, 5, 5, 5};
	int b[10] = {5, 5, 5, 5, 5, 5, 5, 4, 1, 5};
	//printf("before first section: a: %d ; b: %d\n",a, b);
	int sumA = 0;
	int sumB = 0;
#pragma omp parallel for firstprivate(b, a) reduction(+:sumA,sumB)
	for (int i = 0; i < 10; i++)
	{
		sumA += a[i];
		sumB += b[i];
	}
	printf("in a avg:  %d\n", sumA / 10);
	printf("in b avg:  %d\n", sumB / 10);
	
	return 0;
}
