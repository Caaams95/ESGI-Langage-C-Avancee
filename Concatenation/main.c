//
// Created by camil on 30/05/2023.
//
# include <stdio.h>
# include <stdlib.h>
# include <string.h>


int main(){
    printf("=============START=============\n");

    char *chaine1 = malloc( sizeof(char)*10 );
    char *chaine2 = malloc( sizeof(char)*10 );
    char *chaine3= malloc( sizeof(char)*20 );

    strcpy(chaine1, "Hello ");
    strcpy(chaine2, "World !");
//    char *chaine3 = concat(chaine1, chaine2);

    strcpy(chaine3,chaine1);
    strcat(chaine3,chaine2);

    printf("%s\n", chaine3);
    printf("==============END==============\n");

}