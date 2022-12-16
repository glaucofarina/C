#include <stdio.h>
#include <stdlib.h>

//Variaveis globais
char jogo[3][3];
int l, c;

//procedimento para inicializar todas as posicoes da matriz
void inicializarMatriz(){           //procedimento para inicializar matriz
    for(l = 0; l < 3; l++){            //serao criadas as linhas da matriz
         for(c = 0; c < 3; c++)    //seao criadas as colunas da matriz
          jogo[l][c] = '  ';               //serao adicionados espacos vazios na matriz
    }
}

//procedimento para imprimir o jogo natela
    void imprimir(){                               /*procedimento para inicializar a matriz
        printf("\n\n\t 0   1   2\n\n");           /*imprime os numeros das colunas
            for(l = 0; l < 3; l++){                /*percorre as linhas da matriz
                for(c = 0; c < 3; c++){        /*percorre as colunas da matriz
                    if(c == 0)                         /*se c == 0 faça
                        printf("\t");                     /*tabulacao
                    printf(" %c ", jogo[l][c]);   /*imprime um caractere na tela na posicao linha e coluna
                    if(c < 2)                           /*se coluna for menor que 2 faça
                        printf("|");                     /*imprime uma barra vertical
                    if(c == 2)                         /*se coluna for igual a 2 faça
                    printf("  %d", l);                /*imprime o numero das linhas conforme o indice linha na coluna 2
                }
                if(l < 2)                                /*se linha for menor que 2 faça
                    printf("\n\t-----------");      /*imprime uma linha vertical
                printf("\n");                          /*pula uma linha para melhor espacamento
        }
        printf("\n");
}

//funcao para verificar vitoria por linha - retorno binario, 0 - nao ganhou - 1 - ganhou
int ganhouPorLinha(int l, char c){                                     //verifica a linha de indice [l] e recebe os caracteres x ou o
    if(jogo[l][0] == c && jogo[l][1] == c && jogo[l][2] == c)   //se linha (l) colunas 1, 2 e 3 forem verdadeiras return 1(ganhou) se nao return 0 (nao ganhou)
        return 1;
    else
        return 0;
}

//funcao para verificar a vitoria nas 3 linhas - retorno binario 0 - nao ganhou - 1 - ganhou
int ganhouPorLinhas(char c){                                     //recebe os caracteres x ou o
    int ganhou = 0;
    for(l = 0; l < 3; l++){
        ganhou = ganhou + ganhouPorLinha(l, c);
    }
    return ganhou;
}

//funcao para verificar a vitoria em 1 coluna - retorno binario - 0 - nao ganhou - 1 - ganhou
int ganhouPorColuna(int c, char j){
    if(jogo[0][c] == j && jogo[1][c] == j && jogo[2][c] == j)
        return 1;
    else
        return 0;
}

//funcao para verificar vitoria por colunas - retorno binario - 0 - nao ganhou - 1 - ganhou
int ganhouPorColunas(char j){
    int ganhou = 0;
    for(c = 0; c < 3; c++){
        ganhou = ganhou + ganhouPorColuna(c, j);
    }
    return ganhou;
}

//funcao para verificar vitoria na diagonal principal - 0 - nao ganhou - 1 - ganhou
int ganhouPorDiagPrin(char c){
    if(jogo[0][0] == c && jogo[1][1] == c && jogo[2][2] == c)
        return 1;
    else
        return 0;
}

//funcao para verificar vitoria na diagonal secundaria - 0 - nao ganhou - 1 - ganhou
int ganhouPorDiagSec(char c){
    if(jogo[0][2] == c && jogo[1][1] == c && jogo[2][0] == c)
        return 1;
    else
        return 0;
}

//funcao para validar cordenadas digitadas pelo usuario e garantindo que a posicao esta vazia - 0 - nao e valida - 1 - e valida
int ehValida(int l, int c){
    if(l >= 0 && l < 3 && c >= 0 && c < 3 && jogo[l][c] == ' ')
        return 1;
    else
        return 0;
}

//procedimento para ler as cordenadas do jogador
void lerCordenadas(char j){
    int linha, coluna;

    printf("Digite a linha e a coluna: ");
    scanf("%d%d", &linha, &coluna);

    while(ehValida(linha, coluna) == 0){
            printf("Cordenadas invalidas, digite a linha e a coluna: ");
            scanf("%d%d", &linha, &coluna);
     }
     jogo[linha][coluna] = j;
}

//funcao que retorna a quantidade de posicoes vazias
int quantVazias(){
    int quantidade = 0;

    for(l = 0; l < 3; l++){
         for(c = 0; c < 3; c++)
          jogo[l][c] == '  ';
          quantidade++;
   }
    return quantidade;
}

//procedimento jogar com o loop principal do jogo
void jogar(){
    int jogador = 1, vitoriaX = 0, vitoriaO = 0;
    char jogador1 = 'X', jogador2 = 'O';

    do{
        imprimir();
        if(jogador == 1){
            lerCordenadas(jogador1);
            jogador++;
            vitoriaX += ganhouPorLinhas(jogador1);
            vitoriaX += ganhouPorColunas(jogador1);
            vitoriaX += ganhouPorDiagPrin(jogador1);
            vitoriaX += ganhouPorDiagSec(jogador1);
        }
        else{
            lerCordenadas('O');
            jogador = 1;
            vitoriaO += ganhouPorLinhas(jogador2);
            vitoriaO += ganhouPorColunas(jogador2);
            vitoriaO += ganhouPorDiagPrin(jogador2);
            vitoriaO += ganhouPorDiagSec(jogador2);
        }
    }while(vitoriaX == 0 && vitoriaO == 0 && quantVazias() > 0);

    imprimir();

    if(vitoriaO == 1)
        printf("\nParabens Jogador 2, vc venceu!!!\n");
    else if(vitoriaX == 1)
        printf("\nParabens Jogador 1, vc venceu!!!\n");
    else
        printf("\nQue pena, vao se fuder!!!\n");
}

int main ( ){
    int opcao;

    do{
        inicializarMatriz();
        jogar();

        printf("\nDigite 1 para jogar novamente: ");
        scanf("%d", &opcao);
    }while(opcao == 1);


return 0;
}

