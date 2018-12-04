/*

    AUTOR: Leandro Figueiredo Alves

    LEITURA E ESCRITA DE ARQUIVO UTILIZANDO UMA LISTA ENCADEADA SIMPLES

        -> AlteracAo de valores dentro da lista de acordo com o nome ou numero de jogador
        -> Salvamento da lista atualizada em arquivo

    Conteudo esperado no arquivo:

    [string qualquer],[numero]
    [string qualquer],[numero]
    ...
    [ultima linha em branco]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Tipo simples, apenas com informacoes pertinentes:
typedef struct s_type {
    char nome [50];
    int pontos;
    int NumJogadas;
    struct s_type * prox;
} JOGADOR;

JOGADOR * carregaRanking();
void imprimeLista(JOGADOR * lista);
void salvaRanking(JOGADOR * lista);
void alterapontosJogador(JOGADOR * lista, char * nome, int pontos);
JOGADOR * liberaMemoriaUltimoElementoLista(JOGADOR * lista);
void liberaMemoria(JOGADOR * lista);

//  int main() {
//     //Carrega a lista encadeada simples de jogadores a partir do arquivo:
//     JOGADOR * lista = carregaRanking();
//     //Imprime a lista encadeada simples carregada:
//     printf("Lista carregada: \n");
//     imprimeLista(lista);
//     printf("Alterando as pontos de Tainha: \n");
//     //Altera as pontos pelo nome do jogador:
//     alterapontosNomeJogador(lista, "Tainha", 50);
//     printf("Lista alterada: \n");
//     imprimeLista(lista);
//     printf("Salvando a nova lista em arquivo \n");
//     salvaRanking(lista);
//     printf("Carregando nova lista atualizada do disco \n");
//     lista = carregaRanking();
//     printf("Nova lista carregada: \n");
//     imprimeLista(lista);
//     //Altera as pontos pelo numero do jogador:
//     printf("Alterando as pontos do jogador 1: \n");
//     alterapontosNumeroJogador(lista, 1, 50);
//     printf("Lista alterada: \n");
//     imprimeLista(lista);
//     printf("Salvando a nova lista em arquivo \n");
//     salvaRanking(lista);
//     printf("Nova lista carregada: \n");
//     imprimeLista(lista);
//     printf("Liberando a memoria alocada: \n");
//     liberaMemoria(lista);
//     printf("Fim do programa.\n");
//  }
void liberaMemoria(JOGADOR * lista) {
    JOGADOR * ultimo = lista;
    while(ultimo->prox)//enquanto h� pr�ximo
        ultimo = liberaMemoriaUltimoElementoLista(lista); //elimina o �ltimo da lista
    //agora s� tem o primeiro elemento, liberar:
    free(lista);
}
JOGADOR * liberaMemoriaUltimoElementoLista(JOGADOR * lista) {
    JOGADOR * anterior = lista;
    //O ultimo n�o tem proximo:
    while (anterior->prox->prox) { //enquanto n�o for peltimo
        anterior = anterior->prox; //guarda o anterior para zerar o pornteiro para o proximo
        //aux = aux->prox; //itera
    }
    free(anterior->prox);//libera o �ltimo
    anterior->prox = 0; //remove o apontamento, zera o proximo, agora este � o ultimo elemento da lista.
    return lista;

}
void alterapontosNumeroJogador(JOGADOR * lista, int nJogador, int pontos) {
    //itera na lista ate o numero do jogador:
    JOGADOR * aux = lista;
    int i;
    for(i = 0; i < nJogador; i++, aux=aux->prox);
    aux->pontos = pontos;
}
void alterapontosNomeJogador(JOGADOR * lista, char * nome, int pontos) {
    //itera na lista:
    JOGADOR * aux = lista;
    while (aux) {
        //Se os nomes forem iguais
        if(strcmp(aux->nome, nome)==0) {
            //Altera o valor das pontos:
            aux->pontos = pontos;
            return; //Considerando que nAo ha nomes repetidos,
                    //depois de atualizar o valor pode retornar.
        }
        //itera:
        aux=aux->prox;
    }
}
void imprimeLista(JOGADOR * lista){
    int i;
    //Itera-se na lista com um auxiliar:
    JOGADOR * aux = lista;
    //Enquanto ha um auxiliar, ou enquanto ele e diferente de zero, itere:
    
    printf("\t\t\t\t          | Posição | Nome do Jogador | Nº Pontos | Nº Jogadas |\n\n");

    
    for(i=0; aux; i++, aux = aux->prox)
            printf("\t\t\t\t\t          | %d | %s | %d | %d |\n", i, aux->nome,aux->pontos, aux->NumJogadas);
            printf("\t\t\t\t\t          --------------------------------\n");

}

void salvaRanking(JOGADOR * lista) {
    FILE * arquivo = fopen("ranking.txt", "w");
    //itera na lista para ir salvando cada linha, com as infos de cada elemento:
    JOGADOR * aux = lista;
    while(aux) {
        fprintf(arquivo, "%s,%d,%d\n", aux->nome, aux->pontos,aux->NumJogadas);
        //itera:
        aux = aux->prox;
    }
    //SEMPRE fechar o arquivo:
    fclose(arquivo);
}

/*
    OBSERVAcAO: O arquivo deve ter uma ultima linha em branco.
*/
JOGADOR * carregaRanking() {
    FILE * arquivo = fopen("ranking.txt", "r");
	//Verifica abertura do arquivo:
	if(!arquivo) return 0;
    //INICIO DA LISTA
    JOGADOR * lista = (JOGADOR*) malloc (sizeof(JOGADOR));
    //Verifica alocacAo
    if(!lista) return 0;
	//Auxiliar para ler cada linha:
	char linha [60];
	//PRIMEIRO NOME
	fgets(linha, 60, arquivo);
	//Se nAo houver nenhum registro no arquivo:
	if(feof(arquivo)) {
        printf("Lista de ranking vazia.");
        return 0;
	}
	char * nome;
	//Antes da virgula, ha o nome do jogador
    nome = strtok(linha,",");
    //salva no primeiro elemento da lista:
    strcpy(lista->nome,nome);
    //Depois da virgula, vem a quantidade de pontos:
    char * s_pontos = strtok(NULL,",");
    //transforma para inteiro e salva na lista:
    lista->pontos = atoi(s_pontos);
    //printf("\t* DEBUG:\tnome lido: %s, pontos: %d\n", lista->nome, lista->pontos);
    //Numero de jogadas
    char * s_numjogadas = strtok(NULL, ",");
    //transforma para inteiro e salva na lista
    lista->NumJogadas = atoi(s_numjogadas);
    lista->prox = 0;
    //printf("Lido do arquivo, nome %s, pontos: %d, NUmJogadas: %d", lista->nome, lista->pontos, lista->NumJogadas );

    //PROXIMOS NOMES:
    fgets(linha, 60, arquivo);
    //Salva o ponteiro anterior para iterar:
    JOGADOR * anterior = lista;
    //ENQUANTO NAO FOR FIM DO ARQUIVO
    //ATENcAO, uLTIMA LINHA DEVE SER EM BRANCO PARA FUNCIONAMENTO CORRETO.
    while(!feof(arquivo)) {
        //Aloca memoria para o novo jogador lido:
        JOGADOR * novo = (JOGADOR*) malloc (sizeof(JOGADOR));
            //verifica alocacAo
            if(!novo) return 0;
        //Copiando a string lida antes da virgula, economizando variavel:
        strcpy(novo->nome,strtok(linha,","));
        //Capturando a string depois da virgula, transformando para inteiro e salvando no novo elemento da lista
        //Economizando variavel:
        novo->pontos = atoi(strtok(NULL,","));
        //Capturando a string depois da virgula, transformando para inteiro e salvando no novo elemento da lista
        //Economizando variavel:
        novo->NumJogadas = atoi(strtok(NULL,","));
        //printf("\t* DEBUG: \tnome lido: %s, pontos: %d \t numjogadas %d\n", novo->nome, novo->pontos, novo->NumJogadas);
        //Este e um novo elemento, depois dele nAo ha outro:
        novo->prox = 0;
        //O anterior, que guardava o fim da fila, agora vai apontar para o novo elemento criado:
        anterior->prox = novo;
        //Agora o novo elemento criado e o anterior, pois quando iterar sera gerado um novo elemento
		anterior = novo;
		//Antes de iterar, deve-se ler a proxima linha
        fgets(linha, 60, arquivo);
    }
    //SEMPRE fechar o arquivo:
    fclose(arquivo);
    return lista;
}