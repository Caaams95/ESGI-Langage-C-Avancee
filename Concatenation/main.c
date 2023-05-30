//
// Created by camil on 30/05/2023.
//
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char *concat(char *chaine1, char *chaine2){
    strcat(chaine1,chaine2);
    return chaine1;
}

int main(){
    printf("=============START=============\n");

    char *chaine1 = malloc( sizeof(char)*10 );
    char *chaine2 = malloc( sizeof(char)*10 );

    strcpy(chaine1, "Hello ");
    strcpy(chaine2, "World !");

    char *chaine3 = concat(chaine1, chaine2);

    printf("%s", chaine3);
    printf("\n==============END==============\n");

}