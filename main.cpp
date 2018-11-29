#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

#define LIMPA system("clear");

void menu_inicial();

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