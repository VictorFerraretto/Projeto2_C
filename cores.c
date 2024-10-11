//rudmetar aind precisa de mais para mesclar com a main
#include <stdio.h>
#include <stdlib.h>

int main() {
    int back, cor;

    printf("menu");
    scanf(" %d %d",&back, &cor);

    char criacao_cor[20];

    sprintf(criacao_cor, "\x1b[%d;%dm", 40+back,30 + cor);
    printf("%s", criacao_cor);

    printf("This text will have a white background and color code  text\n");

    getchar(); // Pause the program
    return 0;
}
