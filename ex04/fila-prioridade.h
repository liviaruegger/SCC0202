/**
 * @file   fila-prioridade.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 04: Filas de Prioridade
 *         
 * @date   2021-10-04
 * 
 */

// Sobre o TAD Filas de Prioridade:
// As funções neste módulo trabalham com um bloco de filas, sendo cada uma
// referente a uma categoria/prioridade.

#define TAMANHO_MAXIMO 100

typedef struct fila fila_t;

fila_t *criar(int n);
int fila_cheia(fila_t *fila, int n);
int fila_vazia(fila_t *fila, int n);
void inserir(fila_t *fila, int prioridade, void *elemento);
void remover(fila_t *fila, int n, void **elemento);
void destruir(fila_t *fila, int n);