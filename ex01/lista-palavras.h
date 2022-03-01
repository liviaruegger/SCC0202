/**
 * @file   lista-palavras.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 01: Palavras Mais Frequentes
 * 
 * @date   2021-09-22
 * 
 */

typedef struct palavra palavra_t;
typedef struct lista lista_t;

char *read_line(FILE *stream);

static int inserir_palavra(char *nova_palavra, lista_t *lista);
lista_t *criar_lista(char *frase);
void ordenar_lista(lista_t *lista);
void imprimir_palavras(lista_t *lista, int n);
void destruir_lista(lista_t *lista);