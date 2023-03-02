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

double get_fibonacci_time(size_t (*fib_ptr)(size_t), size_t index)
{
	clock_t start, end;
	start = clock();
	printf("Fibonacci sequence at index %ld = %ld\n", index, fib_ptr(index));
	end = clock();
	return ((double) (end - start)) / CLOCKS_PER_SEC;
}

// Dynamic
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

size_t naive_fib(size_t n) {
	if (n == 0 || n == 1) {
		return 1;
	} else {
		return naive_fib(n-1) + naive_fib(n-2);
	}
}

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
	double total_time;
	time_t t;
	srand((unsigned) time(&t));

	total_time = get_fibonacci_time(naive_fib, FIB_IDX);
	printf("naive_fib(%d) took %f seconds to execute \n\n", FIB_IDX, total_time);

	total_time = get_fibonacci_time(arr_fib, FIB_IDX);
	printf("arr_fib(%d) took %f seconds to execute \n\n", FIB_IDX, total_time);

	initialize();
	total_time = get_fibonacci_time(memo_fib, FIB_IDX);
	printf("memo_fib(%d) took %f seconds to execute \n\n", FIB_IDX, total_time);

	return 0;
}
