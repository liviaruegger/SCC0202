/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Projeto 01: Skip Lists - Criando Um Dicionário
 *         
 * @date   2021-12-13
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"

#define MAX_LEVEL   20
#define PROBABILITY 0.5

char *read_word(FILE *stream);
char *read_line(FILE *stream);

int main()
{
    skiplist_t *dicionario = create(MAX_LEVEL, PROBABILITY);

    while (!feof(stdin))
    {
        char *comando = read_word(stdin);

        if (strcmp(comando, "insercao") == 0)
        {
            char *palavra = read_word(stdin);
            char *definicao = read_line(stdin);

            if (insert(dicionario, palavra, definicao) == -1)
                printf("OPERACAO INVALIDA\n");
        }
        else if (strcmp(comando, "alteracao") == 0)
        {
            char *palavra = read_word(stdin);
            char *definicao = read_line(stdin);

            if (change_definition(dicionario, palavra, definicao) == -1)
                printf("OPERACAO INVALIDA\n");

            free(palavra);
        }
        else if (strcmp(comando, "remocao") == 0)
        {
            char *palavra = read_word(stdin);

            if (remove_word(dicionario, palavra) == -1)
                printf("OPERACAO INVALIDA\n");

            free(palavra);
        }
        else if (strcmp(comando, "busca") == 0)
        {
            char *palavra = read_word(stdin);

            if (print_definition(dicionario, palavra) == -1)
                printf("OPERACAO INVALIDA\n");

            free(palavra);
        }
        else if (strcmp(comando, "impressao") == 0)
        {
            char c = getchar();

            char temp = getchar(); // Consome o caractere quebra-linha.
            if (temp == '\r') getchar(); // Consome o '\n' após o '\r'.

            if (print_all(dicionario, c) == -1)
                printf("NAO HA PALAVRAS INICIADAS POR %c\n", c);
        }

        free(comando);
    }

    destroy(dicionario);

    return 0;
}

/**
 * @brief Alocando memória dinamicamente, lê e armazena uma palavra do arquivo dado até
 * encontrar um espaço, uma quebra de linha ou o fim do arquivo (EOF).
 *
 * @param stream entrada (pode ser um arquivo ou a entrada padrão);
 * @return ponteiro para a string lida (char *).
 */
char *read_word(FILE *stream)
{
    char *string = (char *)malloc(sizeof(char));
    int size = 0;

    do
    {
        string[size] = fgetc(stream);
        size++;

        if (string[size - 1] != ' ' &&
            string[size - 1] != '\r' &&
            string[size - 1] != '\n' &&
            string[size - 1] != EOF)
            string = (char *)realloc(string, size + 1);

    } while (string[size - 1] != ' ' &&
             string[size - 1] != '\r' &&
             string[size - 1] != '\n' &&
             string[size - 1] != EOF);

    if (string[size - 1] == '\r')
        getchar();

    string[size - 1] = '\0';

    return string;
}

/**
 * @brief Lê e armazena uma linha do arquivo dado até encontrar uma quebra de linha ou
 * o fim do arquivo (EOF).
 *
 * @param stream entrada (pode ser um arquivo ou a entrada padrão);
 * @return ponteiro para a string lida (char *).
 */
char *read_line(FILE *stream)
{
    char *string = (char *)malloc(sizeof(char));
    int size = 0;

    do
    {
        string[size] = fgetc(stream);
        size++;

        if (string[size - 1] != '\r' && string[size - 1] != '\n' && string[size - 1] != EOF)
            string = (char *)realloc(string, size + 1);

    } while (string[size - 1] != '\r' && string[size - 1] != '\n' && string[size - 1] != EOF);

    if (string[size - 1] == '\r')
        getchar();

    string[size - 1] = '\0';

    return string;
}