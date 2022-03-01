/**
 * @file   ab.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 10: Árvores Binárias - Soma de Nós Filhos
 *         
 * @date   2021-12-06
 * 
 */

typedef enum {false, true} bool;

typedef struct no no_t;

typedef struct arvore
{
	no_t *raiz;
}   arvore_t;

arvore_t *criar();
void finalizar(no_t *raiz);
int inserir_raiz(arvore_t *a, int id, int info, int id_esq, int id_dir);
int inserir_filho(arvore_t *a, int id, int info, int id_esq, int id_dir);
int verificar_soma_arvore(arvore_t *a);