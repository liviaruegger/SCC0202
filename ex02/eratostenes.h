/**
 * @file   eratostenes.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 02: Crivo de Eratóstenes
 * 
 * @date   2021-09-30
 * 
 */

#define VALOR_MAXIMO 10000

typedef struct lista lista_t;

lista_t *criar_lista_de_primos();
void imprimir_primos(lista_t *lista, int indices[], int n_impressoes);
void desalocar_lista(lista_t *lista);