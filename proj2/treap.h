/**
 * @file   treap.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Projeto 02: Árvores Treaps
 *         
 * @date   2021-12-15
 * 
 */

typedef struct node node_t;

typedef struct treap
{
    node_t *root;
}   treap_t;

treap_t *create();
void destroy(node_t *root);
int insert(treap_t *treap, int key, int priority);
int remove_node(treap_t *treap, int key);
int search(node_t *root, int key);
int height(node_t *root);

void print_inorder(node_t *root);
void print_preorder(node_t *root);
void print_postorder(node_t *root);
void print_level_order(node_t *root);
void print_given_level(node_t *root, int level);