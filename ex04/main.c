/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 04: Filas de Prioridade
 *         
 * @date   2021-10-04
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila-prioridade.h"

#define TRUE  1
#define FALSE 0

typedef struct pessoa
{
    char nome[20];
    int idade;
    int agravante;
}   pessoa_t;

void read_word_static(FILE *stream, char *word);
pessoa_t *ler_info_pessoa();
void imprimir_info_pessoa(pessoa_t *pessoa);

// Sobre o uso do TAD Filas de Prioridade:
// O inteiro n é a quantidade de filas que serão criadas; cada fila tem uma
// prioridade. Neste programa, será criado um bloco de 4 filas, sendo:
// fila[0] => idosos (idade >= 60) com agravante de saúde;
// fila[1] => não idosos, com agravante de saúde;
// fila[2] => idosos, sem agravante de saúde;
// fila[3] => não idosos, sem agravante de saúde.

int main()
{
    fila_t *fila = criar(4);

    int n_acoes;
    scanf("%d", &n_acoes);
    getchar(); // Consome o quebra linha (\r).

    for (int i = 0; i < n_acoes; i++)
    {
        getchar(); // Consome o quebra linha (\n).
        char acao[10];
        read_word_static(stdin, acao);

        if (strcmp(acao, "ENTRA") == 0)
        {
            pessoa_t *pessoa = ler_info_pessoa();

            if (fila_cheia(fila, 4))
            {
                printf("FILA CHEIA\n");
                if (i != n_acoes - 1) printf("\n");
            }
            else
            {
                if (pessoa->idade >= 60 && pessoa->agravante == TRUE)
                    inserir(fila, 0, pessoa);
                else if (pessoa->agravante == TRUE)
                    inserir(fila, 1, pessoa);
                else if (pessoa->idade >= 60)
                    inserir(fila, 2, pessoa);
                else
                    inserir(fila, 3, pessoa);
            }
        }
        else if (strcmp(acao, "SAI") == 0)
        {
            if (fila_vazia(fila, 4))
            {
                printf("FILA VAZIA");
                if (i != n_acoes - 1) printf("\n");
            }
            else
            {
                void *pessoa;
                remover(fila, 4, &pessoa);

                imprimir_info_pessoa(pessoa);
                if (i != n_acoes - 1) printf("\n");
            }
        }
    }

    destruir(fila, 4);

    return 0;
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

/**
 * @brief Lê da entrada padrão as informações de uma pessoa (nome, idade e agravante,
 * separados por espaço) e as armazena em uma struct pessoa.
 * 
 * @return ponteiro para a struct com as informações lidas (pessoa_t*).
 */
pessoa_t *ler_info_pessoa()
{
    pessoa_t *pessoa = (pessoa_t *) malloc(sizeof(pessoa_t));

    read_word_static(stdin, pessoa->nome);
    scanf("%d", &pessoa->idade);
    getchar(); // Consome o espaço.
    scanf("%d", &pessoa->agravante);
    getchar(); // Consome o quebra linha (\r).

    return pessoa;
}

/**
 * @brief Imprime na saída padrão as informações de uma pessoa (nome, idade e
 * agravante, separados por espaço).
 * 
 * @param pessoa ponteiro para a struct pessoa contendo as informações que devem
 * ser impressas.
 */
void imprimir_info_pessoa(pessoa_t *pessoa)
{
    printf("%s %d %d", pessoa->nome, pessoa->idade, pessoa->agravante);
}