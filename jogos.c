#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#define max_usu 100
char cpf_lista[max_usu][12];
char senha_lista[max_usu][12];
int indice;
char cpf[12],senha[7];
void iniciacao_arquivos(){
  FILE *arquivoini;
  FILE *arquivoini2;
  char compiler[2000];
  int i=0;

  arquivoini = fopen("login.txt","r");
  for (int i=0;i<max_usu && fgets(compiler, sizeof(compiler), arquivoini);i++) {
      compiler[strcspn(compiler, "\n")] = 0; 

      strcpy(cpf_lista[i], compiler); 

  }
  fclose(arquivoini);

  arquivoini2 = fopen("senhas.txt","r");
  for (int i=0;i<max_usu && fgets(compiler, sizeof(compiler), arquivoini2);i++) {
    compiler[strcspn(compiler, "\n")] = 0; 

    strcpy(senha_lista[i], compiler); 

  }
  fclose(arquivoini2);
}

void login(int *indice){
  int x;
  while (1){
  printf("Olá, por acaso você já é cadastrado?\n");
  printf("1- Sim ou 2-Não");
  scanf("%d",&x);
  if (x== 1){
  
    printf("BEM VINDO!!\n");
    printf("Digite seu CPF: ");
    scanf("%11s", cpf);
    printf("Digite sua senha: ");
    scanf("%6s", senha);

    for (int i = 0; i < max_usu; i++) {
      if (strcmp(cpf_lista[i], cpf)== 0) {
        if (strcmp(senha_lista[i],senha)==0){
          printf("\nLogin realizado com sucesso!\n");
          *indice = i;
          return;
        }



      }
    }
    printf("\nCPF ou senha incorretos!\n");

  
  }
  else if (x== 2){
    char login[12],pass[7];
    FILE *arquivo;
    FILE *arquivo2;
    printf("Vamos cadastrar você!\n");
    printf("Digite seu CPF: ");
    scanf("%11s", login);
    printf("Crie uma senha: ");
    scanf("%6s", pass);

    printf("\nÓtimo você foi cadastrado !!!\n");
    
    arquivo = fopen("login.txt","a");
    fprintf(arquivo,"%s\n",login);
    fclose(arquivo);
    arquivo2 = fopen("senhas.txt","a");
    fprintf(arquivo2,"%s\n",pass);
    fclose(arquivo2);
    
    iniciacao_arquivos();
  }
  
  else{
    printf("Opção inválida!\n");
  }
}
}
int main(){
  setlocale(LC_ALL, "Portuguese");
  iniciacao_arquivos();
  login(&indice);

  printf("%s // %s\n",cpf_lista[indice],senha_lista[indice]);
  printf("indice: %d",indice);
    
}
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
