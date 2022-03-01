/**
 * @file   pilha.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 05: Sequência Balanceada
 *         
 * @date   2021-10-09
 * 
 */

#define TAMANHO_PILHA 1000

typedef char elem;
typedef struct pilha pilha_t;

pilha_t *create();
void destroy(pilha_t *p);
int is_full(pilha_t *p);
int is_empty(pilha_t *p);
int push(pilha_t *p, elem x);
int pop(pilha_t *p, elem *x);
int top(pilha_t *p, elem *x);