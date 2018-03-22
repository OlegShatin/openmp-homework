// C Compiler flag:  -fopenmp
#include <stdio.h>
#include <omp.h>

#define N 20

int main(int argc, char *argv[])
{

	omp_set_dynamic(0);		// запретить библиотеке openmp менять число потоков во время исполнения
	omp_set_num_threads(8); // установить число потоков в 2
	int threadsCount = omp_get_max_threads();
	omp_lock_t locks[threadsCount];
	omp_lock_t root;
	omp_init_lock(&root);
	for (int index = 0; index < threadsCount; index++)
	{
		omp_init_lock(&locks[index]);
	}
	printf("%d\n", threadsCount);

#pragma omp parallel
	{
		//printf("Hello, I'm thread number %d from %d\n", omp_get_thread_num(), omp_get_num_threads());

		omp_set_lock(&root);
		printf("Hello, I'm thread number %d from %d\n", omp_get_thread_num(), omp_get_num_threads());
		for (int i = 0; i < threadsCount; i++)
		{
			if (omp_test_lock(&locks[i]))
			{
				omp_unset_lock(&root);
				if (i < threadsCount - 1)
				{

					omp_set_lock(&locks[i]);
				}
				else
				{
					omp_unset_lock(&locks[i]);
				}
				printf("Hello, I'm thread number %d from %d\n", omp_get_thread_num(), omp_get_num_threads());

				if (i != 0)
				{
					omp_unset_lock(&locks[i - 1]);
				}

				break;
			}
		}
	}

	//dispose
	for (int index = 0; index < threadsCount; index++)
	{
		omp_destroy_lock(&locks[index]);
	}
	omp_destroy_lock(&root);
	
	return 0;
}
