/**
 * @file   tad-string.h
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 03: Substituição de Strings
 * 
 * @date   2021-10-01
 * 
 */

#define TAMANHO_MAX_SAIDA 100

typedef struct string_erro str_t;

str_t *ler_string_para_corrigir();
void corrigir_e_imprimir(str_t *string);
void destruir(str_t *string);