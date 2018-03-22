// C Compiler flag:  -fopenmp
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 20

int main(int argc, char *argv[])
{
	int threadsCount = omp_get_max_threads();
	printf("Threads count: %d\n", threadsCount);

	int length = 12;
	int a[length];
	int b[length];
	int c[length];
	;
	//printf("before first section: a: %d ; b: %d\n",a, b);

#pragma omp parallel for schedule(static, 4) num_threads(3)
	for (int i = 0; i < length; i++)
	{
		a[i] = i * 10;
		b[i] = i * 20;
		printf("working %d of %d threads\n", omp_get_thread_num(), omp_get_num_threads());
	}

	for (int i = 0; i < length; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	for (int i = 0; i < length; i++)
	{
		printf("%d ", b[i]);
	}
	printf("\n");

#pragma omp parallel for schedule(dynamic, 2) num_threads(4)
	for (int i = 0; i < length; i++)
	{
		c[i] = a[i] + b[i];
		printf("working %d of %d threads\n", omp_get_thread_num(), omp_get_num_threads());
	}

	for (int i = 0; i < length; i++)
	{
		printf("%d ", c[i]);
	}
	printf("\n");

	return 0;
}
