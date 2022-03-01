/**
 * @file   bignum.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 09: Grandes Números
 *         
 * @date   2021-11-15
 * 
 */

typedef struct numero numero_t;

numero_t *criar(int sinal);
void adicionar_algarismo(numero_t *numero, int alg);
numero_t *somar(numero_t *numero1, numero_t *numero2);
int comparar(numero_t *numero1, numero_t *numero2);
void imprimir(numero_t *numero);
void liberar(numero_t *numero);