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
#define FIB_IDX 10

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
size_t tabulation_fib(size_t n)
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
size_t recursive_fib(size_t n) {
	if (n == 0 || n == 1) {
		return 1;
	} else {
		return recursive_fib(n-1) + recursive_fib(n-2);
	}
}

// Dynamic Programming - Memoization - Top Down recursion and caching
size_t memoization_fib(size_t n)
{

	if (lookup[n] == NIL){
		if (n == 0 || n == 1)
			return 1;
		else
			lookup[n] = memoization_fib(n - 1) + memoization_fib(n - 2);
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
	double recursive_time, tabulation_time, memoization_time;
	double percentage_change;
	time_t t;
	srand((unsigned) time(&t));

	recursive_time = get_fibonacci_time(recursive_fib, FIB_IDX);
	printf("recursive_fib(%d) took %f seconds to execute \n\n", FIB_IDX, recursive_time);

	tabulation_time = get_fibonacci_time(tabulation_fib, FIB_IDX);
	printf("tabulation_fib(%d) took %f seconds to execute \n\n", FIB_IDX, tabulation_time);

	initialize();
	memoization_time = get_fibonacci_time(memoization_fib, FIB_IDX);
	printf("memoization_fib(%d) took %f seconds to execute \n\n", FIB_IDX, memoization_time);

	percentage_change = calculate_percentage_difference(recursive_time, tabulation_time);
	printf("[+] recursion -> tabulation ~= %.0f%% %s\n", percentage_change, (percentage_change < 0 ? "slower" : "faster"));

	percentage_change = calculate_percentage_difference(recursive_time, memoization_time);
	printf("[+] recursion -> memoization ~= %.0f%% %s\n", percentage_change, (percentage_change < 0 ? "slower" : "faster"));

	percentage_change = calculate_percentage_difference(memoization_time, tabulation_time);
	printf("[+] memoization -> tabulation ~= %.0f%% %s\n", percentage_change, (percentage_change < 0 ? "slower" : "faster"));

	return 0;
}
