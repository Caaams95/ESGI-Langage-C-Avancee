//
// Created by camil on 30/05/2023.
//
# include <stdio.h>
# include <stdlib.h>

# define SIZE 9

int *get_element(int *liste, int nb){
//    printf("GO get_element\n");
    for (int i = 0; i < SIZE; ++i) {
        //printf("%d\n",*(liste + i));
        if (*(liste + i) == nb)
            return  (liste+i);
    }
    return 0;
}

int main(){
    printf("=============START=============\n");

    int maListe[SIZE] = {12, 42, 53, 634, 25, 66, 77, 82, 59};
    int *liste = malloc(sizeof(int)*SIZE);
    //INIT
    for (int i = 0; i < SIZE; ++i) {
        *(liste + i) = maListe[i];
    }

    //Check avant fonction
    printf("%p\n", liste+8);
    printf("%p\n", get_element(liste, 59));

    free(liste);
    printf("==============END==============\n");
}
