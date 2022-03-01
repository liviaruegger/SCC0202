/**
 * @file   poli.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 08: Polinômios Esparsos
 *         
 * @date   2021-11-14
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "poli.h"

struct monomio
{
    int coef;
    int grau;
    monomio_t *prox;
};
 
struct polinomio
{
    monomio_t *inicio;
    monomio_t *fim;
    polinomio_t *prox;
};

struct lista
{
    polinomio_t *inicio;
    polinomio_t *fim;
};

lista_t *criar_lista()
{
    lista_t *lista = (lista_t *) malloc(sizeof(lista_t));

    lista->inicio = NULL;
    lista->fim = NULL;

    return lista;
}

polinomio_t *criar_polinomio()
{
    polinomio_t *polinomio = (polinomio_t *) malloc(sizeof(polinomio_t));

    polinomio->inicio = NULL;
    polinomio->fim = NULL;
    polinomio->prox = NULL;

    return polinomio;
}

void adicionar_termo(polinomio_t *polinomio, int coef, int grau)
{
    monomio_t *termo = (monomio_t *) malloc(sizeof(monomio_t));
    termo->coef = coef;
    termo->grau = grau;
    termo->prox = NULL;

    if (polinomio->inicio == NULL) polinomio->inicio = termo;
    else polinomio->fim->prox = termo;

    polinomio->fim = termo;
}

void adicionar_polinomio(lista_t *lista, polinomio_t *polinomio)
{
    if (lista->inicio == NULL) lista->inicio = polinomio;
    else lista->fim->prox = polinomio;

    lista->fim = polinomio;
}

polinomio_t *somar_polinomios(lista_t *lista)
{
    polinomio_t *soma = (polinomio_t *) malloc(sizeof(polinomio_t));
    
    soma->inicio = NULL;
    soma->fim = NULL;
    soma->prox = NULL;

    polinomio_t *polinomio = lista->inicio;
    while (polinomio != NULL) // Passará por todos os polinômios.
    {
        monomio_t *termo = polinomio->inicio;
        monomio_t *termo_soma = soma->inicio;

        int grau = 0;
        while (termo != NULL) // Passará por todos os termos de cada polinômio.
        {
            if (termo_soma == NULL)
            {
                adicionar_termo(soma, 0, grau);
                termo_soma = soma->fim;
            }

            termo_soma->coef += termo->coef;

            termo = termo->prox;
            termo_soma = termo_soma->prox;
            grau++;
        }
        
        polinomio = polinomio->prox;
    }

    return soma;
}

void imprimir_polinomio(polinomio_t *polinomio)
{
    monomio_t *p = polinomio->inicio;
    
    printf("(");
    while (p != NULL)
    {
        printf("%d", p->coef);
        p = p->prox;
        if (p != NULL) printf(",");
    }
    printf(")");
}

void liberar_polinomio(polinomio_t *polinomio)
{
    monomio_t *p = polinomio->inicio;
    while (p != NULL)
    {
        monomio_t *aux = p;
        p = p->prox;
        free(aux);
    }
    free(polinomio);
}

void liberar_lista(lista_t *lista)
{
    polinomio_t *p = lista->inicio;
    while (p != NULL)
    {
        polinomio_t *aux = p;
        p = p->prox;
        liberar_polinomio(aux);
    }
    free(lista);
}