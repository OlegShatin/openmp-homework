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
	int inv_powers[width];

	int control_sum = 0;
	int control_power = 1;
	for (int i = width - 1; i > -1; i--)
	{

		a[i] = rand() % 2;
		control_sum += control_power * a[i];
		inv_powers[i] = control_power;
		control_power * 2;
	}

	printf("control sum is %d\n", control_sum);

	int sum = 0;
#pragma omp parallel for reduction(+:sum)
	for (int i = width - 1; i > -1; i--)
	{		
		sum += inv_powers[i] * a[i];
	}
	printf("sum is %d\n", sum);

	if (control_sum == sum)
	{
		printf("the answer is correct\n");
	}
	return 0;
}
