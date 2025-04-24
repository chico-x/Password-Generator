#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print_strings(char* strings[] , int n);
void swap(char **a , char** b);
void permute(char **arr, int start, int end, FILE* fp);
void free_keywords(char* strings[], int n);
int factorial(int n);
// swapping function, to be used in the permutations function



void print_strings(char* strings[],int n)
{
    printf("Called\n");
    for(int i = 0 ; i < n ; i++)
    {
        printf("%s\t" , strings[i]);
    }
}

int main() {
    // Start timer
    int i, n;
    char buffer[30]; 

    printf("Enter the number of keywords to input:");
    scanf("%d",&n);
    char* strings[n]; 

    getchar();
    int n_pw = factorial(n);
    printf("Number of Passwords: %d\n", n_pw);

    int char_count = 0;
    for ( i = 0; i < n; i++)
    {
        printf("Enter keyword %d:\n", i + 1); 
        fgets(buffer, sizeof(buffer), stdin); 
        buffer[strcspn(buffer, "\n")] = '\0'; 
        strings[i] = malloc(strlen(buffer) + 1); 
        strcpy(strings[i], buffer);  
        char_count = char_count + strlen(buffer);
    }
    
    float pred_size = ((char_count + 1) * n_pw + 100.0) / 1024.0 ;
    printf("Predicted Size: %.2f KB \n", pred_size);

    char cont;
    printf("Would you like to generate the permutations?(y/n) ");
    scanf("%c" , &cont);
    if(cont == 'n' || cont == 'N')
    {
        return 0;
    }
    //print_strings(strings, n);
    FILE *fp = fopen("permutations.txt", "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file for writing\n");
        exit(1);
    }

    // Generate and write all permutations into the file.
    clock_t start_time = clock();

    permute(strings, 0, n, fp);

    clock_t end_time = clock();
    
    // Calculate the elapsed time in seconds.
    double time_taken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken: %.4f seconds\n", time_taken);
    // Close the file when done.
    fclose(fp);

    // Free allocated memory.
    free_keywords(strings, n);

    // End timer

    return 0;
}

void free_keywords(char* strings[], int n) {
    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }
}

void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char **arr, int start, int end, FILE *fp) {
    if (start == end) {
        // Base case: concatenate and write the permutation to the file.
        for (int i = 0; i < end; i++) {
            fprintf(fp, "%s", arr[i]);
        }
        fprintf(fp, "\n"); // New line after each permutation.
    } else {
        for (int i = start; i < end; i++) {
            // Swap the current element with the start element.
            char *temp = arr[start];
            arr[start] = arr[i];
            arr[i] = temp;

            // Recurse for the next position.
            permute(arr, start + 1, end, fp);

            // Backtrack: swap back to restore original order.
            temp = arr[start];
            arr[start] = arr[i];
            arr[i] = temp;
        }
    }
}

int factorial(int n)
{
    int fact = 1;
    for(int i = n; i >= 1; i--)
    {
        fact *= i;
    }
    return fact;
}