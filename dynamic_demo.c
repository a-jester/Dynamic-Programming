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

#include <math.h>

#define NIL -1
#define MAX 1000000

long long lookup[MAX];

int calculate_percentage_change(double initial, double final)
{
	/*
	 *    V2-V1
	 *  ----------- x 100 = percentage change
	 *     |V1|
	 * 
	 */
	return ((final - initial) / initial) * 100;
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
	arr[0] = 0;
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
	if (n == 0)
		return 0;
	else if (n == 1 || n == 2)
		return 1;
	else
		return recursive_fib(n-1) + recursive_fib(n-2);
}

// Dynamic Programming - Memoization - Top Down recursion and caching
size_t memoization_fib(size_t n)
{

	if (lookup[n] == NIL) {
		if (n == 0)
			return 0;
		else if (n == 0 || n == 1 || n == 2) 
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

void usage()
{
	puts("$ ./dynamic_demo <fibonacci index>");
}

int main(int argc, char *argv[])
{

	if (argc != 2) {
		usage();
		return -1;
	}

	char *endptr = NULL;

	size_t fib_index = strtol(argv[1], &endptr, 10);
	if (endptr == argv[1]) {
		usage();
		return -1;
	}

	double recursive_time, tabulation_time, memoization_time;
	double percentage_change;
	time_t t;
	srand((unsigned) time(&t));

	recursive_time = get_fibonacci_time(recursive_fib, fib_index);
	printf("recursive_fib(%ld) took %f seconds to execute \n\n", fib_index, recursive_time);

	tabulation_time = get_fibonacci_time(tabulation_fib, fib_index);
	printf("tabulation_fib(%ld) took %f seconds to execute \n\n", fib_index, tabulation_time);

	initialize();
	memoization_time = get_fibonacci_time(memoization_fib, fib_index);
	printf("memoization_fib(%ld) took %f seconds to execute \n\n", fib_index, memoization_time);

	percentage_change = calculate_percentage_change(recursive_time, tabulation_time);
	printf("[+] recursion   -> tabulation  ~= %d%% %s\n", abs(percentage_change), (percentage_change > 0 ? "slower" : "faster"));

	percentage_change = calculate_percentage_change(recursive_time, memoization_time);
	printf("[+] recursion   -> memoization ~= %d%% %s\n", abs(percentage_change), (percentage_change > 0 ? "slower" : "faster"));

	percentage_change = calculate_percentage_change(memoization_time, tabulation_time);
	printf("[+] memoization -> tabulation  ~= %d%% %s\n", abs(percentage_change), (percentage_change > 0 ? "slower" : "faster"));

	return 0;
}
