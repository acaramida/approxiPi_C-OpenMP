#include  <stdio.h>
#include  <omp.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int threads = atoi(argv[2]);
  double points = atof(argv[1]);
	long points_per_thread = points/threads;
	double sum = 0.0;

  #pragma omp parallel num_threads(threads)
  {
		unsigned int seed = (unsigned int)omp_get_wtime();
		double p_in = 0;

		for( int i = 0; i < points_per_thread; i++ )
		{
				double x = ((double)rand_r(&seed) / RAND_MAX);
		      		double y = ((double)rand_r(&seed) / RAND_MAX);

				if(x * x + y * y <= 1) {
					p_in++;
				}
		}
		#pragma omp atomic
	  	sum += p_in;
  }

  printf(" points: %.10e \n", points);
  printf(" points in: %.10e \n", sum);
  printf(" PI estimation: %lf \n", sum/points * 4.0);
}
