//
// Created by camil on 30/05/2023.
//
# include <stdio.h>
# include <stdlib.h>
# include <string.h>


int main(){
    printf("toto");



    char *chaine1 = "Hello ";
    char *chaine2 = "World !";
//    char *chaine3 = concat(chaine1, chaine2);

    strcat(chaine1,"coucou");
    printf("%s", chaine1);

}