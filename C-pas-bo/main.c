#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Hello, World!\n");
    int *tableau = malloc(sizeof (int) * 10);

    for (int i = 0; i < 10; ++i){
        *(tableau + i) = i + 10;    }

    for (int i = 0; i < 10; ++i){
        printf("tableau[%d] : %d\n", i, *(tableau + i));
    }


    return 0;
}
