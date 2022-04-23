#include <stdio.h>
#include "edit_dist.h"
#define MIN(a,b) ((a) < (b) ? a : b)

int edit_dist(char * str1, int s1, char * str2, int s2) {
    // Base cases
    if (s1 == 0)
        return s2;
    if (s2 == 0)
        return s1;
 
    // Case if last characters of two characters are same
    if (str1[s1-1] == str2[s2-1])
        return edit_dist(str1, s1-1, str2, s2-1);
 
    // If last characters are not same
    return MIN(1 + edit_dist(str1, s1, str2, s2-1),     // Insert
                 1 + edit_dist(str1, s1-1, str2, s2));   // Remove
}

int edit_dist_dyn(char * str1, int s1, char * str2, int s2, int ** memo){
    // Base cases
    if (s1 == 0){
        return s2;
    }
    if (s2 == 0){
        return s1;
    }

    // If the recursive call has been called previously, then
    // return the stored value calculated previously
    if (memo[s1-1][s2-1] != -1)
        return memo[s1-1][s2-1];
 
    // Case if last characters of two characters are same
    if (str1[s1-1] == str2[s2-1])
        return memo[s1-1][s2-1] = edit_dist_dyn(str1, s1-1, str2, s2-1, memo);
            
    // If last characters are not same
    return memo[s1-1][s2-1] = MIN((1+edit_dist_dyn(str1, s1, str2, s2-1, memo)),     // Insert
                                      (1+edit_dist_dyn(str1, s1-1, str2, s2, memo))); // Remove
                
}

