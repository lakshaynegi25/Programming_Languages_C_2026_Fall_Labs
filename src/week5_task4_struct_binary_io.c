// week5_task4_struct_binary_io.c
// Name: Lakshay  Surname: Negi  Student ID: 241ADB131
//
// Task 4: Bonus - Binary File Version
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

int save_student_binary(const Student* s, const char* filename);
int load_student_binary(const char* filename, Student* out);
long file_size(const char* filename);
int save_student_text(const Student* s, const char* filename);

int main(void) {
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

  if (save_student_text(&s1, txt_filename) != 0) {
    perror("Error saving text");
    return EXIT_FAILURE;
  }

  long txt_size = file_size(txt_filename);
  long bin_size = file_size(bin_filename);

  if (txt_size < 0 || bin_size < 0) {
    fprintf(stderr, "Error calculating file sizes.\n");
    return EXIT_FAILURE;
  }

  printf("Text file size: %ld bytes\n", txt_size);
  printf("Binary file size: %ld bytes\n", bin_size);

  return EXIT_SUCCESS;
}

int save_student_binary(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "wb");
  if (fp == NULL) return -1;

  int result = (fwrite(s, sizeof(Student), 1, fp) == 1) ? 0 : -1;
  if (fclose(fp) != 0) result = -1;

  return result;
}

int load_student_binary(const char* filename, Student* out) {
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) return -1;

  int result = (fread(out, sizeof(Student), 1, fp) == 1) ? 0 : -1;
  fclose(fp);

  return result;
}

long file_size(const char* filename) {
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) return -1;

  if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
    return -1;
  }

  long size = ftell(fp);
  fclose(fp);
  return size;
}

int save_student_text(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) return -1;

  int result = fprintf(fp, "%s %d %f\n", s->name, s->age, s->gpa) < 0 ? -1 : 0;
  if (fclose(fp) != 0) result = -1;

  return result;
}