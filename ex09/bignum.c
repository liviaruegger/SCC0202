/**
 * @file   bignum.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 09: Grandes Números
 *         
 * @date   2021-11-15
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"

#define TRUE  1
#define FALSE 0

typedef struct node node_t; 

struct node
{
    int algarismo;
    node_t *proximo;
    node_t *anterior;
};

struct numero
{
    int sinal; // 1 para positivo, -1 para negativo
    node_t *inicio;
    node_t *fim;
    int tamanho;
};

numero_t *criar(int sinal)
{
    numero_t *numero;
    numero = (numero_t *) malloc(sizeof(numero_t));
    
    numero->sinal = sinal;
    numero->inicio = NULL;
    numero->fim = NULL;
    numero->tamanho = 0;

    return numero;
}

void adicionar_algarismo(numero_t *numero, int alg)
{
    node_t *no = (node_t *) malloc(sizeof(node_t));
    no->algarismo = alg;
    no->anterior = NULL;
    no->proximo = NULL;

    if (numero->inicio == NULL)
    {
        numero->inicio = no;
    }
    else
    {
        numero->fim->proximo = no;
        no->anterior = numero->fim;
    }

    numero->fim = no;
    numero->tamanho++;
}

numero_t *somar(numero_t *numero1, numero_t *numero2)
{
    numero_t *soma = criar(1);
    // Se o resultado for negativo, o sinal será alterado depois.

    node_t *p1 = numero1->fim;
    node_t *p2 = numero2->fim;

    int carry = 0;

    while (p1 != 0 || p2 != 0 || carry != 0)
    {
        int a1, a2;

        if (p1 == NULL) a1 = 0;
        else a1 = (p1->algarismo) * numero1->sinal;
        if (p2 == NULL) a2 = 0;
        else a2 = (p2->algarismo) * numero2->sinal;

        int s = (a1 + a2 + carry) % 10;
        carry = (a1 + a2 + carry) / 10;

        // Cria um nó.
        node_t *no = (node_t *) malloc(sizeof(node_t));
        no->algarismo = abs(s);
        no->anterior = NULL;
        no->proximo = NULL;

        // Adiciona o nó à esquerda.
        if (soma->fim == NULL)
        {
            soma->fim = no;
        }
        else
        {
            soma->inicio->anterior = no;
            no->proximo = soma->inicio;
        }
        soma->inicio = no;
        soma->tamanho++;

        if (p1 != NULL) p1 = p1->anterior;
        if (p2 != NULL) p2 = p2->anterior;

        if (p1 == NULL && p2 == NULL) soma->sinal = s / abs(s);
    }

    return soma;
}

// Retorna  1 quando n1 > n2
// Retorna -1 quando n1 < n2
// Retorna  0 quando n1 = n2
int comparar(numero_t *numero1, numero_t *numero2)
{
    numero2->sinal -= 2 * numero2->sinal;     // Troca o sinal do n2
    numero_t *soma = somar(numero1, numero2); // Soma n1 + (-n2)
    numero2->sinal -= 2 * numero2->sinal;     // Destroca o sinal do n2
    
    // Confere se a soma é zero.
    int soma_zero = TRUE;
    node_t *p = soma->inicio;
    while (p != NULL)
    {
        if (p->algarismo != 0)
        {
            soma_zero = FALSE;
            break;
        }
        p = p->proximo;
    }

    if (soma_zero == TRUE)
    {
        liberar(soma);
        return 0;
    }
    else if (soma->sinal == 1)
    {
        liberar(soma);
        return 1;
    }
    else if (soma->sinal == -1)
    {
        liberar(soma);
        return -1;
    }
}

void imprimir(numero_t *numero)
{
    if (numero->sinal == -1) printf("-");
    
    node_t *p =  numero->inicio;
    while (p != NULL)
    {
        printf("%d", p->algarismo);
        p = p->proximo;
    }
}

void liberar(numero_t *numero)
{
    node_t *p = numero->inicio;
    while (p != NULL)
    {
        node_t *aux = p;
        p = p->proximo;
        free(aux);
    }
    free(numero);
}