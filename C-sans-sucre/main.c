#include <stdio.h>
#include <stdlib.h>


int main() {
    int size;
    printf("Saisis un nombre : \n");
    scanf("%d", &size);


    // Allocation dynamique de la mémoire pour le tableau à 2 dimensions
    char **array = malloc(size * sizeof(char *));
    for (int i = 0; i < size; ++i) {
        *(array + i) = malloc(size * sizeof(char));
    }

    // Initialisation des valeurs du tableau à 2 dimensions
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i==0 || i==size-1){
                *(*(array + i) + j) = '#';
            }else{
                if (j==0 || j==size-1){
                    *(*(array + i) + j) = '#';
                }else{
                    if (i==j || i+j==size-1){
                        *(*(array + i) + j) = 'X';
                        *(*(array + size-i-1) + j) = 'X';
                    }else{
                        *(*(array + i) + j) = ' ';
                    }
                }
            }
        }
    }

    // Affichage du tableau
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%c", *(*(array + i) + j));
        }
        printf("\n");
    }

    // Libération de la mémoire allouée
    for (int i = 0; i < size; i++) {
        free(*(array + i));
    }
    free(array);
    return 0;
}
