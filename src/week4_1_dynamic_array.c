/*
 * week4_1_dynamic_array.c
 * Author:Lakshay Negi
 * Student ID: 241ADB131
 * Description: Dynamically allocates an integer array using malloc,
 *              reads elements from the user, computes their sum and average,
 *              and properly frees allocated memory.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n;

  // Prompt the user for the number of elements (no newline as required)
  printf("Enter number of elements: ");

  // Validate that input is an integer and strictly positive (> 0)
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid size.\n");
    return 1;
  }

  // Dynamically allocate memory for n integers using malloc
  int* arr = (int*)malloc((size_t)n * sizeof(int));

  // Always check if malloc returned NULL (allocation failure)
  if (arr == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  // Prompt the user to enter N integers (no newline after prompt)
  printf("Enter %d integers: ", n);

  long long sum = 0;  // Use long long to prevent potential integer overflow
                      // during summation
  for (int i = 0; i < n; i++) {
    // Read each integer and validate input
    if (scanf("%d", &arr[i]) != 1) {
      free(arr);  // Free the array first before printing error and exiting
      printf("Invalid input.\n");
      return 1;
    }
    sum += arr[i];
  }

  // Compute average in floating-point arithmetic
  double average = (double)sum / n;

  // Print results in the exact required format
  printf("Sum = %lld\n", sum);
  printf("Average = %.2f\n", average);

  // Free dynamically allocated memory before program termination
  free(arr);

  return 0;
}