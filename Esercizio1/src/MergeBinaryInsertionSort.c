#include <stdio.h>
#include <stdlib.h>
#include "MergeBinaryInsertionSort.h"

//Initial capacity for the array
#define INITIAL_CAPACITY 2

//It represents the internal structure of this implementation of array
struct _Array {
  void **array;
  int size;
  int array_capacity;
  int index;
  int (*precedes)(void*, void*);
};

static void insert_element(Array *current_array, void *element);
static void merge_sort(Array *current_array, int k, int i, int j);
static void merge(Array *current_array, int i, int q, int j);
static void binary_insertion_sort(Array *current_array, int left,int right);
static int binarySearch(Array *current_array, void * item, int low, int high);

Array *current_array_create(int (*precedes)(void*, void*)) {
  if (precedes == NULL) {
    fprintf(stderr, "current_array_create: precedes parameter cannot be NULL");
    return NULL;
  }
  Array *current_array = (Array*)malloc(sizeof(Array));
  if (current_array == NULL) {
    fprintf(stderr, "current_array_create: unable to allocate memory for the array");
    return NULL;
  }
  current_array->array = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
  if (current_array->array == NULL) {
    fprintf(stderr, "current_array_create: unable to allocate memory for the internal array");
    return NULL;
  }
  current_array->size = 0;
  current_array->array_capacity = INITIAL_CAPACITY;
  current_array->precedes = precedes;
  current_array->index = 0;
  return current_array;
}

int current_array_is_empty(Array *current_array) {
  if (current_array == NULL) {
    fprintf(stderr, "current_array_is_empty: current_array parameter cannot be NULL");
    return -1;
  }
  return current_array->size == 0;
}

 int current_array_size(Array *current_array) {
  if (current_array == NULL) {
    fprintf(stderr, "current_array_size: current_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return current_array->size;
}

void current_array_add(Array *current_array, void *element) {
  if (current_array == NULL) {
    fprintf(stderr, "current_array_add: current_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (element == NULL) {
    fprintf(stderr, "current_array_add: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

 if (current_array->size >= current_array->array_capacity) {
    current_array->array_capacity = 2 * current_array->array_capacity; // Why multiply by 2?
    current_array->array = (void**)realloc(current_array->array, (unsigned long)current_array->array_capacity * sizeof(void*));
    if (current_array->array == NULL) {
      fprintf(stderr,"current_array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
  }
  insert_element(current_array, element);
  current_array->size++;
  current_array->index++;
}

void *current_array_get(Array *current_array, int i) {
  if (current_array == NULL) {
    fprintf(stderr, "ordered_array_get: ordered_array parameter cannot be NULL");
    return NULL;
  }
  if (i >= current_array->size) {
    fprintf(stderr, "ordered_array_get: Index %d is out of the array bounds", i);
    return NULL;
  }
  return current_array->array[i];
}

void current_array_free_memory(Array *current_array) {
  if (current_array == NULL) {
    fprintf(stderr, "current_array_free_memory: current_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(current_array->array);
  free(current_array);
}

void merge_binary_insertion_sort(Array *current_array){
  int k = 4; // valore di riferimento, se minore utilizzare binary insetion sort

  if (current_array == NULL || current_array->size <= k) {
    fprintf(stderr, "current_array_merge_binary_insertion_sort: current_array parameter cannot be NULL or array size cannot be smaller or equals to k parameter\n");
    exit(EXIT_FAILURE);
  }

  if (current_array->size > 1){
    if (current_array->size > k){
      merge_sort(current_array, k, 0, current_array->size-1);
    }else if (current_array->size <= k){
      binary_insertion_sort(current_array,0,current_array->size);
    }
  }
}


static void merge_sort(Array *current_array, int k, int i, int j){
  int q = 0;
  if((j-i)+1 > k){
    if(i<j){
      q = (i+j)/2;
      merge_sort(current_array,k,i,q);
      merge_sort(current_array,k,q+1,j);
      merge(current_array,i,q,j);
    }
  }else if((j-i)+1 <= k){
    binary_insertion_sort(current_array,i,j);
  }
}

static void merge(Array *current_array, int left, int center, int right){
  int i = 0, j = 0, k = 0;
  int n1 = center - left + 1;
  int n2 = right - center;
  void ** temp1;
  void ** temp2;

  /* Allocate the memory for two generic vector temp1 and temp2*/
  temp1 = (void**)malloc((unsigned long)n1 * sizeof(void*));
  temp2 = (void**)malloc((unsigned long)n2 * sizeof(void*));

  /* Copy data to temp arrays temp1[] and temp2[] */
  for(i = 0; i < n1; i++)
        temp1[i] = current_array->array[left + i];
  for(j = 0; j < n2; j++)
        temp2[j] = current_array->array[center + 1 + j];

  /* Merge the temp arrays back into current_array->array[left..right]*/
  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2){
        if((current_array->precedes(temp1[i], temp2[j]) == 0) || (current_array->precedes(temp1[i], temp2[j]) == 2)){
            current_array->array[k] = temp1[i];
            i++;
        }else{
            current_array->array[k] = temp2[j];
            j++;
        }
        k++;
  }

  /* Copy the remaining elements of temp1[] and temp2[], if there are any */
  while(i < n1){
        current_array->array[k] = temp1[i];
        i++;
        k++;
  }

   while (j < n2) {
        current_array->array[k] = temp2[j];
        j++;
        k++;
    }

    /* Free the memory allocated previously*/
    free(temp1);
    free(temp2);
}

static void binary_insertion_sort(Array *current_array, int left, int right){
  int i, loc, j;
  void * selected;

  for(i=left+1; i<right+1; i++){
    j = i - 1;
    selected = current_array->array[i];

    //find location to insert the selected element
    loc = binarySearch(current_array, selected, left, j);

    //move all elements after location to create space
    while(j >= loc){
      current_array->array[j+1] = current_array->array[j];
      j--;
    }
    current_array->array[j+1] = selected;
  }
}

static int binarySearch(Array * current_array, void * item, int low, int high){
  if(high <= low){
    if(current_array->precedes(item, current_array->array[low]) == 1)
      return low+1;
    else
      return low;
  }
    
  
  int mid = (low + high)/2;

  if((current_array->precedes(item, current_array->array[mid])) == 2)
    return mid+1;
  
  if((current_array->precedes(item, current_array->array[mid])) == 1)
    return binarySearch(current_array, item, mid+1, high);
  
  return binarySearch(current_array, item, low, mid-1);
}
  
//inserts the specified element in the specified array at the specified index position
static void insert_element(Array *current_array, void *element) {
  current_array->array[current_array->index] = element;
}