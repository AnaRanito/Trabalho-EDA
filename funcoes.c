/*!
 *  @file funcoes.c
 *  @author Rita Ranito
 *  @date 2025-03-30
 *  @project Projeto Gestão de Antenas
 *
 *  Implementação funcões.
 *
 *
 *
 */

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Cria dinamicamente uma nova antena com os dados fornecidos.
 */
Antena* criarAntena(char frequencia, int x, int y) {
    Antena* novaAntena = (Antena*)malloc(sizeof(Antena));
    if (!novaAntena) {
        printf("Erro de alocação de memória.\n");
        return NULL;
    }
    novaAntena->frequencia = frequencia;
    novaAntena->x = x;
    novaAntena->y = y;
    novaAntena->proxima = NULL;
    return novaAntena;
}

/**
 * Insere uma nova antena no início da lista ligada.
 */
void inserirAntena(Antena **cabeca, char frequencia, int x, int y) {
    Antena* novaAntena = criarAntena(frequencia, x, y);
    if (!novaAntena) return;

    // Inserção no início: o novo nó aponta para a antiga cabeça
    novaAntena->proxima = *cabeca;

    // Atualiza a cabeça para o novo nó
    *cabeca = novaAntena;
}

/**
 * Procura e remove uma antena com frequência e coordenadas específicas.
 */
void removerAntena(Antena **cabeca, char frequencia, int x, int y) {
    Antena *temp = *cabeca, *anterior = NULL;

    // Percorre a lista até encontrar a antena a remover
    while (temp != NULL && (temp->frequencia != frequencia || temp->x != x || temp->y != y)) {
        anterior = temp;
        temp = temp->proxima;
    }

    // Se não encontrou, termina
    if (temp == NULL) return;

    // Se for o primeiro elemento da lista
    if (anterior == NULL)
        *cabeca = temp->proxima;
    else
        anterior->proxima = temp->proxima;

    free(temp); // Liberta memória
}

/**
 * Lê um ficheiro de texto linha a linha, criando antenas para cada caracter diferente de '.'.
 */
Antena* carregarDeFicheiro(const char* nomeFicheiro, int *linhas, int *colunas) {
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (!ficheiro) {
        printf("Erro ao abrir o ficheiro!\n");
        return NULL;
    }

    Antena *cabeca = NULL;
    char linha[512];
    int y = 0; // Linha atual
    *colunas = 0;
    *linhas = 0;

    // Lê cada linha do ficheiro
    while (fgets(linha, sizeof(linha), ficheiro)) {
        int x = 0;
        int colunas_linha = 0;

        // Lê cada caractere da linha
        for (int i = 0; linha[i] != '\0' && linha[i] != '\n'; i++) {
            char c = linha[i];

            // Cria antena se o caractere não for ponto
            if (c != '.') {
                inserirAntena(&cabeca, c, x, y);
            }
            x++;
            colunas_linha++;
        }

        // Atualiza o número máximo de colunas
        if (colunas_linha > *colunas) {
            *colunas = colunas_linha;
        }

        y++; // Próxima linha
    }

    *linhas = y;
    fclose(ficheiro);
    return cabeca;
}

/**
 * Mostra no terminal todas as antenas guardadas na lista.
 */
void exibirAntenas(Antena *cabeca) {
    printf("Lista de Antenas:\n");
    while (cabeca) {
        printf("Frequência: %c, Coordenadas: (%d, %d)\n", cabeca->frequencia, cabeca->x, cabeca->y);
        cabeca = cabeca->proxima;
    }
}

/**
 * @brief Cria e imprime uma matriz com antenas e interferências calculadas.
 *
 * Esta função inicializa uma matriz com pontos vazios ('.'), posiciona
 * as antenas com base nas coordenadas armazenadas na lista ligada,
 * e calcula os pontos de interferência entre antenas da mesma frequência,
 * marcando-os com '#'. No final, imprime a matriz no terminal.
 */
void calcularEdesenharMatriz(Antena *cabeca, int linhas, int colunas) {
    // Inicializa a matriz com '.'
    char matriz[linhas][colunas];
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = '.';
        }
    }

    // Coloca cada antena na matriz
    for (Antena *temp = cabeca; temp != NULL; temp = temp->proxima) {
        matriz[temp->y][temp->x] = temp->frequencia;
    }

    // Verifica pares de antenas com mesma frequência
    for (Antena *a1 = cabeca; a1 != NULL; a1 = a1->proxima) {
        for (Antena *a2 = a1->proxima; a2 != NULL; a2 = a2->proxima) {
            if (a1->frequencia == a2->frequencia) {
                // Calcula vetor de deslocamento entre antenas
                int dx = a2->x - a1->x;
                int dy = a2->y - a1->y;

                // Aplica o vetor inversamente
                int x1 = a1->x - dx;
                int y1 = a1->y - dy;
                if (x1 >= 0 && x1 < colunas && y1 >= 0 && y1 < linhas && matriz[y1][x1] == '.')
                    matriz[y1][x1] = '#';

                // Aplica o vetor diretamente
                int x2 = a2->x + dx;
                int y2 = a2->y + dy;
                if (x2 >= 0 && x2 < colunas && y2 >= 0 && y2 < linhas && matriz[y2][x2] == '.')
                    matriz[y2][x2] = '#';
            }
        }
    }

    // Imprime a matriz no terminal
    printf("\nMapa da matriz:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}


/**
 * @brief Grava a lista de antenas num ficheiro binário.
 */
 
 void gravarEmBinario(Antena *cabeca, const char *nomeFicheiro) {
     FILE *ficheiro = fopen(nomeFicheiro, "wb");
     if (!ficheiro) {
         printf("Erro ao abrir ficheiro binário para escrita.\n");
         return;
     }
 
     while (cabeca) {
         // Usa a struct definida em estruturas.h
         AntenaBinaria antenaTemp = { cabeca->frequencia, cabeca->x, cabeca->y };
         fwrite(&antenaTemp, sizeof(AntenaBinaria), 1, ficheiro);
         cabeca = cabeca->proxima;
     }
 
     // Fecha o ficheiro
     fclose(ficheiro);
     printf("Lista ligada gravada com sucesso em \"%s\".\n", nomeFicheiro);
 }
 
 




