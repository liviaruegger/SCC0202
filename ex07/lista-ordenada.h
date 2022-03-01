/**
 * @file   lista-ordenada.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 07: Lista Ordenada
 *         
 * @date   2021-11-07
 * 
 */

typedef struct lista lista_t;

lista_t *criar();
int inserir(lista_t *lista, int codigo, char *nome);
int remover(lista_t *lista, int codigo);
void imprimir(lista_t *lista);
void liberar(lista_t *lista);