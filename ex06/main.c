/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 06: Rotação de Lista
 *         
 * @date   2021-10-11
 * 
 */

#include <stdio.h>
#include "rotacao.h"

int main()
{
    int n_casos_teste;
    scanf("%d", &n_casos_teste);

    for (int i = 0; i < n_casos_teste; i++)
    {
        int tamanho_lista, n_rotacoes;
        scanf("%d %d", &tamanho_lista, &n_rotacoes);

        lista_t *lista = criar();

        for (int j = 0; j < tamanho_lista; j++)
        {
            int novo_elemento;
            scanf("%d", &novo_elemento);
            inserir(lista, novo_elemento);
        }

        n_rotacoes = n_rotacoes % tamanho_lista;

        rotacionar(lista, n_rotacoes);
        imprimir(lista);
        liberar(lista);

        if (i < n_casos_teste - 1) printf("\r\n");
    }

    return 0;
}