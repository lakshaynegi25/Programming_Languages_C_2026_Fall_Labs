/*
 * week4_2_struct_student.c
 * Author: Lakshay Negi
 * Student ID: 241ADB131
 * Description: Defines a Student structure, initializes two student records
 *              using the dot operator and strcpy, and prints their details.
 */

#include <stdio.h>
#include <string.h>

// Define the Student structure as required
struct Student {
  char name[50];
  int id;
  float grade;
};

int main(void) {
  // Declare two Student variables
  struct Student student1;
  struct Student student2;

  // Assign values to Student 1 using strcpy and the dot (.) operator
  strcpy(student1.name, "Alice Johnson");
  student1.id = 1001;
  student1.grade = 9.1f;

  // Assign values to Student 2 using strcpy and the dot (.) operator
  strcpy(student2.name, "Bob Smith");
  student2.id = 1002;
  student2.grade = 8.7f;

  // Print the information of each student in the exact required format (%.1f)
  printf("Student 1: %s, ID: %d, Grade: %.1f\n", student1.name, student1.id,
         student1.grade);
  printf("Student 2: %s, ID: %d, Grade: %.1f\n", student2.name, student2.id,
         student2.grade);

  return 0;
}