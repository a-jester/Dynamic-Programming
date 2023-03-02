/**
 * Memoization Demo
 * 
 * @author Alex M. Jester
 * @date 01/20/2021
 * 
 * @version 1.1.0
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NIL -1
#define MAX 1000000
#define FIB_IDX 50
#define FIB_LARGE 100

long long lookup[MAX];

int calculate_percentage_difference(double timeA, double timeB)
{
	/*
	 *    |V1−V2|
	 *  ----------- x 100 = percentage difference
	 *  [(V1+V2)/2]
	 * 
	 */
	return ((timeA - timeB) / ((timeA + timeB) / 2)) * 100;
}

double get_fibonacci_time(size_t (*fib_ptr)(size_t), size_t index)
{
	clock_t start, end;
	start = clock();
	printf("Fibonacci sequence at index %ld = %ld\n", index, fib_ptr(index));
	end = clock();
	return ((double) (end - start)) / CLOCKS_PER_SEC;
}

// Dynamic Programming - Tabulation
size_t arr_fib(size_t n)
{
	size_t *arr = (size_t *)calloc(n+1, sizeof(size_t));
	size_t ans;
	arr[0] = 1;
	arr[1] = 1;

	for (int i = 2; i <= n; i++) {
		arr[i] = arr[i - 1] + arr[i - 2];
	}
	ans = arr[n];
	free(arr);
	return ans;
}

// Recursive - exponential
size_t naive_fib(size_t n) {
	if (n == 0 || n == 1) {
		return 1;
	} else {
		return naive_fib(n-1) + naive_fib(n-2);
	}
}

// Dynamic Programming - Memoization - Top Down recursion and caching
size_t memo_fib(size_t n)
{

	if (lookup[n] == NIL){
		if (n == 0 || n == 1)
			return 1;
		else
			lookup[n] = memo_fib(n - 1) + memo_fib(n - 2);
	}
	return lookup[n];
}

void initialize()
{
	int i;
	for (i = 0; i < MAX; i++)
		lookup[i] = NIL;
}

int main(void)
{
	double naive_time, arr_time, memo_time;
	double percentage_change;
	time_t t;
	srand((unsigned) time(&t));

	naive_time = get_fibonacci_time(naive_fib, FIB_IDX);
	printf("naive_fib(%d) took %f seconds to execute \n\n", FIB_IDX, naive_time);

	arr_time = get_fibonacci_time(arr_fib, FIB_IDX);
	printf("arr_fib(%d) took %f seconds to execute \n\n", FIB_IDX, arr_time);

	initialize();
	memo_time = get_fibonacci_time(memo_fib, FIB_IDX);
	printf("memo_fib(%d) took %f seconds to execute \n\n", FIB_IDX, memo_time);

	percentage_change = calculate_percentage_difference(naive_time, arr_time);
	printf("[+] naive -> array ~= %.0f%% %s\n", percentage_change, (percentage_change < 0 ? "slower" : "faster"));

	percentage_change = calculate_percentage_difference(naive_time, memo_time);
	printf("[+] naive -> memo ~= %.0f%% %s\n", percentage_change, (percentage_change < 0 ? "slower" : "faster"));

	percentage_change = calculate_percentage_difference(arr_time, memo_time);
	printf("[+] array -> memo ~= %.0f%% %s\n", percentage_change, (percentage_change < 0 ? "slower" : "faster"));

	return 0;
}
