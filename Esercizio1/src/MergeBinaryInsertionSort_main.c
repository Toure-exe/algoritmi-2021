#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "MergeBinaryInsertionSort.h"

#define BUFFER_SIZE 1024

typedef struct _record {
  char *string_field;
  long integer_field;
  double double_field;
} Record;

/*
 * It takes as input two pointers to Record.
 * It returns 1 iff the integer field of the first record is greater than
 * the integer field of the second one (0 otherwise)
 * It return 2 iff the two integer field are equals
*/

static int precedes_record_int_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer");
    return -1;
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer");
    return -1;
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  
  if(rec1_p->integer_field > rec2_p->integer_field)
    return 1;
  else if(rec1_p->integer_field < rec2_p->integer_field)
    return 0;
  else
    return 2;
}

/*
 * It takes as input two pointers to Record.
 * It returns 1 iff the string field of the first record is greater than
 * the string field of the second one (0 otherwise)
 * It return 2 iff the two string field are equals
*/
static int precedes_record_string_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_string: the first parameter is a null pointer");
    return -1;
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_string: the second parameter is a null pointer");
    return -1;
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  int ris = strcmp(rec1_p->string_field, rec2_p->string_field);

  if(ris > 0)
    return 1;
  else if(ris < 0)
    return 0;
  else
    return 2;
}

/*
 * It takes as input two pointers to Record.
 * It returns 1 iff the double field of the first record is greater than
 * the double field of the second one (0 otherwise)
 * It return 2 iff the two double field are equals
*/
static int precedes_record_double_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_double_field: the first parameter is a null pointer");
    return -1;
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_double_field: the second parameter is a null pointer");
    return -1;
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  
  if(rec1_p->double_field > rec2_p->double_field)
    return 1;
  else if(rec1_p->double_field < rec2_p->double_field)
    return 0;
  else
    return 2;
}

static void free_array(Array *array) {
  int size = current_array_size(array);
  for (int i = 0; i < size; i++) {
    Record *array_element = (Record*)current_array_get(array, i);
    free(array_element->string_field);
    free(array_element);
  }
  current_array_free_memory(array);
}


static  void print_array(Array *array) {
  int size = current_array_size(array);
  FILE *fp_out = fopen("output.txt","w");

  Record *array_element;
  printf("\nPrinting the ordered data in output.txt...\n");


  fprintf(fp_out,"%s\n", "ORDERED DATA ____________");
  for (int i = 0; i < size; ++i){
    array_element = (Record*)current_array_get(array, i);
    fprintf(fp_out,"%ld, %f, %s\n", array_element->integer_field,array_element->double_field,array_element->string_field);
  }

  fprintf(fp_out,"%s\n\n", "END DATA ____________");

  fclose(fp_out);
}

static void load_array(const char *file_name, Array *array) {
  char buffer[BUFFER_SIZE];
  FILE *fp;

  printf("\nLoading data from file...\n");
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the file");
    exit(EXIT_FAILURE);
  }

  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    Record *record_p = malloc(sizeof(Record));
    if (record_p == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the read record");
      exit(EXIT_FAILURE);
    }

    strtok(buffer,",");
    char *string_field_in_read_line_p = strtok(NULL, ",");
    char *integer_field_in_read_line_p = strtok(NULL, ",");
    char *double_field_in_read_line_p = strtok(NULL, ",");

    record_p->string_field = malloc((strlen(string_field_in_read_line_p)+1) * sizeof(char));
    if (record_p->string_field == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
      exit(EXIT_FAILURE);
    }
    strcpy(record_p->string_field, string_field_in_read_line_p);
    record_p->integer_field = atol(integer_field_in_read_line_p);
    record_p->double_field = atof(double_field_in_read_line_p);
    current_array_add(array, (void*)record_p);
  }
  fclose(fp);
  printf("\nData loaded\n");
}

static void test_wrapper_functions(const char *file_name, int (*compare)(void*, void*)) {
  Array *array = current_array_create(compare);
  load_array(file_name, array);
  clock_t begin = clock();
  merge_binary_insertion_sort(array);
  clock_t end = clock();
  double time_merge = (double)(end - begin)/CLOCKS_PER_SEC;
  printf("Sorting time: %f\n", time_merge);
  print_array(array);
  free_array(array);
}

int main(int argc, char const *argv[]){
  if (argc < 2) {
    printf("Usage: current_array_main <file_name>\n");
    exit(EXIT_FAILURE);
}
  
  test_wrapper_functions(argv[1], precedes_record_int_field);
  test_wrapper_functions(argv[1], precedes_record_double_field);
  test_wrapper_functions(argv[1], precedes_record_string_field);
  return 0;
}