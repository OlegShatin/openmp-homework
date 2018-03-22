// C Compiler flag:  -fopenmp
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define N 20

int main(int argc, char *argv[])
{

	srand(time(NULL));
	omp_set_dynamic(0); // запретить библиотеке openmp менять число потоков во время исполнения
	//omp_set_num_threads(2); // установить число потоков в X
	int threadsCount = omp_get_max_threads();
	int width = 30;
	int a[width];
	int param = 9;
	int control_max = a[0];
	for (int i = 0; i < width; i++)
	{
		a[i] = rand();
		if (a[i] % param == 0)
		{
			control_max = a[i];
		}
	}
	printf("control max is %d\n", control_max);

	int max = 0;
#pragma omp parallel for shared (max)
	for (int i = 0; i < width; i++)
	{
		if (a[i] % param == 0)
		{
#pragma omp critical
			{
				max = a[i];
			}
		}
	}
	printf("max is %d\n", max);

	if (control_max == max)
	{
		printf("the answer is correct\n");
	}
	return 0;
}
