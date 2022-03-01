/**
 * @file   fila-prioridade.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 04: Filas de Prioridade
 *         
 * @date   2021-10-04
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "fila-prioridade.h"

#define TRUE  1
#define FALSE 0

struct fila
{
    void **elementos;
    int inicio;
    int fim;
    int total;
};

/**
 * @brief Cria e inicializa um bloco de n filas.
 * 
 * @param n quantidade de filas a serem criadas;
 * @return endereço da primeira fila (fila_t*). 
 */
fila_t *criar(int n)
{
    fila_t *fila = (fila_t *) malloc(n * sizeof(fila_t));

    for (int i = 0; i < n; i++)
    {
        fila[i].elementos = NULL;
        fila[i].inicio = 0;
        fila[i].fim = 0;
        fila[i].total = 0;
    }
    
    return fila;
}

/**
 * @brief Verifica se a fila atingiu o tamanho máximo definido no arquivo de cabeçalho.
 * A avaliação é feita pela soma total de elementos em todas as filas, independentemente
 * de quantos elementos há em cada fila. 
 * 
 * @param fila endereço da primeira fila;
 * @param n quantidade total de filas;
 * @return 1 (fila cheia) ou 0. 
 */
int fila_cheia(fila_t *fila, int n)
{
    int total_geral = 0;
    for (int i = 0; i < n; i++)
        total_geral += fila[i].total;

    if (total_geral == TAMANHO_MAXIMO)
        return TRUE;
    else
        return FALSE;
}

/**
 * @brief Verifica se a fila está vazia (ou seja, se não há elemento(s) em nenhuma das
 * n filas).
 * 
 * @param fila endereço da primeira fila;
 * @param n quantidade total de filas;
 * @return 1 (todas as filas vazias) ou 0.
 */
int fila_vazia(fila_t *fila, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (fila[i].total != 0)
            return FALSE;
    }

    return TRUE;
}

/**
 * @brief Insere um novo elemento (na verdade, seu endereço) na fila de prioridade cujo
 * índice foi passado como parâmetro.
 * 
 * @param fila endereço da primeira fila;
 * @param prioridade índice da fila na qual o elemento deve ser inserido;
 * @param elemento endereço (void*) que será inserido na fila (a fila é genérica e
 * armazena ponteiros e não os elementos em si).
 */
void inserir(fila_t *fila, int prioridade, void *elemento)
{
    fila[prioridade].elementos = realloc(fila[prioridade].elementos, (fila[prioridade].fim + 1) * sizeof(void *));
    fila[prioridade].elementos[fila[prioridade].fim] = elemento;
    fila[prioridade].fim++;
    fila[prioridade].total++;
}

/**
 * @brief Remove o primeiro elemento da fila, considerando a ordem de prioriodade.
 * 
 * @param fila endereço da primeira fila;
 * @param n quantidade total de filas;
 * @param elemento endereço da variável onde será armazenado o ponteiro para o elemento
 * retirado da fila (ponteiro duplo).
 */
void remover(fila_t *fila, int n, void **elemento)
{
    // Checa as filas por ordem de prioridade.
    for (int i = 0; i < n; i++)
    {
        if(fila[i].total != 0) 
        {
            *elemento = fila[i].elementos[fila[i].inicio];
            fila[i].inicio++;
            fila[i].total--;

            return;
        }
    }
}

/**
 * @brief Desaloca toda a memória utilizada por um bloco de filas.
 * 
 * @param fila endereço da primeira fila;
 * @param n quantidade total de filas.
 */
void destruir(fila_t *fila, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < fila[i].fim; j++)
            free(fila[i].elementos[j]);
        free(fila[i].elementos);
    }

    free(fila);
}