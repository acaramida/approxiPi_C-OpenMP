#include  <stdio.h>
#include <stdlib.h>
#include  <omp.h>

int main(int argc, char *argv[])
{
  double num_steps = atof(argv[1]);
  double sum = 0.0;

  unsigned int seed = omp_get_wtime();

  for (int i = 0; i < num_steps; i++) {
      double x = ((double)rand_r(&seed) / RAND_MAX);
      double y = ((double)rand_r(&seed) / RAND_MAX);

      if((1-x)*(1-x) + (1-y)*(1-y) <= 1) {
        sum++;
      }
  }

  printf(" points: %lf \n", num_steps);
  printf(" points in: %lf \n", sum);
  printf(" PI estimation: %lf \n", sum/num_steps * 4.0);

}
