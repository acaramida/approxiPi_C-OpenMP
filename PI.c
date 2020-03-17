#include  <stdio.h>
#include  <omp.h>

int main(int argc, char *argv[])
{
  #pragma omp parallel
  {
    int ID = 0;
    printf(" hello(%d) ", ID);
    printf(" world(%d) \n", ID);
  }
}
