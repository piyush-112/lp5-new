#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 1000

int main() {
    int array[ARRAY_SIZE];
    int min, max, sum;
    double avg;
    double start_time, end_time;

    // Initialize the array with random values
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000;
    }

    // Initialize reduction variables
    min = array[0];
    max = array[0];
    sum = 0;

    // Start timing
    start_time = omp_get_wtime();

    // Compute reduction using parallel reduction pragma
    #pragma omp parallel for reduction(min:min) reduction(max:max) reduction(+:sum)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += array[i];
        if (array[i] < min) {
            min = array[i];
        }
        if (array[i] > max) {
            max = array[i];
        }
    }

    // Compute average
    avg = (double)sum / ARRAY_SIZE;

    // End timing
    end_time = omp_get_wtime();

    // Print the results
    printf("Array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("Minimum: %d\n", min);
    printf("Maximum: %d\n", max);
    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", avg);

    printf("Execution time: %.6f seconds\n", end_time - start_time);

    return 0;
}
