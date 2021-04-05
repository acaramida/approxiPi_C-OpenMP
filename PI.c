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
	double points;

	flags = 0;
	threads = 1;
	points = 0;

	int option;
	while ((option = getopt(argc, argv, "p:t:b")) != -1)
	{ //get option from the getopt() method
		switch (option)
		{
		case 'p':
			points = atof(optarg);
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

	long points_per_thread = points / threads;
	long sum = 0;

#pragma omp parallel num_threads(threads)
	{
		unsigned int seed = (unsigned int)omp_get_wtime();
		double p_in = 0;

		for (int i = 0; i < points_per_thread; i++)
		{
			double x = ((double)rand_r(&seed) / RAND_MAX);
			double y = ((double)rand_r(&seed) / RAND_MAX);

			if (x * x + y * y <= 1)
			{
				p_in++;
			}
		}
#pragma omp atomic
		sum += p_in;
	}

	clock_gettime(CLOCK_MONOTONIC, &end);
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e9;
	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

	if (flags == 1)
	{
		printf("%.lf\t%d\t%.3lf\n", points, threads, time_taken);
	}
	else
	{
		printf("Total number of points: %.1e \n", points);
		printf("Points within circle: %.1e \n", (double)sum);
		printf("PI estimation: %0.8lf \n", (double)sum / points * 4.0);
		printf("Execution time (s): %.3lf \n", time_taken);
	}
	
	return 0;
}
