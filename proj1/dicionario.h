/**
 * @file   dicionario.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Projeto 01: Skip Lists - Criando Um Dicionário
 *         
 * @date   2021-12-13
 * 
 */

typedef struct skiplist skiplist_t;

skiplist_t *create(int maxlevel, float p);
void destroy(skiplist_t *skiplist);
int insert(skiplist_t *skiplist, char *word, char *definition);
int remove_word(skiplist_t *skiplist, char *word);
int change_definition(skiplist_t *skiplist, char *word, char *new_definition);
int print_definition(skiplist_t *skiplist, char *word);
int print_all(skiplist_t *skiplist, char c);