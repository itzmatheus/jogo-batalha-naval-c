/*
Jogo Batalha Naval
Criador por Matheus Leite
*/
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

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
void iniciaTabuleiro(char tabuleiro[10][10]);
void exibeTabuleiro(char tabuleiro[10][10]);




int main(){
  
    menu_inicial();

    return 0;
}

void menu_inicial(){

    int opcao = 0;
    while(opcao < 1 || opcao > 3){
        cout << "Bem vindo ao jogo!\n";
        cout << "1 => Jogar\n"
                "2 => Sobre\n"
                "3 => Sair\n"
                "Escolha uma opção e tecle ENTER: ";

        cin >> opcao;

        switch(opcao){
            case 1:
                cout << "Inicia o jogo\n";
                jogo();
                break;
            case 2:
                cout << "Quem criou foi matheus\n";
                break;
            case 3:
                cout << "Obrigado por jogar! Até mais.\n";
                break;
            default:
                LIMPA;
                cout << "Opção inválida. Tente novamente\n";
        }
    }


}
void jogo(){
    LIMPA;
    printf("Bem vindo ao Jogo Batalha Naval!\n\n");

    //Criacao do tabuleiro
    char tabuleiro[10][10];
    int linha, coluna; //Variaveis de navegacao

    printf("                Tabuleiro\n\n");

    //Criando tabuleiro
    iniciaTabuleiro(tabuleiro);

    //Exibindo tabuleiro
    exibeTabuleiro(tabuleiro);

    printf("\n\n");

}
void iniciaTabuleiro(char tabuleiro[10][10]){

    int linha, coluna; //Variaveis de navegacao

    //Construir tabuleiro
    for(linha = 0; linha < 10; linha++)
    {

        for(coluna = 0; coluna < 10; coluna++)
        {
            tabuleiro[linha][coluna] = '*';
        }

    }


}
void exibeTabuleiro(char tabuleiro[10][10]){

    int linha, coluna;

    for(linha = 0; linha < 10; linha++)
    {

        for(coluna = 0; coluna < 10; coluna++)
        {
            printf("   %c",tabuleiro[linha][coluna]);
        }
    printf("\n\n");
    }


}