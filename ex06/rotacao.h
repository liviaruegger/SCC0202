/**
 * @file   rotacao.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 06: Rotação de Lista
 *         
 * @date   2021-10-11
 * 
 */

typedef int elem;
typedef struct lista lista_t;

lista_t *criar();
void inserir(lista_t *lista, elem x);
void rotacionar(lista_t *lista, int n_rotacoes);
void imprimir(lista_t *lista);
void liberar(lista_t *lista);