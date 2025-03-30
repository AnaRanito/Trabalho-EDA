/*!
 *  @file funcoes.h
 *  @author Rita Ranito
 *  @date 2025-03-30
 *  @project Projeto Gestão de Antenas
 *
 *  Protótipos das funções. 
 */

#ifndef FUNCOES_H
#define FUNCOES_H
#include "estruturas.h"

/**
 * @brief Cria uma nova antena com os dados fornecidos.
 * @param frequencia Letra que representa a frequência da antena.
 * @param x Coordenada horizontal (coluna).
 * @param y Coordenada vertical (linha).
 * @return Ponteiro para a nova antena criada.
 */
Antena* criarAntena(char frequencia, int x, int y);

/**
 * @brief Insere uma nova antena no início da lista ligada.
 * @param cabeca Ponteiro para o ponteiro da cabeça da lista.
 * @param frequencia Letra que representa a frequência da antena.
 * @param x Coordenada horizontal (coluna).
 * @param y Coordenada vertical (linha).
 */
void inserirAntena(Antena **cabeca, char frequencia, int x, int y);

/**
 * @brief Remove uma antena com coordenadas e frequência específicas.
 * @param cabeca Ponteiro para o ponteiro da cabeça da lista.
 * @param frequencia Letra da frequência a remover.
 * @param x Coordenada horizontal (coluna).
 * @param y Coordenada vertical (linha).
 */
void removerAntena(Antena **cabeca, char frequencia, int x, int y);

/**
 * @brief Carrega uma lista de antenas a partir de um ficheiro de texto.
 * @param nomeFicheiro Nome do ficheiro a ler.
 * @param linhas Ponteiro para armazenar o número de linhas lidas.
 * @param colunas Ponteiro para armazenar o número de colunas lidas.
 * @return Ponteiro para a lista ligada criada.
 */
Antena* carregarDeFicheiro(const char* nomeFicheiro, int *linhas, int *colunas);

/**
 * @brief Exibe a lista de antenas no terminal.
 * @param cabeca Ponteiro para a cabeça da lista de antenas.
 */
void exibirAntenas(Antena *cabeca);

/**
 * @brief Calcula e desenha a matriz com antenas e suas interferências.
 * @param cabeca Ponteiro para a cabeça da lista de antenas.
 * @param linhas Número total de linhas da matriz.
 * @param colunas Número total de colunas da matriz.
 */
void calcularEdesenharMatriz(Antena *cabeca, int linhas, int colunas);


/**
 * @brief Grava a lista de antenas num ficheiro binário.
 *
 * @param cabeca Ponteiro para a cabeça da lista ligada de antenas.
 * @param nomeFicheiro Nome do ficheiro binário onde os dados serão guardados.
 */
void gravarEmBinario(Antena *cabeca, const char *nomeFicheiro);


#endif
