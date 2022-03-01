/**
 * @file   dicionario.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Projeto 01: Skip Lists - Criando Um Dicionário
 *         
 * @date   2021-12-13
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"

typedef struct node node_t;

struct node
{
    char *word;
    char *definition;
    node_t **next; // Cada ponteiro neste vetor corresponde a um nível da skplist.
};

struct skiplist
{
    int level;      // Nível mais alto da skiplist (atual).
    int maxlevel;   // Quantidade máxima de níveis.
    float p;        // Probabilidade de subida de nível.
    node_t *upleft; // Nó de cabeçalho (início).
};

/**
 * @brief Cria um novo nó com as informações referentes a um verbete.
 * 
 * @param word verbete a ser inserido no nó;
 * @param definition definição do verbete a ser inserido no nó;
 * @param level nível que o nó ocupará na skiplist;
 * @return ponteiro para o nó criado (node_t *). 
 */
static node_t *new_node(char *word, char *definition, int level)
{
    node_t *new = (node_t *)malloc(sizeof(node_t));
    if (!new) return NULL;

    new->word = word;
    new->definition = definition;
    new->next = (node_t **)malloc((level + 1) * sizeof(node_t *));
    if (!new->next) return NULL;
    
    for (int i = 0; i < (level + 1); i++)
    {
        new->next[i] = NULL;
    }
    
    return new;
}

/**
 * @brief Cria uma skiplist vazia com informações de nível máximo e probabilidade
 * de subida de nível.
 * 
 * @param maxlevel quantidade máxima de níveis que a skiplist poderá atingir;
 * @param p probabilidade de subida de nível (usada na inserção de novos nós);
 * @return ponteiro para a skiplist criada (skiplist_t *). 
 */
skiplist_t *create(int maxlevel, float p)
{
    skiplist_t *skiplist = (skiplist_t *) malloc(sizeof(skiplist_t));
    if (!skiplist) return NULL;

    skiplist->maxlevel = maxlevel;
    skiplist->p = p;
    skiplist->level = 0;
    skiplist->upleft = new_node(NULL, NULL, maxlevel);

    return skiplist;
}

/**
 * @brief Desaloca toda a memória ocupada por uma skiplist.
 * 
 * @param skiplist ponteiro para a skiplist que deve ser destruída.
 */
void destroy(skiplist_t *skiplist)
{
    if (!skiplist) return;

    node_t *aux, *current;
    current = skiplist->upleft->next[0];
    while (current)
    {
        aux = current;
        current = current->next[0];
        if (aux->word) free(aux->word);
        if (aux->definition) free(aux->definition);
        if (aux->next) free(aux->next);
        free(aux);
    }

    free(skiplist->upleft->next);
    free(skiplist->upleft);
    free(skiplist);
}

/**
 * @brief Busca um verbete (nó) no dicionário (skiplist).
 * 
 * @param skiplist ponteiro para a skiplist dicionário;
 * @param word chave (palavra) que deve ser buscada; 
 * @return ponteiro para o nó encontrado (node_t *); retorna nulo caso o verbete
 * não esteja no dicionário. 
 */
static node_t *search(skiplist_t *skiplist, char *word)
{
    if (!skiplist) return NULL;

    node_t *current = skiplist->upleft;

    for (int i = skiplist->level; i >= 0; i--)
    {
        // if (strcmp(palavra1, palavra2) > 0) -> não está em ordem alfabética
        // if (strcmp(palavra1, palavra2) < 0) -> está em ordem alfabética
        while (current->next[i] != NULL && strcmp(current->next[i]->word, word) < 0)
        {
            current = current->next[i];
        }   
    }

    // Possível posição da palavra:
    current = current->next[0];

    // Se a palavra não está nesta posição, ela não está no dicionário.
    if (current != NULL && strcmp(current->word, word) != 0) return NULL;
    else return current;
}

/**
 * @brief Considerando a probalidade definida na struct da skiplist, sorteia
 * sucessivas subidas de nível a partir do zero (não podendo passar do nível
 * máximo definido também na struct skiplist).
 * 
 * @param skiplist ponteiro para a struct skiplist (contendo p e maxlevel);
 * @return nível sorteado (int).
 */
static int draw_level(skiplist_t *skiplist)
{
    float r = (float)rand() / RAND_MAX; // Valor entre 0 e 1.
    int level = 0;
    while (r < skiplist->p && level < skiplist->maxlevel)
    {
        level++;
        r = (float)rand() / RAND_MAX;
    }
    
    return level;
}

/**
 * @brief Insere ordenadamente um novo verbete no dicionário (skiplist).
 * 
 * @param skiplist ponteiro para a skiplist dicionário;
 * @param word verbete que deve ser inserido no dicionário;
 * @param definition definição do verbete;
 * @return 1 (operação realizada com sucesso) ou -1 (erro).
 */
int insert(skiplist_t *skiplist, char *word, char *definition)
{
    if (!skiplist) return -1;

    node_t *current = skiplist->upleft;

    node_t **aux = (node_t **)malloc((skiplist->maxlevel + 1) * sizeof(node_t *));
    for (int i = 0; i <= skiplist->maxlevel; i++)
    {
        aux[i] = NULL;
    }

    // Encontrar a posição correta para inserção.
    for (int i = skiplist->level; i >= 0; i--)
    {
        while (current->next[i] != NULL && strcmp(current->next[i]->word, word) < 0)
        {
            current = current->next[i];
        }

        aux[i] = current;
    }

    current = current->next[0]; // Posição correta.

    if (current != NULL && strcmp(current->word, word) == 0) // Verbete já existe.
    {
        free(word);
        free(definition);
        free(aux);
        return -1;
    }
    else if (current == NULL || strcmp(current->word, word) != 0)
    {
        int new_level = draw_level(skiplist);
        node_t *new = new_node(word, definition, new_level);

        if (!new) // Caso a alocação de novo nó tenha falhado.
        {
            free(word);
            free(definition);
            free(aux);
            return -1;
        }
        
        // Atualizar o nível da skiplist se necessário.
        if (new_level > skiplist->level)
        {
            for (int i = skiplist->level + 1; i <= new_level; i++)
            {
                aux[i] = skiplist->upleft;
            }

            skiplist->level = new_level;
        }

        for (int i = 0; i <= new_level; i++)
        {
            new->next[i] = aux[i]->next[i];
            aux[i]->next[i] = new;
        }

        free(aux);
        return 1;
    }
}

/**
 * @brief Remove um verbete (nó) do dicionário (skiplist).
 * 
 * @param skiplist ponteiro para a skiplist dicionário;
 * @param word chave (palavra) do nó que deve ser removido;
 * @return 1 (operação realizada com sucesso) ou -1 (erro).
 */
int remove_word(skiplist_t *skiplist, char *word)
{
    if (!skiplist) return -1;

    node_t *current = skiplist->upleft;

    node_t **aux = (node_t **)malloc((skiplist->maxlevel + 1) * sizeof(node_t *));

    for (int i = 0; i <= skiplist->maxlevel; i++)
    {
        aux[i] = NULL;
    }
    
    // Encontrar a possível posição do verbete.
    for (int i = skiplist->level; i >= 0; i--)
    {
        while (current->next[i] != NULL && strcmp(current->next[i]->word, word) < 0)
        {
            current = current->next[i];
        }

        aux[i] = current;
    }

    current = current->next[0];

    // Encontrou a palavra?
    if (current == NULL || strcmp(current->word, word) != 0) // Não encontrou.
    {
        free(aux);
        return -1;
    }
    else if (strcmp(current->word, word) == 0) // Encontrou.
    {
        for (int i = 0; i <= skiplist->level; i++)
        {
            if (aux[i]->next[i] != current) break;
            aux[i]->next[i] = current->next[i];
        }

        while (skiplist->level > 0 && skiplist->upleft->next[skiplist->level] == NULL)
        {
            skiplist->level--;
        }
        
        free(current->next);
        free(current->word);
        free(current->definition);
        free(current);
        free(aux);
        return 1;
    }
}

/**
 * @brief Troca a definição de um dado verbete no dicionário (skiplist).
 * 
 * @param skiplist ponteiro para a skiplist dicionário;
 * @param word verbete cuja definição deve ser substituída;
 * @param new_definition nova definição do verbete;
 * @return 1 (operação realizada com sucesso) ou -1 (erro).
 */
int change_definition(skiplist_t *skiplist, char *word, char *new_definition)
{
    node_t *node_ptr = search(skiplist, word);

    if (node_ptr == NULL)
    {
        free(new_definition);
        return -1;
    }

    free(node_ptr->definition);
    node_ptr->definition = new_definition;
    return 1;
}

/**
 * @brief Busca um verbete no dicionário (skiplist) e imprime, na saída padrão,
 * sua definição.
 * 
 * @param skiplist ponteiro para a skiplist dicionário;
 * @param word chave (palavra) que deve ser buscada;
 * @return 1 (operação realizada com sucesso) ou -1 (erro).
 */
int print_definition(skiplist_t *skiplist, char *word)
{
    node_t *node_ptr = search(skiplist, word);

    if (node_ptr == NULL) return -1;
    
    printf("%s %s\n", node_ptr->word, node_ptr->definition);
    return 1;   
}

/**
 * @brief Imprime, na saída padrão, todas as palavras iniciadas com um dado caractere.
 * 
 * @param skiplist ponteiro para a skiplist dicionário;
 * @param c caractere inicial procurado;
 * @return 1 (operação realizada com sucesso) ou -1 (erro). 
 */
int print_all(skiplist_t *skiplist, char c)
{
    if (!skiplist) return -1;

    char ch[2] = {c, '\0'};
    
    node_t *current = skiplist->upleft;

    for (int i = skiplist->level; i >= 0; i--)
    {
        // if (strcmp(palavra1, palavra2) > 0) -> não está em ordem alfabética
        // if (strcmp(palavra1, palavra2) < 0) -> está em ordem alfabética
        while (current->next[i] != NULL && strncmp(current->next[i]->word, ch, 1) < 0)
        {
            current = current->next[i];
        }   
    }

    current = current->next[0];

    if (current == NULL || strncmp(current->word, ch, 1) != 0)
        return -1;
    
    while (current != NULL && strncmp(current->word, ch, 1) == 0)
    {
        printf("%s %s\n", current->word, current->definition);
        current = current->next[0];
    }

    return 1;
}