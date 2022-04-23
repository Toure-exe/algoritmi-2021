#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "MergeBinaryInsertionSort.h"

/*
 * Test suite for array data structure and algorithms
 */

// precedence relation used in tests
static int precedes_int(void *i1_p, void *i2_p) {
  int *int1_p = (int*)i1_p;
  int *int2_p = (int*)i2_p;
  
  if(*int1_p > *int2_p)
    return 1;
  else if(*int1_p < *int2_p)
    return 0;
  else
    return 2;
}

static void test_current_array_is_empty_zero_el() {
  Array *current_array_int = current_array_create(precedes_int);
  TEST_ASSERT_TRUE(current_array_is_empty(current_array_int));
  current_array_free_memory(current_array_int);
}

static void test_current_array_is_empty_one_el() {
  int i = -12;
  Array *current_array_int = current_array_create(precedes_int);
  current_array_add(current_array_int, &i);
  TEST_ASSERT_FALSE(current_array_is_empty(current_array_int));
  current_array_free_memory(current_array_int);
}

static void test_current_array_size_zero_el() {
  Array *current_array_int = current_array_create(precedes_int);
  TEST_ASSERT_EQUAL_INT(0, current_array_size(current_array_int));
  current_array_free_memory(current_array_int);
}

static void test_current_array_size_one_el() {
  int i1 = -12;
  Array *current_array_int = current_array_create(precedes_int);
  current_array_add(current_array_int, &i1);
  TEST_ASSERT_EQUAL_INT(1, current_array_size(current_array_int));
  current_array_free_memory(current_array_int);
}

static void test_current_array_size_two_el() {
  int i1 = -12;
  int i2 = 2;
  Array *current_array_int = current_array_create(precedes_int);
  current_array_add(current_array_int, &i1);
  current_array_add(current_array_int, &i2);
  TEST_ASSERT_EQUAL_INT(2, current_array_size(current_array_int));
  current_array_free_memory(current_array_int);
}

static void test_current_array_add_get_one_el() {
  int i1 = -12;
  Array *current_array_int = current_array_create(precedes_int);
  current_array_add(current_array_int, &i1);
  //merge_binary_insertion_sort(current_array_int);
  TEST_ASSERT_EQUAL_PTR(&i1, current_array_get(current_array_int, 0));
  current_array_free_memory(current_array_int);
}

static void test_current_array_add_get_three_el() {
  int i1 = -12;
  int i2 = 0;
  int i3 = 4;
  int i4 = 2;
  int i5 = 10;
  int* exp_arr[] = {&i1, &i2, &i4, &i3, &i5};

  Array *current_array_int = current_array_create(precedes_int);
  current_array_add(current_array_int, &i5);
  current_array_add(current_array_int, &i2);
  current_array_add(current_array_int, &i3);
  current_array_add(current_array_int, &i4);
  current_array_add(current_array_int, &i1);

  merge_binary_insertion_sort(current_array_int);
  int **act_arr = malloc(5*sizeof(int*));
  for (int i=0; i < 5; ++i) {
    act_arr[i] = (int*)current_array_get(current_array_int, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, act_arr, 5);
  free(act_arr);
  current_array_free_memory(current_array_int);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_current_array_is_empty_zero_el);
  RUN_TEST(test_current_array_is_empty_one_el);
  RUN_TEST(test_current_array_size_zero_el);
  RUN_TEST(test_current_array_size_one_el);
  RUN_TEST(test_current_array_size_two_el);
  RUN_TEST(test_current_array_add_get_one_el);
  RUN_TEST(test_current_array_add_get_three_el);
  return UNITY_END();
}