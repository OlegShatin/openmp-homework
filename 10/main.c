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

	int control_counter = 0;
	for (int i = 0; i < width; i++)
	{
		a[i] = rand();
		if (a[i] % 9 == 0)
		{
			control_counter++;
		}
	}
	printf("control counter is %d\n", control_counter);

	int counter = 0;
#pragma omp parallel for shared(counter)
	for (int i = 0; i < width; i++)
	{
		if (a[i] % 9 == 0)
		{
#pragma omp atomic
			counter++;
		}
	}
	printf("counter is %d\n", counter);

	if (control_counter == counter)
	{
		printf("the answer is correct\n");
	}
	return 0;
}
