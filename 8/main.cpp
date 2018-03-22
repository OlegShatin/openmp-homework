// C Compiler flag:  -fopenmp
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include "Math.h"
#define N 20

Vector multAsync(Vector vec, Matrix mtx)
{

	Vector result(mtx.rows);
	double start = omp_get_wtime();

	if (vec.size == mtx.columns)
	{
#pragma omp parallel for shared(mtx, vec, result)
		for (int m = 0; m < result.size; m++)
		{
			for (int n = 0; n < vec.size; n++)
			{
				result.arr[m] += mtx.arr[m][n] * vec.arr[n];
			}
			//printf("working %d of %d threads\n", omp_get_thread_num(), omp_get_num_threads());
		}
	}

	double end = omp_get_wtime();
	printf("async cycles time (sec): %f\n", end - start);
	return result;
};

Vector mult(Vector vec, Matrix mtx)
{
	Vector result(mtx.rows);
	double start = omp_get_wtime();

	if (vec.size == mtx.columns)
	{
		for (int m = 0; m < result.size; m++)
		{
			for (int n = 0; n < vec.size; n++)
			{
				result.arr[m] += mtx.arr[m][n] * vec.arr[n];
				//printf("%d", vec.arr[n]);
			}
			//printf("working %d of %d threads\n", omp_get_thread_num(), omp_get_num_threads());
			//printf("%d", result.arr[m]);
		}
	}

	double end = omp_get_wtime();
	printf("sync cycles time (sec): %f\n", end - start);
	return result;
};

int main(int argc, char *argv[])
{
	//init matrix
	Matrix matrix(10000, 10000);
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.columns; j++)
		{
			matrix.arr[i][j] = 1 * i;
			//printf("%d ", matrix.arr[i][j]);
		}
		//printf("\n");
	}
	//printf("\n");

	//init vector
	Vector vector(10000);
	for (int j = 0; j < vector.size; j++)
	{
		vector.arr[j] = 3 + j / 6;
		//printf("%d ", vector.arr[j]);
	}
	//printf("\n");

	//multiple
	Vector res = mult(vector, matrix);
	/*for (int i = 0; i < res.size; i++)
	{
		printf("%d ", res.arr[i]);
	}
	printf("\n");*/

	res = multAsync(vector, matrix);
	/*for (int i = 0; i < res.size; i++)
	{
		printf("%d ", res.arr[i]);
	}*/

	return 0;
}
