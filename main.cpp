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
void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]);
void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10]);
void regras();
void addBarcos(char tabuleiro[10][10]);
void verificaTiro(char tabuleiro[10][10], int linSELECIONADA, int colSELECIONADA, int *pontos, string *mensagem);




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
        cout << "Bem vindo ao jogo!\n";
        cout << "1 => Jogar\n"
                "2 => Regras\n"
                "3 => Sobre\n"
                "4 => Sair\n"
                "Escolha uma opção e tecle ENTER: ";

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
                printf("Quem criou foi matheus\n");
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
    char tabuleiro[10][10], mascara[10][10];
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
        
        //Obtem os dados de linha e coluna para atirar na mascara
        printf("\n\nDigite uma linha: ");
        scanf("%d",&linSELECIONADA);
        printf("Digite uma coluna: ");
        scanf("%d",&colSELECIONADA);

        //Verifica o que o tiro revela para pontuar
        verificaTiro(tabuleiro, linSELECIONADA, colSELECIONADA, &pontos, &mensagem);

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

void verificaTiro(char tabuleiro[10][10], int linSELECIONADA, int colSELECIONADA, int *pontos, string *mensagem){
    switch(tabuleiro[linSELECIONADA][colSELECIONADA]){
        case 'P':
            *pontos += 10;
            *mensagem = "\nVocê encontrou um Barco Pequeno [+ 10 pontos]\n";
            break;
        case '~':
            *mensagem = "\nVocê encontrou ÁGUA [0 pontos]\n";
            *pontos += 0;
            break;
        default:
            *mensagem = "\nPosição inexistente\n";
            *pontos += 0;
            break;
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

    //Imprime o tabuleiro de colunas
    for(int i = 0; i < 10; i++)
    {
        printf(" %d",i);
    }
    
    printf("\n");

    for(linha = 0; linha < 10; linha++)
    {

        //Imprime o tabuleiro de linhas
        printf("%d",linha);

        for(coluna = 0; coluna < 10; coluna++)
        {
            printf(" %c",mascara[linha][coluna]);

        }
    printf("\n");
    }

    //Imprime o tabuleiro de colunas
    for(int i = 0; i < 10; i++)
    {
        printf(" %d",i);
    }

    printf("\n");

    for(linha = 0; linha < 10; linha++)
    {
        
        //Imprime o tabuleiro de linhas
        printf("%d",linha);

        for(coluna = 0; coluna < 10; coluna++)
        {
            printf(" %c",tabuleiro[linha][coluna]);

        }
    printf("\n");
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