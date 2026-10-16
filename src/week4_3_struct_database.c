/*
 * week4_3_struct_database.c
 * Author: Lakshay Negi
 * Student ID: 241ADB131
 * Description: Dynamically allocates an array of Student structures using
 * malloc, reads student records from user input, displays them in a formatted
 *              table, and frees all allocated memory before exiting.
 */

#include <stdio.h>
#include <stdlib.h>

// Define the Student structure (same as in Task 2)
struct Student {
  char name[50];
  int id;
  float grade;
};

int main(void) {
  int n;

  // Prompt the user for the number of students (no newline after it)
  printf("Enter number of students: ");

  // Validate that n is a valid integer and strictly positive (> 0)
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid number.\n");
    return 1;
  }

  // Dynamically allocate memory for n Student records
  struct Student* students =
      (struct Student*)malloc((size_t)n * sizeof(struct Student));

  // Check if malloc returned NULL
  if (students == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  // Read each student's name, ID, and grade
  for (int i = 0; i < n; i++) {
    printf("Enter data for student %d: ", i + 1);

    // Read name (up to 49 chars to prevent buffer overflow), id, and grade
    if (scanf("%49s %d %f", students[i].name, &students[i].id,
              &students[i].grade) != 3) {
      free(students);  // Free the array first before printing error and exiting
      printf("Invalid input.\n");
      return 1;
    }
  }

  // Print one empty line after all input, then the table header
  printf("\n");
  printf("%-6s %-11s %s\n", "ID", "Name", "Grade");

  // Print each student record in input order
  for (int i = 0; i < n; i++) {
    printf("%-6d %-11s %.1f\n", students[i].id, students[i].name,
           students[i].grade);
  }

  // Free dynamically allocated memory before program termination
  free(students);

  return 0;
}