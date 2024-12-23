#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

#define max_usu 100
char cpf_lista[max_usu][12];
char senha_lista[max_usu][12];
int indice;
float carteira[max_usu];
char cpf[12],senha[7];
int i=0;
typedef struct {

    int vermelho;
    int amarelo;
    int azul;
    int verde;
    int ciano;
    int roxo;
} item;
item itens[100];

//ATUALIZAÇÃO
void atualização(float *carteira){
  FILE *carteiraarqui;
  FILE *cores;
  carteiraarqui = fopen("carteira.bin","wb");
  size_t escrevendo =fwrite(carteira, sizeof(carteira), max_usu, carteiraarqui);
  fclose(carteiraarqui);
    cores = fopen("itens.bin","wb");
    fwrite(itens,sizeof(item),100,cores);
    fclose(cores);

}

// MOSTRAR INVENTARIO
void seu_inventario( item *itens){
    int x;

    printf("===========Inventário===========\n");
    printf("| REAIS: %.2f\n", carteira[indice]);
    printf("| ITENS: \x1b[0m\n");
    printf("|-------------------------------\n");
    printf("| 1- Normal (para sair clique sem alteração escolha esse!!)\n");
    if (itens[indice].vermelho == 0){
        printf("|\033[31;9m 2- Vermelho \033[0m\n");
    }
    else{
        printf("|\x1b[31m 2- Vermelho\033[0m\n");
    }
    if (itens[indice].amarelo == 0){
        printf("|\033[33;9m 3- Amarelo \033[0m\n");
    }  
    else{
        printf("|\033[33m 3- Amarelo\033[0m\n");
    } 
    if (itens[indice].azul == 0){
        printf("|\033[34;9m 4- Azul \033[0m\n");
    } 
    else{
        printf("|\033[34m 4- Azul\033[0m\n");
    }  
    if (itens[indice].verde == 0){
        printf("|\033[32;9m 5- Verde \033[0m\n");
    }  
    else{
        printf("|\033[32m 5- Verde\033[0m\n");
    } 
    if (itens[indice].ciano == 0){
        printf("|\033[36;9m 6- Ciano \033[0m\n");
    } 
    else{
        printf("|\033[36m 6- Ciano\033[0m\n");
    }  
    if (itens[indice].roxo == 0){
        printf("|\033[35;9m 7- Roxo \033[0m\n");
    }
    else{
        printf("|\033[35m 7- Roxo\033[0m\n");
    }
    printf("| ");
    while(1){
        scanf("%d",&x);

    switch (x){
    case 1:
      printf("\x1b[0m");
      return;
    case 2:
      if (itens[indice].vermelho == 0){
        printf("Essa cor está bloqueada, para desbloquear compre na loja!\n");
        continue;
      }
      else{
      printf("\x1b[31m");
      return;
      }
    case 3:
      if (itens[indice].amarelo == 0){
        printf("Essa cor está bloqueada, para desbloquear compre na loja!\n");
        continue;
      }
      else{
    printf("\x1b[33m");
      return;
      }
    case 4:
          if (itens[indice].azul == 0){
        printf("Essa cor está bloqueada, para desbloquear compre na loja!\n");
        continue;
      }
      else{
        printf("\x1b[34m");
        return;
      }
    case 5:
          if (itens[indice].verde == 0){
        printf("Essa cor está bloqueada, para desbloquear compre na loja!\n");
        continue;
      }
      else{
        printf("\x1b[32m");
        return;
      }
    case 6:
          if (itens[indice].ciano == 0){
        printf("Essa cor está bloqueada, para desbloquear compre na loja!\n");
        continue;
      }
      else{
        printf("\x1b[36m");
        return;
      }
    case 7:
      if (itens[indice].roxo == 0){
        printf("Essa cor está bloqueada, para desbloquear compre na loja!\n");
        continue;
      }
      else{
        printf("\x1b[35m");
        return;
      }
    default:
    return;



    }
  }
}

// ADICIONAR RESULTADO AO HISTÓRICO
void adicionar_historico(const char* cpf, const char* tipo_jogo, const char* resultado, float valor_apostado) {
    char nome_arquivo[30];
    sprintf(nome_arquivo, "historico.txt"); 

    FILE *arquivo = fopen(nome_arquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de histórico.\n");
        return;
    }

    fprintf(arquivo, "%s Tipo de Jogo: %s | Resultado: %s | Valor Apostado: R$%.2f\n", cpf, tipo_jogo, resultado, valor_apostado);




    fclose(arquivo);
}

// EXIBIR HISTÓRICO
void historico(const char* cpf) {
    char nome_arquivo[30];


    FILE *arquivo = fopen("historico.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de histórico.\n");
        return;
    }

    char linha[100];
    printf("\n=========== HISTÓRICO ===========\n");
    while (fgets(linha, sizeof(linha),arquivo) != NULL) {

        char *espaco = strchr(linha, ' '); 
        if (espaco != NULL) {
            *espaco = '\0'; 

            if (strcmp(linha, cpf) == 0) {
                printf("%s", espaco + 1); 
            }
        }
    }
    fclose(arquivo);
    printf("===================================\n");
    printf("\n<--- volte com 'ENTER'\n");
    getchar();
}


// DEPOSITAR 
void depositar(float *carteira) {
    float valor;
  while(1){
    printf("Quanto deseja depositar (ou 0 para não depositar), MAX(R$5000.00):\n");
    scanf("%f", &valor);

    if (valor < 0) {
        printf("Valor inválido. O depósito deve ser positivo.\n");
    } else if (valor > 5000) {
        printf("O valor máximo para depósito é R$5000.00.\n");
    } else {
        carteira[indice] += valor; 
        printf("Depósito de R$%.2f realizado com sucesso!\n", valor);
        break;
    }
  }
  printf("\n<--- volte com 'ENTER'\n");
  getchar();
};

// SACAR
void sacar(float *carteira) {

    float valor;
    char sen[6];
    while(1){

        printf("Quanto deseja sacar (ou 0 para não depositar): ");
        scanf("%f", &valor);


        if (valor > carteira[indice]) {
            printf("ERRO: Você não pode sacar dinheiro a mais do que o disponível em sua carteira!! (carteira: %.2f)\n",
                  carteira[indice]);


        }
        else{
        carteira[indice] -= valor;
        printf("Saque de R$%.2f realizado com sucesso!\n", valor);
        break;
        }
    }


  printf("\n<--- volte com 'ENTER'\n");
  getchar();
}

//LOJA
void loja(float *carteira){
  int x;
  printf("==============LOJA==============\n");
  printf("1- Vermelho (R$10.000)\n");
  printf("2- Amarelo (R$15.000)\n");
  printf("3- Azul (20.000)\n");
  printf("4- Verde (R$25.000)\n");
  printf("5- Ciano (R$30.000)\n");
  printf("6- Roxo (R$35.000)\n");
 printf("===============================\n");
 printf("Digite a cor você quer comprar ('0' se nenhuma): ");
 while (1){
 scanf("%d", &x);
  switch (x){
  case 1:
    if (carteira[indice]< 10000){
      printf("Saldo Insuficiente!!\n");
      continue;
    }
    else if(itens[indice].vermelho==1){
      printf("Esta cor ja foi comprada!!\n");
      continue;
    }  
    else{
      printf("Obrigado pela compra!\n");
      carteira[indice]-=10000;
      itens[indice].vermelho=1;
      return;
    }
  case 2:
    if (carteira[indice]< 15000){
      printf("Saldo Insuficiente!!\n");
      continue;
    }
    else if(itens[indice].amarelo==1){
      printf("Esta cor ja foi comprada!!\n");
      continue;
    }
    else{
      printf("Obrigado pela compra!\n");
      carteira[indice]-=15000;
      itens[indice].amarelo=1;
      return;
    }  
  case 3:
    if (carteira[indice]< 20000){
      printf("Saldo Insuficiente!!\n");
      continue;
    }
    else if(itens[indice].azul==1){
      printf("Esta cor ja foi comprada!!\n");
      continue;
    }
    else{
      printf("Obrigado pela compra!\n");
      carteira[indice]-=20000;
      itens[indice].azul=1;
      return;
    } 
  case 4:
    if (carteira[indice]< 25000){
      printf("Saldo Insuficiente!!\n");
      continue;
    }
    else if(itens[indice].verde==1){
      printf("Esta cor ja foi comprada!!\n");
      continue;
    }
    else{
      printf("Obrigado pela compra!\n");
      carteira[indice]-=25000;
      itens[indice].verde=1;
      return;
    }  
  case 5:
    if (carteira[indice]< 30000){
      printf("Saldo Insuficiente!!\n");
      continue;
    }
    else if(itens[indice].ciano==1){
      printf("Esta cor ja foi comprada!!\n");
      continue;
    }
    else{
      printf("Obrigado pela compra!\n");
      carteira[indice]-=30000;
      itens[indice].ciano=1;
      return;
    }  
  case 6:
    if (carteira[indice]< 35000){
      printf("Saldo Insuficiente!!\n");
      continue;
    }
    else if(itens[indice].roxo==1){
      printf("Esta cor ja foi comprada!!\n");
      continue;
    }
    else{
      printf("Obrigado pela compra!\n");
      carteira[indice]-=35000;
      itens[indice].roxo=1;
      return;
    }

  default:
    return;
  }
}
}
// ARQUIVOS 
void iniciacao_arquivos(float *carteira){
  FILE *arquivoini;
  FILE *arquivoini2;
  FILE *carteiraarqui;
  FILE *cores;
  char compiler[2000];


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

  carteiraarqui = fopen("carteira.bin","rb");
  fread(carteira, sizeof(float), max_usu, carteiraarqui);
  fclose(carteiraarqui);
    cores = fopen("itens.bin","rb");
    size_t lendo = fread(itens,sizeof(item),100,cores);
    fclose(cores);
}

void login(int *indice){
  int x;
  while (1){
  printf("Olá, por acaso você já é cadastrado?\n");
  printf("1- Sim ou 2-Não\n");
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

    iniciacao_arquivos(carteira);
  }

  else{
    printf("Opção inválida!\n");
  }
}
}

// APOSTA
int apostar(float *carteira){
  float aposta;
  while(1){
  printf("\n=================APOSTA=================\n");
  printf("Antes de jogar quanto você gostaria de apostar?\n");
  printf("Valor: ");
  scanf("%f", &aposta);
    if (aposta> carteira[indice]){
      printf("Você não tem dinheiro suficiente para apostar esse valor!!\n");

    }
    else{
      break;
    }
  }
  return aposta;
}

// GUESS
void guess(float *carteira){
    float aposta= apostar(carteira);
    carteira[indice] -= aposta;
    int num_adv;
    printf("\n=========== ADIVINHE ==========\n");
    sleep(1);
    printf("==    Você terá 5 chances!   ==\n");
    sleep(1.5);
    printf("==  escolhendo um número ... ==\n");
    sleep(2.5);
    srand(time(NULL));
    int num_escolhido = rand() % 100 +1;
    printf("\n  Adivinhe um número de 1 a 100:\n");

    for (int i = 0;i<5;i++){
    scanf("%d", &num_adv);
    if (i== 4){
            sleep(2);
            if (num_adv != num_escolhido){
                printf("--JOGO PERDIDO :( , O número escolhido era %d--\n", num_escolhido);
                printf("Como você apostou R$%.2f, logo você perdeu R$%.2f.\n",aposta,aposta);
                printf("====================================");
                sleep(2);
                adicionar_historico(cpf,"Adivinhe", "Derrota", aposta);
            }
            else {
                printf("***UFA!! Você ACERTOU!!!***\n");
                printf("Como você apostou R$%.2f você ganha + R$%.2f.\n",aposta,aposta *3);
                printf("====================================");
                sleep(2);
                adicionar_historico(cpf,"Adivinhe", "Vitória", aposta);
                carteira[indice] += aposta * 4;
                break;
            }
    }

    else{
    if (num_adv < num_escolhido){
        sleep(1.5);
        printf("--incorreto, tente um número MAIOR!--\n");
    }
    else if (num_adv> num_escolhido){
        sleep(1.5);
        printf("--Incorreto, tente um número MENOR!--\n");
    }
    else if (num_adv == num_escolhido){
        sleep(2);
        printf("***Parabéns você ACERTOU!!!***\n");
        printf("Como você apostou R$%.2f você ganha + R$%.2f.\n",aposta,aposta *3);
        printf("====================================");
        sleep(2);
        adicionar_historico(cpf,"Adivinhe", "Vitória", aposta);
        carteira[indice] += aposta * 4;
        break;
    }
    }

}
}


// DICE
void dice(float *carteira){
    int dados[4] = {};
    float aposta= apostar(carteira);
    carteira[indice] -= aposta;
    printf("\n===========DADOS===========\n");
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
    printf("\n-------------------------\n");
    int pontos_mesa = dados[2] + dados[3];
    if (pontos_player < pontos_mesa){
        printf("Que pena!! você PERDEU :(\n");
        printf("Como você apostou R$%.2f você perdeu - R$%.2f.\n",aposta,aposta);
        printf("============================\n");
        adicionar_historico(cpf,"Dados", "Derrota", aposta);
    }
    else if (pontos_player> pontos_mesa){
        printf("Parabens, você ganhou!!\n");
        printf("Como você apostou R$%.2f você ganha + R$%.2f.\n",aposta,aposta);
        carteira[indice] += aposta * 2;
        printf("============================\n");
        adicionar_historico(cpf,"Dados", "Vitória", aposta);
    }
    else if (pontos_player == pontos_mesa){
        printf("UAU!! vocês EMPATARAM.\n");
        printf("Como você apostou R$%.2f você receberá R$%.2f de volta.\n",aposta,aposta);
        carteira[indice] += aposta;
        printf("============================\n");
        adicionar_historico(cpf,"Dados", "Empate", aposta);
    }
    sleep(2);

}

// MENU DE JOGOS
void menu_jogos(){

  int cont;

  while(1){
    printf("\n");
    printf("=============JOGOS==========\n");
    printf("--------------------------\n");
    printf("-> 1-Dados (2x)\n");
    printf("-> 2-Adivinhe (4x)\n");
    printf("-> 3-Volte para o menu\n");
    printf("============================\n");
    scanf("%d", &cont);
    printf("\n");
    switch (cont){
      case 1:
        dice(carteira);
        atualização(carteira);
        getchar();
        break;
      case 2:
        guess(carteira);
        atualização(carteira);
        getchar();
        break;
      case 3:
        return;
    };

  };
};


// MENU PRINCIPAL
void menu(){

  int cont;

  while(1){
    printf("\n");
    printf("=============MENU==========\n");
    printf("O que você deseja acessar?\n");
    printf("--------------------------\n");
    printf("-> 1-Jogar\n");
    printf("-> 2-Seu inventário\n");
    printf("-> 3-Depositar\n");
    printf("-> 4-Sacar\n");
    printf("-> 5-Loja\n");
    printf("-> 6-Histórico\n");
    printf("-> 7-Sair\n");
    printf("===========================\n");
    scanf("%d", &cont);
    printf("\n");


      switch (cont){
      case 1:
        menu_jogos();
        getchar();
        break;
      case 2:
        seu_inventario(itens);
        getchar();
        break;
      case 3:
        depositar(carteira);
        atualização(carteira);
        getchar();
        break;
      case 4:
        sacar(carteira);
        atualização(carteira);
        getchar();
        break;
      case 5:
        loja(carteira);
        atualização(carteira);
        break;
      case 6:
        historico(cpf);
        getchar();
        break;
      case 7:
        printf("DESCONECTANDO...\n");
        printf("\x1b[0m");
        return;
    }
  }
}
int main(){
  setlocale(LC_ALL, "Portuguese");
  iniciacao_arquivos(carteira);
  login(&indice);
  menu();
  return 0;
}
