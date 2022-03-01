/**
 * @file   abb.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 11: Impressão de Árvores Binárias de Busca
 *         
 *         [TAD desenvolvido em aula pelo Prof. Marcelo Manzato]
 *         
 * @date   2021-12-13
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

struct no
{
	no_t *esq;
	no_t *dir;
	elem info;
};

arvore_t *criar()
{
	arvore_t *a = (arvore_t *) malloc(sizeof(arvore_t));
	a->raiz = NULL;
	return a;
}

int esta_vazia(arvore_t *a)
{
	if (a != NULL)
	{
		if (a->raiz == NULL)
			return 1;
	}
	return 0;
}

void finalizar(no_t *raiz)
{
	if (raiz != NULL)
	{
		finalizar(raiz->esq);
		finalizar(raiz->dir);
		free(raiz);
	}
}

void imprimir(no_t *raiz)
{
	if (raiz != NULL)
	{
		printf("%d(", raiz->info);
		imprimir(raiz->esq);
		printf(",");
		imprimir(raiz->dir);
		printf(")");
	}
	else
	{
		printf("null");
	}
}

int altura(no_t *raiz)
{
	if (raiz == NULL)
		return 0;

	int alt_esq = 1 + altura(raiz->esq);
	int alt_dir = 1 + altura(raiz->dir);

	if (alt_esq > alt_dir)
		return alt_esq;
	else
		return alt_dir;
}

void pre_ordem(no_t *raiz)
{
	if (raiz != NULL)
	{
		printf("%d ", raiz->info);
		pre_ordem(raiz->esq);
		pre_ordem(raiz->dir);
	}
}

void em_ordem(no_t *raiz)
{
	if (raiz != NULL)
	{
		em_ordem(raiz->esq);
		printf("%d ", raiz->info);
		em_ordem(raiz->dir);
	}
}

void pos_ordem(no_t *raiz)
{
	if (raiz != NULL)
	{
		pos_ordem(raiz->esq);
		pos_ordem(raiz->dir);
		printf("%d ", raiz->info);
	}
}

no_t *busca(no_t *raiz, elem x)
{
	if (raiz == NULL)
	{
		return NULL;
	}
	else if (raiz->info == x)
	{
		return raiz;
	}
	else if (x < raiz->info)
	{
		return busca(raiz->esq, x);
	}
	else
	{
		return busca(raiz->dir, x);
	}
}

int inserir(no_t **raiz, elem x)
{
	if (*raiz == NULL)
	{
		*raiz = (no_t *) malloc(sizeof(no_t));
		(*raiz)->info = x;
		(*raiz)->esq = NULL;
		(*raiz)->dir = NULL;
		return 1;
	}
	else if (x == (*raiz)->info)
	{
		return 0;
	}
	else if (x < (*raiz)->info)
	{
		return inserir(&(*raiz)->esq, x);
	}
	else
	{
		return inserir(&(*raiz)->dir, x);
	}
}

int remover(no_t **raiz, elem x)
{
	if (*raiz == NULL)
	{
		return 0;
	}
	else if (x < (*raiz)->info)
	{
		return remover(&(*raiz)->esq, x);
	}
	else if (x > (*raiz)->info)
	{
		return remover(&(*raiz)->dir, x);
	}
	else
	{
		if ((*raiz)->esq == NULL && (*raiz)->dir == NULL)
		{
			free(*raiz);
			*raiz = NULL;
			return 1;
		}
		else if ((*raiz)->esq == NULL)
		{
			no_t *aux = *raiz;
			*raiz = (*raiz)->dir;
			free(aux);
			return 1;
		}
		else if ((*raiz)->dir == NULL)
		{
			no_t *aux = *raiz;
			*raiz = (*raiz)->esq;
			free(aux);
			return 1;
		}
		else
		{
			no_t *aux = (*raiz)->esq;
			while (aux->dir != NULL)
			{
				aux = aux->dir;
			}
			(*raiz)->info = aux->info;
			return remover(&(*raiz)->esq, aux->info);
		}
	}
}