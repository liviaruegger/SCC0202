/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 03: Substituição de Strings
 * 
 * @date   2021-10-01
 * 
 */

#include <stdio.h>
#include "tad-string.h"

typedef enum {false, true} bool;

int main()
{
    bool encontrou_eof = false;

    while (encontrou_eof == false)
    {
        str_t *string = ler_string_para_corrigir();
        corrigir_e_imprimir(string);
        destruir(string);

        char c = fgetc(stdin);
        if (c == EOF) encontrou_eof = true;
        else ungetc(c, stdin);

        if (encontrou_eof == false) printf("\r\n");
    }

    return 0;
}