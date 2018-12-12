#include <stdlib.h>
#include <stdio.h>

// export OMP_NUM_THREADS=4 && time ./a.out

#include <omp.h>

static long steps = 500000000;
// static long steps = 50000000;
// static long steps = 50000;

double step;

int main() {
	int i,j;
    double x, tmp=0.0;
    double pi, sum = 0.0;
    double start;

    step = 1.0/(double) steps;

    int choice = 0;
    printf("Enter your choice : ");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            #pragma omp parallel for reduction(+:sum) private(x)
            for (i=0; i < steps; i++) {
                x = (i+0.5)*step;
                sum += 4.0 / (1.0+x*x); 
            }
            pi = step * sum;
            printf("PI = %.16g \n", pi);
            break;
        case 2:
            #pragma omp parallel shared(sum) private(tmp)
            {
                #pragma omp for private(x)
                for (i=0; i < steps; i++) {
                    x = (i+0.5)*step;
                    tmp += 4.0 / (1.0+x*x); 
                }
                #pragma omp atomic
                sum += tmp;
            }
            pi = step * sum;
            printf("PI = %.16g \n", pi);
            break;
        default:
            printf("Error choice!");
    }
    return 0;
}