/**
 * @file   main.c
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

int main()
{
    int n_casos_teste;
    scanf("%d", &n_casos_teste);
    getchar(); // Consome o \r
    getchar(); // Consome o \n

    for (int i = 0; i < n_casos_teste; i++)
    {
        int n_polinomios;
        scanf("%d", &n_polinomios);
        getchar(); // Consome o \r
        getchar(); // Consome o \n

        lista_t *lista_polinomios = criar_lista();

        for (int j = 0; j < n_polinomios; j++)
        {
            polinomio_t *polinomio = criar_polinomio();

            int i = 0;
            char c = getchar();
            while (c != ')') // Formato de entrada de polinômio: (0,0,1,2,3,4)
            {
                int coef;
                scanf("%d", &coef);
                adicionar_termo(polinomio, coef, i);
                c = getchar();
                i++;
            }
            getchar(); // Consome o \r
            getchar(); // Consome o \n
            
            adicionar_polinomio(lista_polinomios, polinomio);
        }

        polinomio_t *soma = somar_polinomios(lista_polinomios);
        
        imprimir_polinomio(soma);
        if (i != n_casos_teste - 1) printf("\r\n");

        liberar_polinomio(soma);
        liberar_lista(lista_polinomios);
    }

    return 0;
}