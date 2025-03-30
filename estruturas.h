/*!
 *  @file estruturas.h
 *  @author Rita Ranito
 *  @date 2025-03-30
 *  @project Projeto Gestão de Antenas
 *
 *  Declaração de estruturas. 
 */

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

/**
 * @brief Estrutura que representa uma antena com frequência e coordenadas.
 */
typedef struct Antena {
    char frequencia;         /**< Frequência da antena. */
    int x, y;                /**< Coordenadas (coluna x, linha y). */
    struct Antena *proxima;  /**< Ponteiro para a próxima antena na lista. */
} Antena;

/**
 * @brief Estrutura auxiliar usada para gravar ou ler dados binários de uma antena.
 * Esta estrutura contém apenas os campos essenciais: frequência e coordenadas (x e y).
  */
 typedef struct {
    char frequencia;  /**< Frequência da antena */
    int x, y;         /**< Coordenadas da antena */
} AntenaBinaria;




#endif
