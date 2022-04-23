#ifndef MERGE_BINARY_INSERCTION_SORT
#define MERGE_BINARY_INSERCTION_SORT

/*
 * An array of any number of elements of any kind
 */
typedef struct _Array Array;

/* It creates an empty array and returns the created an array.
 * It accepts as input a pointer to a function implementing the precedence
 * relation between the array elements. Such a function must accept as input
 * two pointers to elements and return 0 iff the first element does NOT precede
 * the second one and a number different from zero otherwise.
 * The input parameter cannot be NULL
 */
Array *current_array_create(int (*precdes)(void*, void*));

/* It accepts as input a pointer to anarray and
 * it returns 1 iff the ordered array is empty (0 otherwise).
 * The input parameter cannot be NULL
 */
int current_array_is_empty(Array*);

/* It accepts as input a pointer to an array and it
 * returns the number of elements currently stored into the array.
 * The input parameter cannot be NULL
 */
int current_array_size(Array*);

/* It accepts as input a pointer to an  array and a pointer to an
 * element. It adds the element to the ordered array in the right position.
 * The input parameters cannot be NULL
 */
void current_array_add(Array*, void*);

/* It accepts as input a pointer to an array and an integer "i" and
 * it returns the pointer to the i-th element of the array
 * The first parameter cannot be NULL; the second parameter must be a valid
 * position within the ordered array
 */
void *current_array_get(Array*, int);

/* It accepts as input a pointer to an array and
 * it frees the memory allocated to store the ordered array.
 * It does not free the memory allocated to store the array elements,
 * since freeing that memory is responsibility of the function where
 * the ordered array was created. The input parameters cannot be NULL
 */
void current_array_free_memory(Array*);


/* It accepts as input a pointer to an generic array and
 * sort it by using the insertion sort with binary search or 
 * by using the only merge sort depending on the developer's choice.
 */
void merge_binary_insertion_sort(Array*);

#endif // MERGE_BINARY_INSERCTION_SORT