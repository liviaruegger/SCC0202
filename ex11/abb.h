/**
 * @file   abb.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 11: Impressão de Árvores Binárias de Busca
 *         
 *         [TAD desenvolvido em aula pelo Prof. Marcelo Manzato]
 *         
 * @date   2021-12-13
 * 
 */

typedef int elem;

typedef struct no no_t;

typedef struct arvore
{
	no_t *raiz;
} 	arvore_t;

arvore_t *criar();
int esta_vazia(arvore_t *a);
void finalizar(no_t *raiz);
void imprimir(no_t *raiz);
int altura(no_t *raiz);
void pre_ordem(no_t *raiz);
void em_ordem(no_t *raiz);
void pos_ordem(no_t *raiz);
no_t *busca(no_t *raiz, elem x);
int inserir(no_t **raiz, elem x);
int remover(no_t **raiz, elem x);