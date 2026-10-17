// week5_task4_struct_binary_io.c
// Name: Lakshay  Surname: Negi  Student ID: 241ADB131
//
// Task 4: Bonus - Binary File Version
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
  char name[MAX_NAME_LEN];
  int age;
  float gpa;
} Student;

// Function prototypes
int save_student_binary(const Student* s, const char* filename);
int load_student_binary(const char* filename, Student* out);
long file_size(const char* filename);

// Helper to save text version for comparison (identical to Task 2)
int save_student_text(const Student* s, const char* filename);

int main(void) {
  // Zero-initialise to avoid writing uninitialized padding bytes to disk
  Student s1 = {0};
  strcpy(s1.name, "Alice");
  s1.age = 21;
  s1.gpa = 3.75f;

  Student loaded = {0};
  const char* bin_filename = "student.bin";
  const char* txt_filename = "student.txt";

  printf("Saving student in binary format...\n");
  if (save_student_binary(&s1, bin_filename) != 0) {
    perror("Error saving binary");
    return EXIT_FAILURE;
  }

  printf("Loading student from binary file...\n");
  if (load_student_binary(bin_filename, &loaded) != 0) {
    perror("Error loading binary");
    return EXIT_FAILURE;
  }

  printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age,
         loaded.gpa);

  // Save in text format to compare sizes
  if (save_student_text(&s1, txt_filename) != 0) {
    perror("Error saving text");
    return EXIT_FAILURE;
  }

  long txt_size = file_size(txt_filename);
  long bin_size = file_size(bin_filename);

  printf("Text file size: %ld bytes\n", txt_size);
  printf("Binary file size: %ld bytes\n", bin_size);

  return EXIT_SUCCESS;
}

// Write the struct directly in binary format
int save_student_binary(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "wb");
  if (fp == NULL) return -1;

  size_t written = fwrite(s, sizeof(Student), 1, fp);
  fclose(fp);

  return (written == 1) ? 0 : -1;
}

// Read the struct directly from binary format
int load_student_binary(const char* filename, Student* out) {
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) return -1;

  size_t read_count = fread(out, sizeof(Student), 1, fp);
  fclose(fp);

  return (read_count == 1) ? 0 : -1;
}

// Get the file size in bytes using fseek and ftell
long file_size(const char* filename) {
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) return -1;

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);

  fclose(fp);
  return size;
}

// Helper text saver for size comparison
int save_student_text(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) return -1;

  fprintf(fp, "%s %d %f\n", s->name, s->age, s->gpa);

  fclose(fp);
  return 0;
}