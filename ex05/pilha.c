/**
 * @file   pilha.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 05: Sequência Balanceada
 *         
 * @date   2021-10-09
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct pilha
{
    int topo;
    elem itens[TAMANHO_PILHA];
};

pilha_t *create()
{
    pilha_t *p = (pilha_t *) malloc(sizeof(pilha_t));
    p->topo = -1;

    return p;
}

void destroy(pilha_t *p)
{
    if (p != NULL)
        free(p);

    p = NULL;
}

int is_full(pilha_t *p)
{
    if (p->topo == TAMANHO_PILHA - 1)
        return 1;
    else
        return 0;
}

int is_empty(pilha_t *p)
{
    if (p->topo == -1)
        return 1;
    else
        return 0;
}

int push(pilha_t *p, elem x)
{
    if (is_full(p) == 1)
        return -1;

    p->topo = p->topo + 1;
    p->itens[p->topo] = x;
    return 1;
}

int pop(pilha_t *p, elem *x)
{
    if (is_empty(p) == 1)
        return -1;

    *x = p->itens[p->topo];
    p->topo -= 1;
    return 1;
}

int top(pilha_t *p, elem *x)
{
    if (is_empty(p) == 1)
        return -1;

    *x = p->itens[p->topo];
    return 1;
}