#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
void guess(){
    int num_adv;
    printf("=========== ADIVINHE ==========\n");
    printf("==    Você terá 5 chances!   ==\n");
    printf("==  escolhendo um número ... ==\n");
    srand(time(NULL));
    int num_escolhido = rand() % 100 +1;
    printf("\n  Adivinhe um número de 1 a 100:\n");

    for (int i = 0;i<5;i++){
    scanf("%d", &num_adv);
    if (i== 4){
            if (num_adv != num_escolhido){
                printf("--JOGO PERDIDO :( , O número escolhido era %d--\n", num_escolhido);
            }
            else {
                printf("***UFA!! Você ACERTOU!!!***\n");
                break;
            }
    }
    
    else{
    if (num_adv < num_escolhido){
        printf("--incorreto, tente um número MAIOR!--\n");
    }
    else if (num_adv> num_escolhido){
        printf("--Incorreto, tente um número MENOR!--\n");
    }
    else if (num_adv == num_escolhido){
        printf("***Parabéns você ACERTOU!!!***\n");
        break;
    }
    }
    
}
}
//dados
void dice(){
    int dados[4] = {};
   
    printf("\n===========APOSTE===========\n");
    srand(time(NULL));
    for (int i = 0; i<4;i++){

         dados[i]= rand() % 6 + 1;

    }
    printf ("Você joga os dados ...\n");
    sleep(1);
    printf("Você tira %d e %d\n",dados[0] ,dados[1]);
    sleep(1.5);
    int pontos_player= dados[0] + dados[1];
    printf ("A mesa joga os dados ...\n");
    sleep(2);
    printf("Ela tira %d e %d\n",dados[2] ,dados[3]);
    sleep(1);
    int pontos_mesa = dados[2] + dados[3];
    if (pontos_player < pontos_mesa){
        printf("Que pena!! você PERDEU :(\n");
        printf("============================\n");
    }
    else if (pontos_player> pontos_mesa){
        printf("Parabens, você ganhou!!\n");
        printf("============================\n");
    }
    else if (pontos_player == pontos_mesa){
        printf("UAU!! vocês tiraram o mesmo número.\n");
        printf("============================\n");
    }

}
