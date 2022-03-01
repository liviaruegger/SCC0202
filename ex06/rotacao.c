/**
 * @file   rotacao.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 06: Rotação de Lista
 *         
 * @date   2021-10-11
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "rotacao.h"

typedef struct node node_t; 

struct node
{
    elem info;
    node_t *proximo;
    node_t *anterior;
};

struct lista
{
    node_t *inicio;
    node_t *fim;
    int tamanho;
};

lista_t *criar()
{
    lista_t *lista;
    lista = (lista_t *) malloc(sizeof(lista_t));
    
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;

    return lista;
}

void inserir(lista_t *lista, elem x)
{
    // Criar novo nó:
    node_t *novo_no = (node_t *) malloc(sizeof(node_t));
    novo_no->info = x;
    novo_no->proximo = NULL;
    novo_no->anterior = NULL;

    if (lista->inicio == NULL) // 1o caso: lista vazia.
    {
        lista->inicio = novo_no;
    }
    else // 2o caso: lista com pelo menos um elemento.
    {
        lista->fim->proximo = novo_no;
        novo_no->anterior = lista->fim;
    }

    lista->fim = novo_no;
    lista->tamanho++;
}

void rotacionar(lista_t *lista, int n_rotacoes)
{
    for (int i = 0; i < n_rotacoes; i++)
    {
        lista->fim->proximo = lista->inicio; // Lista se torna temporariamente circular.
        lista->inicio = lista->fim; // Atualiza o início (no momento, início = fim).
        lista->fim = lista->inicio->anterior; // Atualiza fim.
        
        lista->fim->proximo = NULL;
        lista->inicio->anterior = NULL;
    }
}

void imprimir(lista_t *lista)
{
    node_t *no = lista->inicio;

    while (no != NULL)
    {
        printf("%d", no->info);
        if (no->proximo != NULL) printf(" ");
        no = no->proximo;
    }
}

void liberar(lista_t *lista)
{
    if (lista != NULL)
    {
        node_t *no = lista->inicio;

        while (no != NULL)
        {
            lista->inicio = no->proximo;
            free(no);
            no = lista->inicio;
        }

        free(lista);
    }
}