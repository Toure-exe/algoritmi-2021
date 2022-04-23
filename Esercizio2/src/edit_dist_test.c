#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "edit_dist.h"

/*
 * Test suite for edit_distance classic and dynamic memory
 */

static void test_both_strings_are_empty() {
	char * string1 = "";
    char * string2 = "";
    int s1 = (int)strlen(string1);
    int s2 = (int)strlen(string2);

    TEST_ASSERT_EQUAL_INT(0, edit_dist(string1, s1, string2, s2));
}

static void test_both_strings_are_empty_dyn() {
	char * string1 = "";
    char * string2 = "";
    int s1 = (int)strlen(string1);
    int s2 = (int)strlen(string2);
    int ** memo = malloc((unsigned long)s1 * sizeof(int *));
    for(int i=0; i<s1; i++)
    	memo[i] = malloc((unsigned long)s2 * sizeof(int));
    for(int i=0; i<s1; i++){
    	for(int j=0; j<s2; j++)
    		memo[i][j] = -1;
    }

    TEST_ASSERT_EQUAL_INT(0, edit_dist_dyn(string1, s1, string2, s2, memo));

    for(int i=0; i<s1; i++)
        free(memo[i]);
     free(memo);
}

static void test_first_string_is_empty() {
    char * string1 = "";
    char * string2 = "Ciao";
    int s1 = (int)strlen(string1);
    int s2 = (int)strlen(string2);

    TEST_ASSERT_EQUAL_INT(4, edit_dist(string1, s1, string2, s2));
}

static void test_first_string_is_empty_dyn() {
    char * string1 = "";
    char * string2 = "Ciao";
    int s1 = (int)strlen(string1);
    int s2 = (int)strlen(string2);
    int ** memo = malloc((unsigned long)s1 * sizeof(int *));
    for(int i=0; i<s1; i++)
    	memo[i] = malloc((unsigned long)s2 * sizeof(int));
    for(int i=0; i<s1; i++){
    	for(int j=0; j<s2; j++)
    		memo[i][j] = -1;
    }

    TEST_ASSERT_EQUAL_INT(4, edit_dist_dyn(string1, s1, string2, s2, memo));

    for(int i=0; i<s1; i++)
        free(memo[i]);
     free(memo);
}

static void test_second_string_is_empty() {
    char * string1 = "Ciao";
    char * string2 = "";
    int s1 = (int)strlen(string1);
    int s2 = (int)strlen(string2);

    TEST_ASSERT_EQUAL_INT(4, edit_dist(string1, s1, string2, s2));
}

static void test_second_string_is_empty_dyn() {
    char * string1 = "Ciao";
    char * string2 = "";
    int s1 = (int)strlen(string1);
    int s2 = (int)strlen(string2);
    int ** memo = malloc((unsigned long)s1 * sizeof(int *));
    for(int i=0; i<s1; i++)
    	memo[i] = malloc((unsigned long)s2 * sizeof(int));
    for(int i=0; i<s1; i++){
    	for(int j=0; j<s2; j++)
    		memo[i][j] = -1;
    }

    TEST_ASSERT_EQUAL_INT(4, edit_dist_dyn(string1, s1, string2, s2, memo));

    for(int i=0; i<s1; i++)
        free(memo[i]);
     free(memo);
}

static void test_edit_dist_classic() {
    char * string1 = "hanno";
    char * string2 = "buttu";
    int s1 = (int)strlen(string1);
    int s2 = (int)strlen(string2);

    TEST_ASSERT_EQUAL_INT(10, edit_dist(string1, s1, string2, s2));
}

static void test_edit_dist_dynamic() {
    char * string1 = "hanno";
    char * string2 = "buttu";
    int s1 = (int)strlen(string1);
    int s2 = (int)strlen(string2);
    int ** memo = malloc((unsigned long)s1 * sizeof(int *));
    for(int i=0; i<s1; i++)
    	memo[i] = malloc((unsigned long)s2 * sizeof(int));
    for(int i=0; i<s1; i++){
    	for(int j=0; j<s2; j++)
    		memo[i][j] = -1;
    }

    TEST_ASSERT_EQUAL_INT(10, edit_dist_dyn(string1, s1, string2, s2, memo));

    for(int i=0; i<s1; i++)
        free(memo[i]);
     free(memo);
}

static void test_strings_equals(){
    char * string1 = "mondo";
    char * string2 = "mondo";
    int s1 = (int)strlen(string1);
    int s2 = (int)strlen(string2);

    TEST_ASSERT_EQUAL_INT(0,edit_dist(string1,s1,string2,s2));

}

static void test_strings_equals_dyn(){
    char * string1 = "mondo";
    char * string2 = "mondo";
    int s1 = (int)strlen(string1);
    int s2 = (int)strlen(string2);
    int ** memo = malloc((unsigned long)s1 * sizeof(int *));
    for(int i=0; i<s1; i++)
        memo[i] = malloc((unsigned long)s2 * sizeof(int));
    for(int i=0; i<s1; i++){
        for(int j=0; j<s2; j++)
            memo[i][j] = -1;
    }

    TEST_ASSERT_EQUAL_INT(0,edit_dist_dyn(string1,s1,string2,s2,memo));

    for(int i=0; i<s1; i++)
        free(memo[i]);
     free(memo);

}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_both_strings_are_empty);
  RUN_TEST(test_both_strings_are_empty_dyn);
  RUN_TEST(test_first_string_is_empty);
  RUN_TEST(test_first_string_is_empty_dyn);
  RUN_TEST(test_second_string_is_empty);
  RUN_TEST(test_second_string_is_empty_dyn);
  RUN_TEST(test_edit_dist_classic);
  RUN_TEST(test_edit_dist_dynamic);
  RUN_TEST(test_strings_equals);
  RUN_TEST(test_strings_equals_dyn);
  return UNITY_END();
}