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
#include "ranking.c"

//Atalhos usados no projeto
using namespace std;
//Metodo para limpar tela
#define LIMPA system("clear");
#define P "Barco Pequeno"


/*
Metodos que envolvem interacao com usuario
*/
void menu_inicial();
void jogo();

/*
Metodos genericos do tabuleiro
*/
void ranking();
void iniciaTabuleiro(char tabuleiro[15][15], char mascara[15][15]);
void exibeTabuleiro(char tabuleiro[15][15], char mascara[15][15]);
void regras();
void addBarcos(char tabuleiro[15][15]);
void verificaTiro(char tabuleiro[15][15], char mascara[15][15], int linSELECIONADA, int colSELECIONADA, int *pontos, string *mensagem, int *tentativasPlayer);




int main(){
    
    //Gera numeros aleatorios
    srand((unsigned)time(NULL));

    menu_inicial();

    return 0;
}

void menu_inicial(){
    LIMPA;
    int opcao = 0;

    while(opcao < 1 || opcao > 3){
         printf("\t\t\t\t         ____        __        ____             _   __                  __\n");
    printf("\t\t\t\t        / __ )____ _/ /_____ _/ / /_  ____ _   / | / /___ __   ______ _/ /\n");
    printf("\t\t\t\t       / __  / __ `/ __/ __ `/ / __ \\/ __ `/  /  |/ / __ `/ | / / __ `/ / \n");
    printf("\t\t\t\t      / /_/ / /_/ / /_/ /_/ / / / / / /_/ /  / /|  / /_/ /| |/ / /_/ / /  \n");
    printf("\t\t\t\t     /_____/\\__,_/\\__/\\__,_/_/_/ /_/\\__,_/  /_/ |_/\\__,_/ |___/\\__,_/_/   \n");
        
        
                printf("\n\n");
        printf("\t\t\t\t\t\t       --------------------------------\n");
        printf("\t\t\t\t\t\t       |        MENU PRINCIPAL        |\n");
        printf("\t\t\t\t\t\t       --------------------------------\n");
        printf("\t\t\t\t\t\t       |  1. NOVO JOGO                |\n");
        printf("\t\t\t\t\t\t       |  2. INSTRUÇÕES DO JOGO       |\n");
        printf("\t\t\t\t\t\t       |  3. RANKING                  |\n");
        printf("\t\t\t\t\t\t       |  4. SAIR                     |\n");
        printf("\t\t\t\t\t\t       --------------------------------\n\n\n");
        
        
        printf("Escolha uma opção e tecle ENTER: ");

        cin >> opcao;

        switch(opcao){
            case 1:
                jogo();
                break;
            case 2:
                LIMPA;
                printf("Informações do tabuleiro:\n");
                regras();
                break;
            case 3:
                ranking();
                break;
            case 4:
                printf("Obrigado por jogar! Até mais.\n");
                return;
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
    //Criacao do tabuleiro
    //Tabuleiro (Mapa com os objetos implantados) e Mascara (Mapa com objetos desconhecidos)
    char tabuleiro[15][15], mascara[15][15];
    int linha, coluna; //Variaveis de navegacao
    int linSELECIONADA, colSELECIONADA; //Posicoes escolhidas pelo usuario
    bool fimJogo = false; //Jogo finalizado false
    int pontos = 0; //Variavei armazenara pontos
    string mensagem = "Bem vindo ao Jogo Batalha Naval\n";
    int tentativasPlayer = 0, maxTentativasPlayer = 10; //Tentativas do jogarr
    int opcao; //Variavel para armazenar opcoes de fim de jogo do usuario
    string NomeJogador; //String que ira armazenar o nome do jogador

    //Criando tabuleiro
    iniciaTabuleiro(tabuleiro, mascara);

    //Adicionar elementos aleatorios no tabuleiro principal
    //Implantar barcos
    addBarcos(tabuleiro);

    printf("Qual nome do jogador Nº 1 ?\n");
    cin >> NomeJogador;

    while(fimJogo == false){

        LIMPA;

        //Exibindo tabuleiro
        exibeTabuleiro(tabuleiro, mascara);

        //Imprime mensagens de notificacao ao(s) play(ers)
        cout << "\n" << NomeJogador << ", " << mensagem;
        printf(
            "Tentativas: %d/%d"
            " | "
            "Pontos: %d\n",tentativasPlayer,maxTentativasPlayer,pontos);
        

        //Verifica os dados inseridos
        linSELECIONADA = -1, colSELECIONADA = -1;
        while((linSELECIONADA < 0 || colSELECIONADA < 0) || (linSELECIONADA > 14 || colSELECIONADA > 14)){
        
            //Obtem os dados de linha e coluna para atirar na mascara
            printf("\n\nDigite uma linha: ");
            scanf("%d",&linSELECIONADA);
            printf("Digite uma coluna: ");
            scanf("%d",&colSELECIONADA);
        
        }

        //Verifica o que o tiro revela para pontuar
        verificaTiro(tabuleiro,mascara, linSELECIONADA, colSELECIONADA, &pontos, &mensagem, &tentativasPlayer);

        //Revela o que esta no tabuleiro
        mascara[linSELECIONADA][colSELECIONADA] = tabuleiro[linSELECIONADA][colSELECIONADA];

        //Verifica o numero de tentativas e menor que o maximo definido
        if (tentativasPlayer < maxTentativasPlayer){
            fimJogo = false;
            //Se for menor ele adiciona mais uma tentativa
            tentativasPlayer++;
        }else{
            fimJogo = true;
            mensagem = "\nLimite de tentativas atingido.\n";
        }

        //Mensagem final para o usuario apos terminar todas as tentativas
        cout << mensagem;
        printf("Você fez %d pontos!\n\n",pontos);
    }

    printf("O que desejas :\n"
    "1 => Jogar novamente\n"
    "2 => Ir para o menu principal\n"
    "3 => Sair\n"
    
    "Escolha: ");
    
    scanf("%d",&opcao);
    switch(opcao){
        case 1:
            jogo();
            break;
        case 2:
            menu_inicial();
            break;
        case 3:
            printf("Obrigado por jogar. Volte depois :)");
            return;
        default:
            printf("Opção inválida");
    }

}

void ranking(){
    //Carrega a lista encadeada simples de jogadores a partir do arquivo:
    JOGADOR * lista = carregaRanking();
    //Imprime a lista encadeada simples carregada:
    printf("Lista carregada: \n");
    imprimeLista(lista);
    printf("Alterando as vitorias de Tainha: \n");
    char nome[7] = "TAINHA";
    //Altera as vitorias pelo nome do jogador:
    alteraVitoriasNomeJogador(lista, nome, 50);
    printf("Lista alterada: \n");
    imprimeLista(lista);
    printf("Salvando a nova lista em arquivo \n");
    salvaRanking(lista);
    printf("Carregando nova lista atualizada do disco \n");
    lista = carregaRanking();
    printf("Nova lista carregada: \n");
    imprimeLista(lista);
    //Altera as vitorias pelo numero do jogador:
    printf("Alterando as vitorias do jogador 1: \n");
    alteraVitoriasNumeroJogador(lista, 1, 50);
    printf("Lista alterada: \n");
    imprimeLista(lista);
    printf("Salvando a nova lista em arquivo \n");
    salvaRanking(lista);
    printf("Nova lista carregada: \n");
    imprimeLista(lista);
}

void verificaTiro(char tabuleiro[15][15],char mascara[15][15],int linSELECIONADA, int colSELECIONADA, int *pontos, string *mensagem, int *tentativasPlayer){
    
    //Verifica se a posicao ja foi encontrada
    
    if (mascara[linSELECIONADA][colSELECIONADA] == '*') {
        
        //Verifica se encontrou algo no tiro
        switch(tabuleiro[linSELECIONADA][colSELECIONADA]){
            case 'P':
                *pontos += 10;
                *mensagem = "\nVocê encontrou um Barco Pequeno [+ 10 pontos]\n";
                break;
            case '~':
                *mensagem = "\nVocê encontrou ÁGUA [+0 pontos]\n";
                *pontos += 0;
                break;
            case 'M':
                *pontos += 20;
                *mensagem = "\n Você encontrou um Barco Médio [+ 20 pontos]\n";
                break;
            default:
                *mensagem = "\nPosição inexistente\n";
                *pontos += 0;
                break;
        }
    }else{
        *mensagem = "\nPosicao já encontrada. Tente outra!!!\n";
        *pontos += 0;
        *tentativasPlayer -= 1;
    }
    
}

void iniciaTabuleiro(char tabuleiro[15][15],char mascara[15][15]){

    int linha, coluna; //Variaveis de navegacao

    //Construir tabuleiro
    for(linha = 0; linha < 15; linha++)
    {

        for(coluna = 0; coluna < 15; coluna++)
        {
            tabuleiro[linha][coluna] = '~';
            mascara[linha][coluna] = '*';

        }

    }


}
void exibeTabuleiro(char tabuleiro[15][15], char mascara[15][15]){

    int linha, coluna;

    //Imprime o tabuleiro de colunas
    printf("   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14");

    printf("\n");

    for(linha = 0; linha < 15; linha++)
    {

        //Imprime o tabuleiro de linhas
        if(linha < 10){
            printf("%d ",linha);

        }else{
            printf("%d",linha);
        }
        for(coluna = 0; coluna < 15; coluna++)
        {
            printf(" %c ",mascara[linha][coluna]);

        }
    printf("\n");
    }

    //Imprime o tabuleiro de colunas
    printf("\n   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14");

    printf("\n");

    for(linha = 0; linha < 15; linha++)
    {
        
        //Imprime o tabuleiro de linhas
        if(linha < 10){
            printf("%d ",linha);

        }else{
            printf("%d",linha);
        }
        for(coluna = 0; coluna < 15; coluna++)
        {
            printf(" %c ",tabuleiro[linha][coluna]);

        }
    printf("\n");
    }


}
void addBarcos(char tabuleiro[15][15]){

    //Numero de barcos
    int qtdPequeno = 10, qtdMedio = 5, qtdPosicionada = 0;//Qtd de barcos
    int linhaALEATORIA, colunaALEATORIA;

    //add barcos pequenos "P"
    //verifica se ja posicionou os barcos
    while(qtdPosicionada < qtdPequeno){
        //Gera numero aleatorio de 0 ate 14
        linhaALEATORIA = rand() % 14;
        colunaALEATORIA = rand() % 14;

        //Verifica se na posicao aleatoria e agua
        if(tabuleiro[linhaALEATORIA][colunaALEATORIA] == '~')
        {
            //Se for adiciona o barco
            tabuleiro[linhaALEATORIA][colunaALEATORIA] = 'P';
            //Adiciona tambem o numero de qtdPequeno posicionada (cont)
            qtdPosicionada++;
        }
    }

    qtdPosicionada = 0;
    //add barcos Medios "M"
    //verifica se ja posicionou os barcos
    while(qtdPosicionada < qtdMedio){
        //Gera numero aleatorio de 0 ate 14
        linhaALEATORIA = rand() % 14;
        colunaALEATORIA = rand() % 14;

        //Verifica se na posicao aleatoria e agua
        if(tabuleiro[linhaALEATORIA][colunaALEATORIA] == '~')
        {
            //Se for adiciona o barco
            tabuleiro[linhaALEATORIA][colunaALEATORIA] = 'M';
            //Adiciona tambem o numero de qtdPequeno posicionada (cont)
            qtdPosicionada++;
        }
    }



}