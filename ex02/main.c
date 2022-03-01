/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 02: Crivo de Eratóstenes
 * 
 * @date   2021-09-30
 * 
 */

#include <stdio.h>
#include "eratostenes.h"

int main()
{
    int n_primos_impressos;
    scanf("%d ", &n_primos_impressos);

    int indices[n_primos_impressos];

    int parada = 0;
    for (int i = 0; i < n_primos_impressos; i++)
    {
        scanf("%d ", &indices[i]);
        if (indices[i] > parada) parada = indices[i];        
    }

    lista_t *lista_de_primos = criar_lista_de_primos();
    imprimir_primos(lista_de_primos, indices, n_primos_impressos);
    desalocar_lista(lista_de_primos);

    return 0;
}