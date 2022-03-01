/**
 * @file   ab.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 10: Árvores Binárias - Soma de Nós Filhos
 *         
 * @date   2021-12-06
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "ab.h"

struct no
{
    int id;
    int info;
    no_t *esq;
    no_t *dir;
};

arvore_t *criar()
{
    arvore_t *a = (arvore_t *) malloc(sizeof(arvore_t));
    a->raiz = NULL;
    return a;
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

static no_t *busca(no_t *raiz, int id)
{
    if (raiz == NULL)
        return NULL;

    if (raiz->id == id)
        return raiz;

    no_t *p = busca(raiz->esq, id);
    if (p == NULL)
        p = busca(raiz->dir, id);

    return p;
}

int inserir_raiz(arvore_t *a, int id, int info, int id_esq, int id_dir)
{
    if (a == NULL) return 0;
    if (a->raiz != NULL) return 0; // Já existe raiz.
    
    // Criar nó raiz:
    no_t *p = (no_t *) malloc(sizeof(no_t));
    p->id = id;
    p->info = info;
    p->esq = NULL;
    p->dir = NULL;

    // Inserir nó raiz na árvore:
    if (a != NULL) a->raiz = p;
    
    // Criar nó da esquerda (se houver).
    if (id_esq != -1)
    {
        no_t *p_esq = (no_t *) malloc(sizeof(no_t));
        p_esq->id = id_esq;
        //p_esq->info = -1;
        p_esq->esq = NULL;
        p_esq->dir = NULL;

        p->esq = p_esq;
    }
    
    // Criar nó da direita (se houver).
    if (id_dir != -1)
    {
        no_t *p_dir = (no_t *) malloc(sizeof(no_t));
        p_dir->id = id_dir;
        //p_dir->info = -1;
        p_dir->esq = NULL;
        p_dir->dir = NULL;

        p->dir = p_dir;
    }

    return 1;
}

int inserir_filho(arvore_t *a, int id, int info, int id_esq, int id_dir)
{
    no_t *p = busca(a->raiz, id);

    if (p == NULL) return 0;
    
    p->info = info;

    // Criar nó da esquerda (se houver).
    if (id_esq != -1)
    {
        no_t *p_esq = (no_t *) malloc(sizeof(no_t));
        p_esq->id = id_esq;
        //p_esq->info = -1;
        p_esq->esq = NULL;
        p_esq->dir = NULL;

        p->esq = p_esq;
    }
    
    // Criar nó da direita (se houver).
    if (id_dir != -1)
    {
        no_t *p_dir = (no_t *) malloc(sizeof(no_t));
        p_dir->id = id_dir;
        //p_dir->info = -1;
        p_dir->esq = NULL;
        p_dir->dir = NULL;

        p->dir = p_dir;
    }

    return 1;
}

static void verificar_soma_no(no_t *no, bool *flag)
{
    // Se for nó folha, retorna.
    if (no != NULL && no->esq == NULL && no->dir == NULL) return;

    // Se tiver apenas um filho, verifica se o valor do filho é igual ao do pai.    
    if (no->esq != NULL && no->dir == NULL)
    {
        if (no->info == no->esq->info)
        {
            verificar_soma_no(no->esq, flag);
        }
        else
        {
            *flag = false;
            return;
        }
    }
    else if (no->esq == NULL && no->dir != NULL)
    {
        if (no->info == no->dir->info)
        {
            verificar_soma_no(no->dir, flag);
        }
        else
        {
            *flag = false;
            return;
        }
    }
    else // Se tiver dois filhos, verifica se a soma de seus valores é igual ao valor do pai.
    {
        if (no->info == no->dir->info + no->esq->info)
        {
            verificar_soma_no(no->esq, flag);
            verificar_soma_no(no->dir, flag);
        }
        else
        {
            *flag = false;
            return;
        }
    }
}

int verificar_soma_arvore(arvore_t *a)
{
    bool flag = true;
    verificar_soma_no(a->raiz, &flag);
    return flag;
}