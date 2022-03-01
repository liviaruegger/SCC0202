/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 01: Palavras Mais Frequentes
 * 
 * @date   2021-09-22
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "lista-palavras.h"

typedef enum {false, true} bool;

int main()
{
    bool encontrou_eof = false;

    while (encontrou_eof == false)
    {
        char *frase = read_line(stdin);

        int n_palavras;
        scanf("%d ", &n_palavras);

        char c = fgetc(stdin);
        if (c == EOF) encontrou_eof = true;
        else ungetc(c, stdin);

        lista_t *lista = criar_lista(frase);
        free(frase);
        ordenar_lista(lista);
        imprimir_palavras(lista, n_palavras);
        destruir_lista(lista);

        if (encontrou_eof == false) printf("\n\n");
    }

    return 0;
}