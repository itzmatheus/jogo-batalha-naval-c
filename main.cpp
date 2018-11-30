/*
Jogo Batalha Naval
Criador por Matheus Leite
*/
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdbool.h>
#include <time.h>

using namespace std;

//Metodo para limpar tela
#define LIMPA system("clear");

/*
Metodos que envolvem interacao com usuario
*/
void menu_inicial();
void jogo();

/*
Metodos genericos do tabuleiro
*/
void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]);
void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10]);
void regras();
void addBarcos(char tabuleiro[10][10]);




int main(){
    
    //Gera numeros aleatorios
    srand((unsigned)time(NULL));

    menu_inicial();

    return 0;
}

void menu_inicial(){

    int opcao = 0;
    while(opcao < 1 || opcao > 3){
        cout << "Bem vindo ao jogo!\n";
        cout << "1 => Jogar\n"
                "2 => Regras\n"
                "3 => Sobre\n"
                "4 => Sair\n"
                "Escolha uma opção e tecle ENTER: ";

        cin >> opcao;

        switch(opcao){
            case 1:
                printf("Inicia o jogo\n");
                jogo();
                break;
            case 2:
                LIMPA;
                printf("Informações do tabuleiro:\n");
                regras();
                break;
            case 3:
                printf("Quem criou foi matheus\n");
                break;
            case 4:
                printf("Obrigado por jogar! Até mais.\n");
                break;
            default:
                LIMPA;
                printf("Opção inválida. Tente novamente\n");
        }
    }


}
void regras(){
    printf(
        "* = Local desconhecido\n"
        "~ = Local com água\n"
        "P = Barco pequeno\n"
        );
}
void jogo(){
    LIMPA;
    printf("Bem vindo ao Jogo Batalha Naval!\n\n");

    //Criacao do tabuleiro
    //Tabuleiro (Mapa com os objetos implantados) e Mascara (Mapa com objetos desconhecidos)
    char tabuleiro[10][10], mascara[10][10];
    int linha, coluna; //Variaveis de navegacao
    int linSELECIONADA, colSELECIONADA; //Posicoes escolhidas pelo usuario
    bool fimJogo = false; //Jogo finalizado false

    printf("     Tabuleiro\n\n");

    //Criando tabuleiro
    iniciaTabuleiro(tabuleiro, mascara);

    //Adicionar elementos aleatorios no tabuleiro principal
    //Implantar barcos
    addBarcos(tabuleiro);

    while(fimJogo == false){
        LIMPA;
        //Exibindo tabuleiro
        exibeTabuleiro(tabuleiro, mascara);

        printf("\nDigite uma linha: ");
        scanf("%d",&linSELECIONADA);
        printf("Digite uma coluna: ");
        scanf("%d",&colSELECIONADA);

        //Revela o que esta no tabuleiro
        mascara[linSELECIONADA][colSELECIONADA] = tabuleiro[linSELECIONADA][colSELECIONADA];

    }

}
void iniciaTabuleiro(char tabuleiro[10][10],char mascara[10][10]){

    int linha, coluna; //Variaveis de navegacao

    //Construir tabuleiro
    for(linha = 0; linha < 10; linha++)
    {

        for(coluna = 0; coluna < 10; coluna++)
        {
            tabuleiro[linha][coluna] = '~';
            mascara[linha][coluna] = '*';

        }

    }


}
void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10]){

    int linha, coluna;

    printf(" 0 1 2 3 4 5 6 7 8 9 \n");

    for(linha = 0; linha < 10; linha++)
    {

        for(coluna = 0; coluna < 10; coluna++)
        {
            printf(" %c",tabuleiro[linha][coluna]);
            //printf(" %c",mascara[linha][coluna]);

        }
    printf(" %d\n",linha);
    }


        printf("\n\n 0 1 2 3 4 5 6 7 8 9 \n");

    for(linha = 0; linha < 10; linha++)
    {

        for(coluna = 0; coluna < 10; coluna++)
        {
            //printf(" %c",tabuleiro[linha][coluna]);
            printf(" %c",mascara[linha][coluna]);

        }
    printf(" %d\n",linha);
    }


}
void addBarcos(char tabuleiro[10][10]){

    //Numero de barcos
    int qtd = 10, qtdPosicionada = 0;
    int linhaALEATORIA, colunaALEATORIA;

    //verifica se ja posicionou os barcos
    while(qtdPosicionada < qtd){
        //Gera numero aleatorio de 0 ate 9
        linhaALEATORIA = rand() % 9;
        colunaALEATORIA = rand() % 9;

        //Verifica se na posicao aleatoria e agua
        if(tabuleiro[linhaALEATORIA][colunaALEATORIA] == '~')
        {
            //Se for adiciona o barco
            tabuleiro[linhaALEATORIA][colunaALEATORIA] = 'P';
            //Adiciona tambem o numero de qtd posicionada (cont)
            qtdPosicionada++;
        }
    }


}