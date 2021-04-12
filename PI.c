#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

	int flags, threads;
	double num_steps;

	flags = 0;
	threads = 1;
	num_steps = 1000;

	int option;
	while ((option = getopt(argc, argv, "p:t:b")) != -1)
	{ //get option from the getopt() method
		switch (option)
		{
		case 'p':
			num_steps = atof(optarg);
			break;
		case 't':
			threads = atoi(optarg);
			break;
		case 'b':
			flags = 1;
			break;
		case '?': //used for some unknown options
			printf("unknown option: %c\n", optopt);
			break;
		}
	}

	double pi, sum = 0.0;
	double step = 1.0 / num_steps;

#pragma omp parallel num_threads(threads) reduction(+:sum)
	{
		double x = 0.0;
#pragma omp for
		for (long i = 0; i < (long)num_steps; i++)
		{
			x = (i+0.5)*step;
			sum += 4.0/(1.0 + x*x);
			
		}		
		
	}
	
	pi = step * sum;

	clock_gettime(CLOCK_MONOTONIC, &end);
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e9;
	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

	if (flags == 1)
	{
		printf("%.lf\t%d\t%.3lf\n", num_steps, threads, time_taken);
	}
	else
	{
		printf("Total number of num_steps: %.1e \n", num_steps);
		printf("PI estimation: %.24lf \n", pi);
		printf("Execution time (s): %.3lf \n", time_taken);
	}
	
	return 0;
}
