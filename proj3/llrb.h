/**
 * @file   llrb.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Projeto 03: Árvore Rubro-Negra (LLRB)
 *         
 * @date   2021-12-16
 * 
 */

typedef struct node node_t;

typedef struct llrb_tree
{
    node_t *root;
}   tree_t;

tree_t *create();
void destroy(tree_t *tree);
void insert(tree_t *llrb_tree, int data);

int successor(tree_t *tree, int key);
int predecessor(tree_t *tree, int key);
int maximum(tree_t *tree);
int minimum(tree_t *tree);

void print_preorder(node_t *root);
void print_inorder(node_t *root);
void print_postorder(node_t *root);