// week5_task2_struct_save_load.c
// Name: Lakshay  Surname: Negi  Student ID: 241ADB131
//
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
  char name[MAX_NAME_LEN];
  int age;
  float gpa;
} Student;

int save_student(const Student* s, const char* filename);
int load_student(const char* filename, Student* out);

int main(void) {
  Student s1 = {0};
  strcpy(s1.name, "Alice");
  s1.age = 21;
  s1.gpa = 3.75f;

  Student loaded = {0};
  const char* filename = "student.txt";

  printf("Saving student to file...\n");
  if (save_student(&s1, filename) == -1) {
    perror("Error saving student");
    return EXIT_FAILURE;
  }

  printf("Loading student from file...\n");
  if (load_student(filename, &loaded) == -1) {
    perror("Error loading student");
    return EXIT_FAILURE;
  }

  printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age,
         loaded.gpa);

  return EXIT_SUCCESS;
}

int save_student(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) return -1;

  int result = fprintf(fp, "%s %d %f\n", s->name, s->age, s->gpa) < 0 ? -1 : 0;

  if (fclose(fp) != 0) result = -1;
  return result;
}

int load_student(const char* filename, Student* out) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) return -1;

  int items_read = fscanf(fp, "%49s %d %f", out->name, &out->age, &out->gpa);

  fclose(fp);

  return (items_read == 3) ? 0 : -1;
}