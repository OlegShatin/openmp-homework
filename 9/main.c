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
	int width = 8;
	int height = 6;
	int d[height][width];

	for (int i = 0; i < height; i++)
	{

		for (int j = 0; j < width; j++)
		{
			d[i][j] = rand();
		}
	}

	//printf("before first section: a: %d ; b: %d\n",a, b);

	int min = d[0][0];
	int max = d[0][0];

//sync check
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (min > d[i][j])
			{

				min = d[i][j];
			}

			if (max < d[i][j])
			{

				max = d[i][j];
			}
		}
	}
	printf("sync in d min:  %d; max: %d\n", min, max);

	//parallel
	min = d[0][0];
	max = d[0][0];

#pragma omp parallel for num_threads(4)
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (min > d[i][j])
			{
#pragma omp critical(to_min)
				min = d[i][j];
			}

			if (max < d[i][j])
			{
#pragma omp critical(to_max)
				max = d[i][j];
			}
		}
	}
	printf("in d min:  %d; max: %d\n", min, max);

	return 0;
}
