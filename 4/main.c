// C Compiler flag:  -fopenmp
#include <stdio.h>
#include <omp.h>

#define N 20

int main(int argc, char *argv[])
{

	omp_set_dynamic(0); // запретить библиотеке openmp менять число потоков во время исполнения

	//omp_set_num_threads(2); // установить число потоков в X
	int threadsCount = omp_get_max_threads();
	printf("Threads count: %d\n", threadsCount);

	int a[10] = {5, 5, 5, 5, 5, 5, 6, 5, 5, 5};
	int b[10] = {5, 5, 5, 5, 5, 5, 5, 4, 1, 5};
//printf("before first section: a: %d ; b: %d\n",a, b);
#pragma omp parallel sections num_threads(2) firstprivate(b, a)
	{
#pragma omp section 
		{
			int max = a[0];
			for (int i = 1; i < 10; i++)
			{
				if (max < a[i])
					max = a[i];
			}
			printf("in a max:  %d\n", max);
		}
#pragma omp section 
		{
			int min = b[0];
			for (int i = 1; i < 10; i++)
			{
				
				if (min > b[i]) 				
					min = b[i];
				
			}
			printf("in b min:  %d\n", min);
		}
	}

	return 0;
}
