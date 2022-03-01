/**
 * @file   treap.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Projeto 02: Árvores Treaps
 *         
 * @date   2021-12-15
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "treap.h"

struct node
{
    int key;
    int priority;
    node_t *left;
    node_t *right;
};

/**
 * @brief Função auxiliar que executa, em uma sub-árvore de raiz y, uma rotação
 * para a direita.
 * 
 * @param y ponteiro para o nó raiz da sub-árvore;
 * @return nó raiz da sub-árvore após a rotação (node_t *). 
 */
static node_t *rotate_right(node_t *y)
{
    node_t *x = y->left;
    node_t *subtree = x->right;
 
    // Rotação:
    x->right = y;
    y->left = subtree;
 
    return x; // Retorna a nova raiz.
}

/**
 * @brief Função auxiliar que executa, em uma sub-árvore de raiz x, uma rotação
 * para a esquerda.
 * 
 * @param x ponteiro para o nó raiz da sub-árvore;
 * @return nó raiz da sub-árvore após a rotação (node_t *). 
 */
static node_t *rotate_left(node_t *x)
{
    node_t *y = x->right;
    node_t *subtree = y->left;
 
    // Rotação:
    y->left = x;
    x->right = subtree;

    return y; // Retorna a nova raiz.
}

/**
 * @brief Cria uma treap vazia.
 * 
 * @return ponteiro para a árvore criada (treap_t *).
 */
treap_t *create()
{
    treap_t *treap = (treap_t *) malloc(sizeof(treap_t));
    if (treap) treap->root = NULL;
    return treap;
}

/**
 * @brief Desaloca toda a memória ocupada por uma árvore binária.
 * 
 * @param root ponteiro para o nó raiz da árvore.
 */
void destroy(node_t *root)
{
	if (root)
	{
		destroy(root->left);
		destroy(root->right);
		free(root);
	}
}

/**
 * @brief Função auxiliar que cria um novo nó com as informações dadas.
 * 
 * @param key chave (parâmetro para ordem de ABB na treap);
 * @param priority prioridade (parâmetro para ordem de heap na treap);
 * @return ponteiro para o nó criado (node_t *). 
 */
static node_t *new_node(int key, int priority)
{
    node_t *node = (node_t *) malloc(sizeof(node_t));
    if (!node) return NULL;

    node->key = key;
    node->priority = priority;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/**
 * @brief Função recursiva que, dadas as informações de chave e prioridade,
 * cria e insere na treap um novo nó. A inserção deve respeitar a condição
 * de heap máximo de acordo com a prioridade de cada nó.
 * 
 * @param root ponteiro para o nó raiz da treap;
 * @param key chave (parâmetro para ordem de ABB na treap);
 * @param priority prioridade (parâmetro para ordem de heap na treap);
 * @param flag endereço receberá 0 caso a inserção seja mal sucedida;
 * @return nó raiz após a inserção (node_t *).
 */
static node_t *_insert(node_t* root, int key, int priority, int *flag)
{
    // Caso base: se chegou a um ponteiro nulo (chamada recursiva depois
    // de um nó folha), cria o novo nó e retorna um ponteiro para ele.
    if (!root) return new_node(key, priority);
    
    // Chave repetida. Inserção falhou.
    if (root->key == key) *flag = 0;
    
    // Chamada recursiva para a sub-árvore correta.
    if (key < root->key) // Quando a chave é menor...
    {
        // Chama a recursão para a sub-árvore da esquerda.
        root->left = _insert(root->left, key, priority, flag);
 
        // Conserta o heap máximo, se necessário.
        if (root->left->priority > root->priority)
            root = rotate_right(root);
    }
    else if (key > root->key) // Quando a chave é maior...
    {
        // Chama a recursão para a sub-árvore da direita.
        root->right = _insert(root->right, key, priority, flag);
 
        // Conserta o heap máximo, se necessário.
        if (root->right->priority > root->priority)
            root = rotate_left(root);
    }

    return root;
}

/**
 * @brief Dada uma treap e as informações para um novo nó, chama a função de
 * inserção recursiva a partir do nó raiz.
 * 
 * @param treap ponteiro para a treap;
 * @param key chave (parâmetro para ordem de ABB na treap);
 * @param priority prioridade (parâmetro para ordem de heap na treap);
 * @return 1 (operação realizada com sucesso) ou 0 (chave repetida).
 */
int insert(treap_t *treap, int key, int priority)
{
    int was_successful = 1;
    node_t *aux = _insert(treap->root, key, priority, &was_successful);

    treap->root = aux; // Atualiza a raiz (pode ter mudado).
    
    return was_successful;
}

/**
 * @brief Função recursiva que, dada a raiz de uma treap, busca nela uma dada
 * chave e, caso a encontre, remove seu nó da árvore.
 * 
 * @param root ponteiro para o nó raiz da treap;
 * @param key chave que buscamos para ser removida;
 * @param flag endereço receberá 1 caso a remoção seja bem sucedida;
 * @return nó raiz após a remoção (node_t *). 
 */
static node_t *_remove_node(node_t *root, int key, int *flag)
{
    if (!root) return NULL;
    
    // Encontrou a chave?
    if (key < root->key)
    {
        // Chamada recursiva para a sub-árvore da esquerda.
        root->left = _remove_node(root->left, key, flag);
    }
    else if (key > root->key)
    {
        // Chamada recursiva para a sub-árvore da direita.
        root->right = _remove_node(root->right, key, flag);
    }
    else // Encontrou a chave.
    {
        if (root->left == NULL) // Não tem filho esquerdo.
        {
            node_t *temp = root->right;
            free(root);
            root = temp; // Filho da direita se torna raiz.
        }
        else if (root->right == NULL) // Não tem filho direito.
        {
            node_t *temp = root->left;
            free(root);
            root = temp; // Filho da esquerda se torna raiz.
        }
        else // Encontrou a chave em um nó que tem ambos os filhos.
        {
            // Rotaciona para a esquerda e faz uma nova chamada recursiva.
            root = rotate_left(root);
            root->left = _remove_node(root->left, key, flag);
        }

        *flag = 1; // Remoção realizada com sucesso.
    }

    return root;
}

/**
 * @brief Dada uma treap e uma chave, chama a função recursiva de remoção a
 * partir do nó raiz.
 * 
 * @param treap ponteiro para a treap;
 * @param key chave que deverá ser removida;
 * @return 1 (operação realizada com sucesso) ou 0 (chave não localizada).
 */
int remove_node(treap_t *treap, int key)
{
    int was_successful = 0;
    node_t *aux = _remove_node(treap->root, key, &was_successful);

    treap->root = aux; // Atualiza a raiz (pode ter mudado).

    return was_successful;
}

/**
 * @brief Busca uma dada chave em uma treap (funciona com qualquer ABB). 
 * 
 * @param root ponteiro para o nó raiz da árvore;
 * @param key chave para a busca;
 * @return 1 (chave encontrada) ou 0 (chave não encontrada).
 */
int search(node_t *root, int key)
{
    // Caso base: a raiz é nula.
    if (!root) return 0;

    // Caso base: a chave está na raiz.
    if (root->key == key) return 1;

    // Chamada recursiva para a sub-árvore correta:
    return key < root->key ? search(root->left, key) : search(root->right, key);
}

/**
 * @brief Dado um nó raiz, calcula a altura de uma árvore binária.
 * 
 * @param root ponteiro para o nó raiz da árvore;
 * @return altura da árvore (int). 
 */
int height(node_t *root)
{
    // Caso base: uma árvore vazia tem altura 0.
	if (!root) return 0;

    // Chamada recursiva para cada um dos filhos.
	int h_left = 1 + height(root->left);
	int h_right = 1 + height(root->right);

    // Retorna o maior dentre os dois valores.
    return h_left > h_right ? h_left : h_right;
}


/* FUNÇÕES DE IMPRESSÃO SEGUNDO TIPO DE PERCURSO */

/**
 * @brief Imprime, na saída padrão, os elementos de uma treap no modelo
 * (<chave>, <prioridade>), seguindo o percurso em-ordem.
 * 
 * @param root ponteiro para o nó raiz da árvore a ser impressa.
 */
void print_inorder(node_t *root)
{
	if (root)
	{
		print_inorder(root->left);
		printf("(%d, %d) ", root->key, root->priority);
		print_inorder(root->right);
	}
}

/**
 * @brief Imprime, na saída padrão, os elementos de uma treap no modelo
 * (<chave>, <prioridade>), seguindo o percurso pré-ordem.
 * 
 * @param root ponteiro para o nó raiz da árvore a ser impressa.
 */
void print_preorder(node_t *root)
{
	if (root)
	{
        printf("(%d, %d) ", root->key, root->priority);
		print_preorder(root->left);
		print_preorder(root->right);
	}
}

/**
 * @brief Imprime, na saída padrão, os elementos de uma treap no modelo
 * (<chave>, <prioridade>), seguindo o percurso pós-ordem.
 * 
 * @param root ponteiro para o nó raiz da árvore a ser impressa.
 */
void print_postorder(node_t *root)
{
	if (root)
	{
		print_postorder(root->left);
		print_postorder(root->right);
		printf("(%d, %d) ", root->key, root->priority);
	}
}

/**
 * @brief Imprime, na saída padrão, os elementos de uma treap no modelo
 * (<chave>, <prioridade>), seguindo o percurso em largura (nível por nível).
 * Este método de impressão possui complexidade de tempo O(n^2) no pior caso.
 * 
 * @param root ponteiro para o nó raiz da árvore a ser impressa.
 */
void print_level_order(node_t *root)
{
    int h = height(root);

    for (int i = 1; i <= h; i++)
    {
        print_given_level(root, i);
    }
}
 
/**
 * @brief Imprime, na saída padrão, os elementos de uma dada linha de uma treap
 * no modelo (<chave>, <prioridade>).
 * 
 * @param root ponteiro para o nó raiz da árvore a ser impressa;
 * @param level nível que deve ser impresso.
 */
void print_given_level(node_t *root, int level)
{
    if (!root) return;

    if (level == 1)
    {
        printf("(%d, %d) ", root->key, root->priority);
    }
    else if (level > 1)
    {
        print_given_level(root->left, level - 1);
        print_given_level(root->right, level - 1);
    }
}