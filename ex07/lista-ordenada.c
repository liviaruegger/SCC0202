/**
 * @file   lista-ordenada.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 07: Lista Ordenada
 *         
 * @date   2021-11-07
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "lista-ordenada.h"

typedef struct node node_t;

struct node
{
    int codigo;
    char *nome;
    node_t *proximo;
};

struct lista
{
    node_t *inicio;
    // node_t *fim; -> Não será necessário.
};

lista_t *criar()
{
    lista_t *lista = (lista_t *) malloc(sizeof(lista_t));

    lista->inicio = NULL;
    // lista->fim = NULL;

    return lista;
}

int inserir(lista_t *lista, int codigo, char *nome)
{
    node_t *aux = lista->inicio;
    node_t *anterior = NULL;

    // Encontrar a posição correta:
    while (aux != NULL && codigo > aux->codigo)
    {
        anterior = aux;
        aux = aux->proximo;
    }

    // Código já está presente na lista?
    if (aux != NULL && codigo == aux->codigo) return 0;
    
    // Criar o novo nó:
    node_t *novo_no = (node_t *) malloc(sizeof(node_t));
    novo_no->codigo = codigo;
    novo_no->nome = nome;

    if (anterior == NULL) // Inserir no início da lista.
    {
        novo_no->proximo = lista->inicio;
        lista->inicio = novo_no;
    }
    else // Inserir no meio ou no fim da lista.
    {
        novo_no->proximo = anterior->proximo;
        anterior->proximo = novo_no;
    }

    return 1;
}

int remover(lista_t *lista, int codigo)
{
    node_t *aux = lista->inicio;
    node_t *anterior = NULL;

    // Encontrar a posição correta:
    while (aux != NULL && codigo > aux->codigo)
    {
        anterior = aux;
        aux = aux->proximo;
    }

    // Código não está presente na lista?
    if (aux == NULL || codigo != aux->codigo) return 0;

    if (anterior == NULL) // Remover o primeiro elemento.
    {
        lista->inicio = lista->inicio->proximo;
        free(aux->nome);
        free(aux);
    }
    else // Remover do meio ou do fim da lista.
    {
        anterior->proximo = aux->proximo;
        free(aux->nome);
        free(aux);
    }

    return 1;
}

void imprimir(lista_t *lista)
{
    if (lista->inicio == NULL)
    {
        printf("VAZIA\r\n");
        return;
    }
    
    node_t *temp = lista->inicio;
    while (temp != NULL)
    {
        printf("%d, %s;", temp->codigo, temp->nome);
        temp = temp->proximo;
        if (temp != NULL) printf(" ");
    }
    printf("\r\n");
}

void liberar(lista_t *lista)
{
    if (lista != NULL)
    {
        node_t *temp = lista->inicio;
        while (temp != NULL)
        {
            lista->inicio = temp->proximo;
            
            free(temp->nome);
            free(temp);

            temp = lista->inicio;
        }

        free(lista);
    }
}