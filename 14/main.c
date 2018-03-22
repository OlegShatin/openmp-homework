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
	int n = 210;
	int control_sqr = n * n;
	printf("control sqr is %d\n", control_sqr);

	int sqr = 0;
	int max = n * 2 + 1;
#pragma omp parallel for reduction(+:sqr)
	for (int i = 1; i < max; i += 2)
	{		
		sqr += i;
	}
	printf("sqr is %d\n", sqr);

	if (control_sqr == sqr)
	{
		printf("the answer is correct\n");
	}
	return 0;
}
