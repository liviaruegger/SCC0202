/**
 * @file   lista-palavras.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 01: Palavras Mais Frequentes
 * 
 * @date   2021-09-22
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista-palavras.h"

typedef enum {false, true} bool;

struct palavra
{
    int n_ocorrencias;
    char *palavra;
};

struct lista
{
    int tamanho;
    palavra_t **palavras;
};

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

    string[size - 1] = '\0';

    return string;
}

/**
 * @brief Insere uma nova palavra na lista. Caso ela já tenha sido inserida, adiciona 
 * um ao seu contador de ocorrências.
 * 
 * @param nova_palavra string (char *) contendo a palavra que deve ser adicionada à lista;
 * @param lista ponteiro para a struct lista (contendo tamanho e lista de palavras);
 * @return 1 caso a palavra seja nova, 0 caso ela já esteja na lista (int). 
 */
static int inserir_palavra(char *nova_palavra, lista_t *lista)
{
    // Se a lista já contém palavras, confere se a nova palavra está entre elas.
    if (lista[0].tamanho > 0)
    {
        for (int i = 0; i < lista[0].tamanho; i++)
        {
            if (strcmp(nova_palavra, lista[0].palavras[i]->palavra) == 0)
            {
                lista[0].palavras[i]->n_ocorrencias++;
                return 0;
            }
        }
    }

    // Caso a palavra não tenha sido encontrada na lista, ela é inserida:
    lista->palavras = (palavra_t **) realloc(lista->palavras, (lista->tamanho + 1) * sizeof(palavra_t *));
    lista->palavras[lista->tamanho] = (palavra_t *) malloc(sizeof(palavra_t));
    lista->palavras[lista->tamanho]->palavra = (char *) malloc(strlen(nova_palavra) + 1);

    strcpy(lista->palavras[lista->tamanho]->palavra, nova_palavra);
    lista->palavras[lista->tamanho]->n_ocorrencias = 1;

    return 1;
}

/**
 * @brief Recebe uma frase e a separa em palavras, inserindo cada palavra na lista criada
 * e contando suas ocrrências posteriores (através da função inserir_palavra).
 * 
 * @param frase string (char *) contendo diversas palavras separadas por espaço;
 * @return ponteiro para a lista (struct) que foi criada (lista_t *). 
 */
lista_t *criar_lista(char *frase)
{
    // Cria uma lista vazia.
    lista_t *lista = (lista_t *) malloc(sizeof(lista_t));
    lista->tamanho = 0;
    lista->palavras = NULL; 

    // Separa a frase em palavras e, para cada uma, chama a função inserir_palavra.
    char *palavra_temp = strtok(frase, " ");
    while (palavra_temp != NULL)
    {
        int inseriu_palavra = inserir_palavra(palavra_temp, lista);
        lista->tamanho += inseriu_palavra;

        palavra_temp = strtok(NULL, " ");
    }
    
    free(palavra_temp);

    return lista;
}

/**
 * @brief (Bubble sort) Ordena a lista de palavras segundo dois critérios: primeiramente,
 * pelo número de ocorrências (do maior para o menor); caso duas ou mais palavras tenham o
 * mesmo número de ocorrências, elas serão ordenadas alfabeticamente.
 * 
 * @param lista ponteiro para a struct lista (contendo tamanho e lista de palavras).
 */
void ordenar_lista(lista_t *lista)
{
    bool trocou;
    do
    {
        trocou = false;

        // Percorre a lista da segunda à última palavra.
        for (int i = 1; i < lista->tamanho; i++) 
        {
            // Se está fora de ordem (critério frequência), faz a troca.
            if (lista->palavras[i - 1]->n_ocorrencias < lista->palavras[i]->n_ocorrencias)
            {
                palavra_t *temp = lista->palavras[i - 1];
                lista->palavras[i - 1] = lista->palavras[i];
                lista->palavras[i] = temp;
                trocou = true;
            }
            
            // Se o número de ocorrências das duas palavras é o mesmo, checa se elas estão
            // em ordem alfabética; se não estiverem, faz a troca.
            else if (lista->palavras[i - 1]->n_ocorrencias == lista->palavras[i]->n_ocorrencias)
            {
                if (strcmp(lista->palavras[i - 1]->palavra, lista->palavras[i]->palavra) > 0)
                {
                    palavra_t *temp = lista->palavras[i - 1];
                    lista->palavras[i - 1] = lista->palavras[i];
                    lista->palavras[i] = temp;
                    trocou = true;
                }
            }
        }

    } while (trocou != false);
} 

/**
 * @brief Imprime, na saída padrão, as n primeiras palavras da lista e seus respectivos
 * números de ocorrências.
 * 
 * @param lista ponteiro para a struct lista (contendo tamanho e lista de palavras).
 * @param n número de palavras que devem ser impressas.
 */
void imprimir_palavras(lista_t *lista, int n)
{
    if (n > lista->tamanho) n = lista->tamanho;
    
    for (int i = 0; i < (n - 1); i++)
    {
        printf("%s %d\n", lista->palavras[i]->palavra, lista->palavras[i]->n_ocorrencias);
    }

    printf("%s %d", lista->palavras[n - 1]->palavra, lista->palavras[n - 1]->n_ocorrencias);

}

/**
 * @brief Desaloca toda a memória utilizada por uma lista.
 * 
 * @param lista ponteiro para a struct lista (contendo tamanho e lista de palavras).
 */
void destruir_lista(lista_t *lista)
{
    for (int i = 0; i < lista->tamanho; i++)
    {
        free(lista->palavras[i]->palavra);
        free(lista->palavras[i]);
    }
    free(lista->palavras);
    free(lista);
}