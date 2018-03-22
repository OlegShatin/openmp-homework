// C Compiler flag:  -fopenmp
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 20

int main(int argc, char *argv[])
{

	omp_set_dynamic(0); // запретить библиотеке openmp менять число потоков во время исполнения
	//omp_set_num_threads(2); // установить число потоков в X
	int threadsCount = omp_get_max_threads();
	printf("Threads count: %d\n", threadsCount);

	int d[6][8];

	for (int i = 0; i < 6; i++)
	{

		for (int j = 0; j < 8; j++)
		{
			d[i][j] = rand();
		}
	}

//printf("before first section: a: %d ; b: %d\n",a, b);
#pragma omp parallel sections num_threads(3) firstprivate(d)
	{
#pragma omp section
		{
			int sum = 0;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					sum += d[i][j];
				}
			}
			printf("in d avg:  %d\n", sum / (6 * 8));
		}
#pragma omp section
		{
			int min = d[0][0];
			int max = d[0][0];
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (min > d[i][j])
						min = d[i][j];
					if (max < d[i][j])
						max = d[i][j];
				}
			}
			printf("in d min:  %d; max: %d\n", min, max);
		}
#pragma omp section
		{
			int dividedOn3Count = 0;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (d[i][j] % 3 == 0)
						dividedOn3Count++;
				}
			}
			printf("in d mod 3 == 0 count:  %d\n", dividedOn3Count);
		}
	}

	return 0;
}
