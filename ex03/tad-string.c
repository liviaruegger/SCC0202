/**
 * @file   tad-string.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 03: Substituição de Strings
 * 
 * @date   2021-10-01
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad-string.h"

#define TRUE 0

struct string_erro
{
    char *frase;
    char *erro;
    char *correcao;
};

/**
 * @brief Lê e armazena uma linha do arquivo dado até encontrar uma quebra de linha ou
 * o fim do arquivo (EOF).
 * 
 * @param stream entrada (pode ser um arquivo ou a entrada padrão);
 * @return ponteiro para a string lida (char *). 
 */
static char *read_line(FILE *stream)
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

    string[size - 1] = '\0';

    return string;
}

/**
 * @brief Lê da entrada padrão as strings necessárias para corrigir uma frase (a frase
 * com erros, o erro e a correção) e as armazena em uma struct. 
 * 
 * @return struct contendo as três strings (str_t*). 
 */
str_t *ler_string_para_corrigir()
{
    str_t *string_erro = (str_t *) malloc(sizeof(str_t));

    string_erro->frase = read_line(stdin);
    string_erro->erro = read_line(stdin);
    string_erro->correcao = read_line(stdin);

    return string_erro;
}

/**
 * @brief Dada uma struct contendo três strings (frase, erro e correção), modifica a
 * frase, substituindo os trechos de erro pela correção.
 * 
 * @param string struct contendo as três strings. 
 */
static void corrigir_frase(str_t *string)
{
    int tamanho_frase = strlen(string->frase);
    int tamanho_erro = strlen(string->erro);
    int tamanho_correcao = strlen(string->correcao);

    char *ptr_busca = string->frase;

    while (ptr_busca <= string->frase + (tamanho_frase - tamanho_erro))
    {
        int encontrou_erro = strncmp(string->erro, ptr_busca, tamanho_erro);

        if (encontrou_erro == TRUE)
        {
            // Identifica o trecho de frase após o erro (que será movido):
            char *ptr_mover = ptr_busca + tamanho_erro;
            int tamanho_mover = strlen(ptr_mover);

            // Move o trecho, deixando o espaço exato para a correção:
            memmove(ptr_busca + tamanho_correcao, ptr_mover, tamanho_mover + 1);

            // Copia a correção para o espaço deixado:
            memcpy(ptr_busca, string->correcao, tamanho_correcao);

            ptr_busca += tamanho_correcao;
        }
        else
        {
            ptr_busca++;
        }  
    }
}

/**
 * @brief Imprime na saída padrão a frase contida na struct recebida como parâmetro.
 * Caso o tamanho da frase exceda o tamanho máximo definido, imprime apenas os primeiros
 * n caracteres da string (sendo n o tamanho máximo). 
 * 
 * @param string struct contendo três strings: frase, erro e correção. 
 */
static void imprimir_frase(str_t *string)
{
    int n_caracteres = strlen(string->frase);
    if (n_caracteres > TAMANHO_MAX_SAIDA)
        n_caracteres = TAMANHO_MAX_SAIDA;

    for (int i = 0; i < n_caracteres; i++)
        printf("%c", string->frase[i]);
}

/**
 * @brief Chama as funções corrigir_frase e imprimir_frase, passando como parâmetro a
 * string recebida.
 * 
 * @param string struct contendo três strings: frase, erro e correção. 
 */
void corrigir_e_imprimir(str_t *string)
{
    corrigir_frase(string);
    imprimir_frase(string);
}

/**
 * @brief Desaloca toda a memória ocupada pela struct string.
 * 
 * @param string struct contendo três strings: frase, erro e correção. 
 */
void destruir(str_t *string)
{
    free(string->frase);
    free(string->erro);
    free(string->correcao);
    free(string);
}