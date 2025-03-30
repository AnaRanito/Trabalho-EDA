/*!
 *  @file main.c
 *  @author Rita Ranito
 *  @date 2025-03-30
 *  @project Projeto Gestão de Antenas
 *
 *  Entrada principal do programa.
 *      
 */

#include <stdio.h>
#include "funcoes.h"

/**
 * Função principal: lê o ficheiro, carrega antenas, exibe e desenha a matriz.
 */
int main() {
    const char *nomeFicheiro = "matriz3.txt"; // Nome do ficheiro com a matriz
    int linhas = 0, colunas = 0;

    // Carrega antenas do ficheiro e determina dimensões da matriz
    Antena *listaAntenas = carregarDeFicheiro(nomeFicheiro, &linhas, &colunas);

    if (listaAntenas == NULL) {
        printf("Erro: Não foi possível carregar as antenas.\n");
        return 1;
    }

    // Mostra lista de antenas
    exibirAntenas(listaAntenas);

    // Desenha a matriz com antenas e posições calculadas
    calcularEdesenharMatriz(listaAntenas, linhas, colunas);

    //Grava a lista ligada de antenas num ficheiro binário
    gravarEmBinario(listaAntenas, "antenas.bin");


    return 0;
}
