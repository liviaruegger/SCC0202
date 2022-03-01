/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 07: Lista Ordenada
 *         
 * @date   2021-11-07
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista-ordenada.h"

typedef enum {false, true} bool;

char *read_line(FILE *stream);
void read_word_static(FILE *stream, char *word);

int main()
{
    lista_t *lista = criar();

    bool encontrou_eof = false;
    while (!encontrou_eof)
    {
        char comando[9];
        read_word_static(stdin, comando);

        if (strcmp(comando, "INSERE") == 0)
        {
            int codigo;
            scanf("%d", &codigo);
            getchar(); // Consome o espaço após o código.

            char *nome = read_line(stdin);

            int inseriu = inserir(lista, codigo, nome);
            if (!inseriu)
            {
                printf("INVALIDO\r\n");
                free(nome);
            }
        }
        else if (strcmp(comando, "REMOVE") == 0)
        {
            int codigo;
            scanf("%d", &codigo);
            getchar(); // Consome o '\n' após o código.

            int removeu = remover(lista, codigo);
            if (!removeu) printf("INVALIDO\r\n");
        }
        else if (strcmp(comando, "IMPRIMIR") == 0)
        {
            imprimir(lista);
        }
        
        char temp = fgetc(stdin);
        if (temp == EOF) encontrou_eof = true;
        else ungetc(temp, stdin);
    }
    
    liberar(lista);

    return 0;
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
    char *string = (char *) malloc(sizeof(char));
    int size = 0;

    do
    {
        string[size] = fgetc(stream);
        size++;

        if (string[size - 1] != '\r' && string[size - 1] != '\n' && string[size - 1] != EOF)
            string = (char *) realloc(string, size + 1);

    } while (string[size - 1] != '\r' && string[size - 1] != '\n' && string[size - 1] != EOF);

    if (string[size - 1] == '\r') getchar();

    string[size - 1] = '\0';

    return string;
}

/**
 * @brief Lê e armazena, em um vetor de caracteres estático, uma palavra do arquivo
 * dado até encontrar um espaço, uma quebra de linha ou o fim do arquivo (EOF).
 * Obs: o vetor precisa ter tamanho suficiente para armazenar a palavra; caso não
 * tenha, o programa será abortado ("stack smashing").
 * 
 * @param stream entrada (pode ser um arquivo ou a entrada padrão);
 * @param word vetor de caracteres onde será armazenada a palavra.
 */
void read_word_static(FILE *stream, char *word)
{
    int i = 0;
    do
    {
        word[i] = fgetc(stream);

        if (word[i] == ' ' || word[i] == '\r' || word[i] == '\n' || word[i] == EOF)
            word[i] = '\0';
        
        i++;

    } while (word[i - 1] != '\0');
}