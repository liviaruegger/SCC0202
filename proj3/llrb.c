/**
 * @file   llrb.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Projeto 03: Árvore Rubro-Negra (LLRB)
 *         
 * @date   2021-12-16
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "llrb.h"

#define RED 'r'
#define BLACK 'b'

struct node
{
    int data;
    char color;
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
 * @brief Função auxiliar que faz a troca de cores entre dois nós.
 * 
 * @param node1 nó 1, que deve trocar de cor com o nó 2;
 * @param node2 nó 2, que deve trocar de cor com o nó 1.
 */
static void swap_colors(node_t *node1, node_t *node2)
{
    char temp = node1->color;
    node1->color = node2->color;
    node2->color = temp;
}

/**
 * @brief Cria uma árvore vazia.
 * 
 * @return ponteiro para a árvore criada (tree_t *).
 */
tree_t *create()
{
    tree_t *tree = (tree_t *) malloc(sizeof(tree_t));
    if (tree) tree->root = NULL;
    return tree;
}

/**
 * @brief A partir da raiz, desaloca a memória ocupada por todos os nós de uma
 * sub-árvore binária.
 * 
 * @param root ponteiro para o nó raiz da sub-árvore.
 */
static void destroy_subtree(node_t *root)
{
	if (root)
	{
		destroy_subtree(root->left);
		destroy_subtree(root->right);
		free(root);
	}
}

/**
 * @brief Desaloca toda a memória ocupada por uma árvore binária.
 * 
 * @param root ponteiro para a árvore (struct contendo o ponteiro para raiz).
 */
void destroy(tree_t *tree)
{
	if (tree)
	{
        destroy_subtree(tree->root);
        free(tree);
	}
}

/**
 * @brief Função auxiliar que cria um novo nó de Árvore Rubro-Negra (LLRB)
 * com a informação dada. Por definição, todo novo nó é da cor vermelha.
 * 
 * @param data informação a ser inserida no nó (chave);
 * @return ponteiro para o nó criado (node_t *). 
 */
static node_t *new_node(int data)
{
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (!new_node) return NULL;

    new_node->left  = NULL;
    new_node->right = NULL;
    new_node->data  = data;
    new_node->color = RED;
    
    return new_node;
}

/**
 * @brief Função recursiva que, partir de uma dada raiz, insere na árvore LLRB
 * um dado valor, mantendo os critérios de ordem da LLRB.
 * 
 * @param root raiz da árvore LLRB;
 * @param data valor que deve ser inserido na árvore (em um novo nó);
 * @return nó raiz após a inserção (node_t *).
 */
static node_t *_insert(node_t *root, int data)
{
    // Se a raiz for nula, cria e retorna um novo nó.
    if (!root) return new_node(data);
 
    if (data < root->data) // Vai para a sub-árvore da esquerda.
        root->left = _insert(root->left, data);
    else if (data > root->data) // Vai para sub-árvore da direita.
        root->right = _insert(root->right, data);
    else // Se o valor já existe na árvore, apenas encerra a operação.
        return root;
 
    /* A partir daqui, a função corrige a ordem da LLRB */

    // Filho da direita é vermelho; filho da esquerda é preto ou nulo.
    if (root->right && root->right->color == RED
    && (!root->left || root->left->color == BLACK))
    {
        root = rotate_left(root);
        swap_colors(root, root->left);      
    }
    
    // Filho da esquerda e neto da esquerda são vermelhos.
    if (root->left && root->left->color == RED 
    && (root->left->left && root->left->left->color == RED))
    {
        root = rotate_right(root);
        swap_colors(root, root->right);
    }
    
    // Ambos os filhos são vermelhos.
    if (root->left && root->left->color == RED
    && (root->right && root->right->color == RED))
    {
        // Inverte as cores dos três nós (raiz e filhos).
        root->color = (root->color == RED) ? BLACK : RED;
        root->left->color = BLACK;
        root->right->color = BLACK;
    }
 
    return root;
}

/**
 * @brief Dada uma árvore do tipo LLRB e um valor que deve ser inserido nela,
 * chama a função de inserção recursiva a partir do nó raiz.
 * 
 * @param llrb_tree árvore LLRB na qual o valor deve ser inserido;
 * @param data valor a ser inserido.
 */
void insert(tree_t *llrb_tree, int data)
{
    if (llrb_tree) llrb_tree->root = _insert(llrb_tree->root, data);
}

/**
 * @brief Função recursiva que, dada uma chave e a raiz de uma árvore binária,
 * faz um percurso em-ordem pela árvore até encontrar a posição da chave,
 * salvando, em um endereço dado, seu sucessor imediato no percurso.
 * 
 * @param root raiz da árvore binária onde o percurso deve ser feito;
 * @param key chave da qual buscamos o sucessor;
 * @param last endereço onde será armazenado o valor encontrado em cada chamada
 * recursiva da função, de tal forma que pode ser acessado na chamada seguinte;
 * @param successor endereço onde será armazenado o sucessor que buscamos.
 */
static void _successor(node_t *root, int key, int *last, int *successor)
{
    if (!root) return;

    _successor(root->left, key, last, successor);

    if ((*last) == key)
    {
        *successor = root->data;
        *last = -1; // Reseta.
        return;
    }
    
    *last = root->data;
    _successor(root->right, key, last, successor);
}

/**
 * @brief Dada uma chave e uma árvore binária, chama, a partir do nó raiz, uma
 * função recursiva que encontra o sucessor da chave em um percurso em-ordem
 * pela árvore.
 * 
 * @param tree ponteiro para a árvore (struct contendo o ponteiro para raiz);
 * @param key chave da qual buscamos o sucessor;
 * @return valor do sucessor da chave no percurso em-ordem pela árvore (int). 
 */
int successor(tree_t *tree, int key)
{
    int last = -1;
    int successor = -1;

    if (tree) _successor(tree->root, key, &last, &successor);

    return successor;
}

/**
 * @brief Função recursiva que, dada uma chave e a raiz de uma árvore binária,
 * faz um percurso em-ordem pela árvore até encontrar a posição da chave,
 * salvando, em um endereço dado, seu predecessor imediato no percurso.
 * 
 * @param root raiz da árvore binária onde o percurso deve ser feito;
 * @param key chave da qual buscamos o predecessor;
 * @param last endereço onde será armazenado o valor encontrado em cada chamada
 * recursiva da função, de tal forma que pode ser acessado na chamada seguinte;
 * @param predecessor endereço onde será armazenado o predecessor que buscamos.
 */
static void _predecessor(node_t *root, int key, int *last, int *predecessor)
{
    if (!root) return;
    
    _predecessor(root->left, key, last, predecessor);
    
    if (root->data == key)
    {
        *predecessor = (*last);
        return;
    }
    
    *last = root->data;
    _predecessor(root->right, key, last, predecessor);
}

/**
 * @brief Dada uma chave e uma árvore binária, chama, a partir do nó raiz, uma
 * função recursiva que encontra o predecessor da chave em um percurso em-ordem
 * pela árvore.
 * 
 * @param tree ponteiro para a árvore (struct contendo o ponteiro para raiz);
 * @param key chave da qual buscamos o predecessor;
 * @return valor do predecessor da chave no percurso em-ordem pela árvore (int).
 */
int predecessor(tree_t *tree, int key)
{
    int last = -1;
    int predecessor = -1;

    if (tree) _predecessor(tree->root, key, &last, &predecessor);

    return predecessor;
}

/**
 * @brief Encontra o máximo valor armazenado em uma Árvore Binária de Busca (ABB)
 * de qualquer tipo (funciona com treaps, rubro-negras etc). 
 * 
 * @param tree ponteiro para a árvore (struct contendo o ponteiro para raiz);
 * @return máximo valor armazenado na árvore (int).
 */
int maximum(tree_t *tree)
{
    if (!tree || !tree->root) return -1;

    node_t *aux = tree->root;
    node_t *prev = NULL;

    while (aux)
    {
        prev = aux;
        aux = aux->right;
    }
    
    if (prev) return prev->data;
}

/**
 * @brief Encontra o mínimo valor armazenado em uma Árvore Binária de Busca (ABB)
 * de qualquer tipo (funciona com treaps, rubro-negras etc). 
 * 
 * @param tree ponteiro para a árvore (struct contendo o ponteiro para raiz);
 * @return mínimo valor armazenado na árvore (int).
 */
int minimum(tree_t *tree)
{
    if (!tree || !tree->root) return -1;
    
    node_t *aux = tree->root;
    node_t *prev = NULL;

    while (aux)
    {
        prev = aux;
        aux = aux->left;
    }
    
    if (prev) return prev->data;
}

/**
 * @brief Imprime, na saída padrão, os elementos de uma árvore binária separados
 * por espaços, seguindo o percurso pré-ordem.
 * 
 * @param root ponteiro para o nó raiz da árvore a ser impressa.
 */
void print_preorder(node_t *root)
{
	if (root)
	{
        printf("%d ", root->data);
		print_preorder(root->left);
		print_preorder(root->right);
	}
}

/**
 * @brief Imprime, na saída padrão, os elementos de uma árvore binária separados
 * por espaços, seguindo o percurso em-ordem.
 * 
 * @param root ponteiro para o nó raiz da árvore a ser impressa.
 */
void print_inorder(node_t *root)
{
	if (root)
	{
		print_inorder(root->left);
		printf("%d ", root->data);
		print_inorder(root->right);
	}
}

/**
 * @brief Imprime, na saída padrão, os elementos de uma árvore binária separados
 * por espaços, seguindo o percurso pós-ordem.
 * 
 * @param root ponteiro para o nó raiz da árvore a ser impressa.
 */
void print_postorder(node_t *root)
{
	if (root)
	{
		print_postorder(root->left);
		print_postorder(root->right);
		printf("%d ", root->data);
	}
}



/* Funções auxiliares de busca (não utilizadas neste trabalho) */

static node_t *search(node_t *root, int key)
{
    // Caso base: a raiz é nula.
    if (!root) return NULL;

    // Caso base: a chave está na raiz.
    if (root->data == key) return root;

    // Chamada recursiva para a sub-árvore correta:
    return key < root->data ? search(root->left, key) : search(root->right, key);
}

static node_t *find_parent(node_t *root, int key)
{
    // Caso base: raiz é nula.
    if (!root) return NULL;

    // Caso base: chave está em um dos filhos.
    if (root->left && root->left->data == key) return root;
    if (root->right && root->right->data == key) return root;

    // Chamadas recursivas.
    node_t *aux = find_parent(root->left, key);
    if (!aux) aux = find_parent(root->right, key);

    return aux;
}