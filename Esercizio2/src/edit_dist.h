#ifndef EDIT_DIST
#define EDIT_DIST

/*
 * A recursive algorithm to find minimum number
 * of operations to convert the first string of length m to
 * the second one of length n
 */
int edit_dist(char *, int, char *, int);

/*
 * A dynamic algorithm to find minimum number
 * of operations to convert the first string of length m to
 * the second one of length n
 */
int edit_dist_dyn(char *, int, char *, int, int **);

#endif // EDIT_DIST