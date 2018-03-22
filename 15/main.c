// C Compiler flag:  -fopenmp
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define N 20

int main(int argc, char *argv[])
{

	int limit = 1000000;
	int start = 999900;
	int sqr_lim;
	bool is_prime[limit + 1];
	int x2, y2;
	int i, j;
	int n;

	// Инициализация решета
	sqr_lim = (int)sqrt((long double)limit);
	for (i = 0; i <= limit; i++)
		is_prime[i] = false;
	is_prime[2] = true;
	is_prime[3] = true;

	// Предположительно простые — это целые с нечётным числом
	// представлений в данных квадратных формах.
	// x2 и y2 — это квадраты i и j (оптимизация).
	x2 = 0;
	#pragma omp parallel for private(n)
	for (i = 1; i <= sqr_lim; i++)
	{
		x2 += 2 * i - 1;
		y2 = 0;
		for (j = 1; j <= sqr_lim; j++)
		{
			y2 += 2 * j - 1;

			n = 4 * x2 + y2;
			if ((n <= limit) && (n % 12 == 1 || n % 12 == 5))
				is_prime[n] = !is_prime[n];

			// n = 3 * x2 + y2;
			n -= x2; // Оптимизация
			if ((n <= limit) && (n % 12 == 7))
				is_prime[n] = !is_prime[n];

			// n = 3 * x2 - y2;
			n -= 2 * y2; // Оптимизация
			if ((i > j) && (n <= limit) && (n % 12 == 11))
				is_prime[n] = !is_prime[n];
		}
	}

	// Отсеиваем кратные квадратам простых чисел в интервале [5, sqrt(limit)].
	// (основной этап не может их отсеять)
	for (i = 5; i <= sqr_lim; i++)
	{
		if (is_prime[i])
		{
			n = i * i;
			for (j = n; j <= limit; j += n)
			{
				is_prime[j] = false;
			}
		}
	}

	// Вывод списка простых чисел в консоль.
	if (start < 2)
		printf("2, ");
		if (start < 3)
		printf("3, ");
	if (start < 5)
		printf("5");
	
	
	for (i = start; i <= limit; i++)
	{ // добавлена проверка делимости на 3 и 5. В оригинальной версии алгоритма потребности в ней нет.
		if ((is_prime[i]) && (i % 3 != 0) && (i % 5 != 0))
		{
			printf(", %d", i);
		}
	}

	return 0;
}
