/**
 * @file   poli.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 08: Polinômios Esparsos
 *         
 * @date   2021-11-14
 * 
 */

typedef struct monomio monomio_t;
typedef struct polinomio polinomio_t;
typedef struct lista lista_t;

lista_t *criar_lista();
polinomio_t *criar_polinomio();
void adicionar_termo(polinomio_t *polinomio, int coef, int grau);
void adicionar_polinomio(lista_t *lista, polinomio_t *polinomio);
polinomio_t *somar_polinomios(lista_t *lista);
void imprimir_polinomio(polinomio_t *polinomio);
void liberar_polinomio(polinomio_t *polinomio);
void liberar_lista(lista_t *lista);