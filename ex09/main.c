/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 09: Grandes Números
 *         
 * @date   2021-11-15
 * 
 */

#include <stdio.h>
#include <string.h>
#include "bignum.h"

numero_t *ler_numero();

int main()
{
    int n_operacoes;
    scanf("%d", &n_operacoes);
    getchar(); // Consome o \r
    getchar(); // Consome o \n

    for (int i = 0; i < n_operacoes; i++)
    {
        char comando[3];
        for (int i = 0; i < 3; i++)
            comando[i] = fgetc(stdin);
        getchar(); // Consome o espaço

        numero_t *numero1 = ler_numero();
        numero_t *numero2 = ler_numero();
        getchar(); // Consome o \n
        
        // Executar comando.
        if (strcmp(comando, "SUM") == 0)
        {
            numero_t *soma = somar(numero1, numero2);
            imprimir(soma);
            liberar(soma);
        }
        else if (strcmp(comando, "BIG") == 0)
        {
            int result = comparar(numero1, numero2);
            if (result == 1) printf("1");
            else printf("0");
        }
        else if (strcmp(comando, "SML") == 0)
        {
            int result = comparar(numero1, numero2);
            if (result == -1) printf("1");
            else printf("0");
        }
        else if (strcmp(comando, "EQL") == 0)
        {
            int result = comparar(numero1, numero2);
            if (result == 0) printf("1");
            else printf("0");
        }
        printf("\r\n");

        liberar(numero1);
        liberar(numero2);
    }

    return 0;
}

/**
 * @brief Faz a leitura de um número da entrada padrão, algarismo por algarismo,
 * e chama as funções do TAD Grandes Números para criar um grande número do tipo
 * numero_t definido pelo TAD (uma lista duplamente encadeada).
 * 
 * @return ponteiro para o TAD número (numero_t *). 
 */
numero_t *ler_numero()
{
    numero_t *numero;

    char c = fgetc(stdin);
    if (c == '-')
    {
        numero = criar(-1);
        c = fgetc(stdin);
    }
    else
    {
        numero = criar(1);
    }

    // Descartar zeros à esquerda.
    if (c == '0')
    {
        do
        {
            c = fgetc(stdin);
        } while (c == '0');
    }

    // Ler e adicionar todos os algarismos.
    do
    {
        adicionar_algarismo(numero, c - '0');
        c = fgetc(stdin);
    } while (c != ' ' && c != '\r');

    return numero;
}