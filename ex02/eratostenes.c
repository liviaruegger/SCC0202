/**
 * @file   eratostenes.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 02: Crivo de Eratóstenes
 * 
 * @date   2021-09-30
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "eratostenes.h"

struct lista
{
    int tamanho;
    int *lista;
};

/**
 * @brief Recebe, por referência, uma struct contendo um vetor de inteiros e
 * aplica sobre ele o algoritmo do Crivo de Eratóstenes, deixando em seu lugar um vetor
 * contendo apenas números primos.
 * 
 * @param lista struct lista contendo uma lista de inteiros (int *) e seu tamanho. 
 */
static void retirar_multiplos(lista_t *lista)
{
    int indice = 1; // Começa no número 2.

    // Substitui todos os números que não são primos por -1.
    while (indice < lista->tamanho / 2) // O mais eficiente seria usar a raiz quadrada.
    {
        int n = indice + 1;
        for (int i = (2 * n) - 1; i < lista->tamanho; i += n)
            lista->lista[i] = -1;
        
        indice++;
    }

    // Cria uma nova lista apenas com os números primos.
    int novo_tamanho = 0;
    int *lista_temp = NULL;

    for (int i = 0; i < lista->tamanho; i++)
    {
        if (lista->lista[i] != -1)
        {
            lista_temp = (int *) realloc(lista_temp, (novo_tamanho + 1) * sizeof(int));
            lista_temp[novo_tamanho] = lista->lista[i];
            novo_tamanho++;
        }
    }

    lista->tamanho = novo_tamanho;
    free(lista->lista);
    lista->lista = lista_temp;
}

/**
 * @brief Cria uma lista de inteiros que vão de 1 até o valor máximo estabelecido no
 * arquivo .h e chama a função retirar_multiplos, que modifica a lista para que nela
 * permaneçam apenas os números primos.
 * 
 * @return ponteiro para a struct lista contendo o vetor de números primos e o tamanho
 * desse vetor (lista_t *).
 */
lista_t *criar_lista_de_primos()
{
    lista_t *lista_de_primos = (lista_t *) malloc(sizeof(lista_t));
    lista_de_primos->lista = (int *) malloc(VALOR_MAXIMO * sizeof(int));
    lista_de_primos->tamanho = VALOR_MAXIMO;

    // Preenche lista com inteiros até o valor máximo.
    for (int i = 0; i < VALOR_MAXIMO; i++)
        lista_de_primos->lista[i] = i + 1;

    retirar_multiplos(lista_de_primos);

    return lista_de_primos;
}

/**
 * @brief Imprime os valores de n números primos a partir de uma lista de índices
 * que indicam suas posições na lista de primos.
 *
 * @param lista struct contendo o vetor de números primos e o tamanho desse vetor;
 * @param indices vetor contendo os índices dos números primos a serem impressos;
 * @param n_impressoes número de primos que devem ser impressos.
 */
void imprimir_primos(lista_t *lista, int indices[], int n_impressoes)
{
    for (int i = 0; i < n_impressoes - 1; i++)
        printf("%d ", lista->lista[indices[i]]);
    printf("%d", lista->lista[indices[n_impressoes -1]]);
}

/**
 * @brief Desaloca a memória ocupada pela lista de primos.
 * 
 * @param lista struct contendo o vetor de números primos e seu tamanho.
 */
void desalocar_lista(lista_t *lista)
{
    free(lista->lista);
    free(lista);
}