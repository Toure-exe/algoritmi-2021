#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "edit_dist.h"
#define MAX_LEN 1024


static int ** create_matrix(int s1, int s2){
    int ** memo = malloc((unsigned long)s1 * sizeof(int *));
    for(int i=0; i<s1; i++)
        memo[i] = malloc((unsigned long)s2 * sizeof(int));
    for(int i=0; i<s1; i++){
        for(int j=0; j<s2; j++)
            memo[i][j] = -1;
    }

    return memo;
}

static int ** recreate_matrix(int s1, int s2,int ** memo){
    memo = realloc(memo, (unsigned long)s1 * sizeof(int*)); 
    for(int i=0; i<s1; i++)
        memo[i] = realloc(memo[i], (unsigned long)s2 * sizeof(int)); 
    for(int i=0; i<s1; i++){
        for(int j=0; j<s2; j++)
            memo[i][j] = -1;
    }

    return memo;
}

static void free_matrix(int ** matrix){
    if(matrix != NULL){
        for(int i=0; i<(int)(sizeof(matrix[i])/sizeof(matrix[0])); i++)
          free(matrix[i]);
       free(matrix);
    }
    
}

static void run_edit_distance_dyn(const char * correctme, const char * dict){
    FILE * fp_cm = fopen(correctme,"r");
    FILE * fp_dict = fopen(dict,"r");
    FILE * fp_out = fopen("corrected.txt","w");
    char * str1 = malloc(MAX_LEN * sizeof(char));
    char * current_str = malloc(MAX_LEN * sizeof(char));
    char * str2 = malloc(MAX_LEN * sizeof(char));
    int current_edit = 0, temp_edit = 0;
    int ** memo = NULL;

   
    printf("correzione in corso...\n");
    while(fscanf(fp_cm,"%s",str1) != EOF){

     for(int i=0; i<(int)strlen(str1); i++)
          str1[i] = (char)tolower(str1[i]);
        
    // printf("correctme attuale: %s\n", str1);
 
     current_str = realloc(current_str, (unsigned long) strlen(str1) * sizeof(char));   
      strcpy(current_str,str1);

      if(fscanf(fp_dict,"%s",str2) <= 0){
        printf("reading error.\n");
        exit(EXIT_FAILURE);
      }  
      memo = create_matrix((int)strlen(str1),(int)strlen(str2));
     
      current_edit = edit_dist_dyn(str1,(int)strlen(str1),str2,(int)strlen(str2),memo);
     
      
      while(fscanf(fp_dict,"%s",str2) != EOF){
        memo = recreate_matrix((int)strlen(str1),(int)strlen(str2),memo);
        temp_edit = edit_dist_dyn(str1,(int)strlen(str1),str2,(int)strlen(str2),memo);
        
        if(current_edit > temp_edit){
            current_edit = temp_edit;
            current_str = realloc(current_str, (unsigned long)strlen(str2) * sizeof(char));
            strcpy(current_str,str2);
        }
      }
      fprintf(fp_out, "%s ", current_str); 
      //printf("parola corretta: %s\n", current_str);
      current_edit = 0;
      fseek(fp_dict, 0, SEEK_SET);
       
    }

    printf("\nfile corretto generato in ./corrected.txt\n");
    free_matrix(memo);
    free(str1);
    free(str2);
    free(current_str);
    fclose(fp_cm);
    fclose(fp_dict);
    fclose(fp_out);

}


static void run_edit_distance(const char * correctme, const char * dict){
    FILE * fp_cm = fopen(correctme,"r");
    FILE * fp_dict = fopen(dict,"r");
    FILE * fp_out = fopen("corrected.txt","w");
    char * str1 = malloc(MAX_LEN * sizeof(char));
    char * current_str = malloc(MAX_LEN * sizeof(char));
    char * str2 = malloc(MAX_LEN * sizeof(char));
    int current_edit = 0, temp_edit = 0;
   

    while(fscanf(fp_cm,"%s",str1) != EOF){

     for(int i=0; i<(int)strlen(str1); i++)
          str1[i] = (char)tolower(str1[i]);
        
     printf("correctme attuale: %s\n", str1);
 
     current_str = realloc(current_str, (unsigned long)strlen(str1) * sizeof(char));   
      strcpy(current_str,str1);    
      if(fscanf(fp_dict,"%s",str2) <= 0){
        printf("reading error.\n");
        exit(EXIT_FAILURE);
      }  
      current_edit = edit_dist(str1,(int)strlen(str1),str2,(int)strlen(str2));
     
      while(fscanf(fp_dict,"%s",str2) != EOF){

        temp_edit = edit_dist(str1,(int)strlen(str1),str2,(int)strlen(str2));
        if(current_edit > temp_edit){
            current_edit = temp_edit;
            current_str = realloc(current_str, (unsigned long)strlen(str2) * sizeof(char));
            strcpy(current_str,str2);
        }
      }
      fprintf(fp_out, "%s ", current_str); 
      printf("parola corretta: %s\n", current_str);
      current_edit = 0;
      fseek(fp_dict, 0, SEEK_SET);
       
    }

    printf("\nfile corretto generato in ./corrected.txt\n");
    free(str1);
    free(str2);
    free(current_str);
    fclose(fp_cm);
    fclose(fp_dict);
    fclose(fp_out);

}


static void test_wrapper_functions(const char *correctme, const char *dict) {
    if (correctme == NULL) {
        fprintf(stderr, "main: unable to open the file");
        exit(EXIT_FAILURE);
    }

    if (dict == NULL) {
        fprintf(stderr, "main: unable to open the file");
        exit(EXIT_FAILURE);
    }


    run_edit_distance_dyn(correctme,dict);
    run_edit_distance(correctme,dict);
    
}



int main(int argc, char const * argv[]){
    if(argc < 3){
         printf("Usage: current_array_main <file_name>\n");
         exit(EXIT_FAILURE);
    }

    test_wrapper_functions(argv[1],argv[2]);

}

