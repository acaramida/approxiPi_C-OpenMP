#include "omp.h"
#include "stdio.h"
#include "stdlib.h"

double points = 0;
double sum = 0;

void* numbers_in(void *arg) {

	unsigned int seed = (unsigned int)omp_get_wtime();
	double p_in = 0;
	int *threads = (int*)arg;

	for( int i = 0; i < points/ *threads; i++ )
	{
			double x = ((double)rand_r(&seed) / RAND_MAX);
      double y = ((double)rand_r(&seed) / RAND_MAX);

			if(x * x + y * y <= 1) {
				p_in++;
			}
	}

	sum+=p_in;
}

void main( int argc, const char* argv[] )
{
	int threads = atof(argv[2]);
	points = atof(argv[1]);

  #pragma omp prallel num_threads(threads){
    int ID = omp_get_thread_num();

    printf(" hello (%d)\n", ID);
    printf(" points: %lf \n", points);
    printf(" points in: %lf \n", sum);
    printf(" PI estimation: %lf \n", sum/points * 4.0);
  }
}
