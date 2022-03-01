/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 05: Sequência Balanceada
 *         
 * @date   2021-10-09
 * 
 */

#include <stdio.h>
#include "pilha.h"

typedef enum {false, true} bool;

bool compativel(char a, char b);

int main()
{
    char leitura;

    do
    {
        pilha_t *pilha = create();
        bool balanceado = true;

        do
        {
            leitura = getchar();

            if (balanceado == true)
            {           
                if (leitura == '[' || leitura == '(' || leitura == '{')
                {
                    push(pilha, leitura);
                }
                else if (leitura == '"')
                {
                    if (is_empty(pilha))
                    {
                        push(pilha, leitura);
                    }
                    else
                    {
                        char ultimo;
                        top(pilha, &ultimo);
                        
                        if (ultimo == '"') pop(pilha, &ultimo);
                        else push(pilha, leitura);
                    }
                }
                else if (leitura == ']' || leitura == ')' || leitura == '}')
                {
                    if (is_empty(pilha))
                    {
                        balanceado = false;
                    }
                    else
                    {
                        char ultimo;
                        top(pilha, &ultimo);

                        if (compativel(ultimo, leitura)) pop(pilha, &ultimo);
                        else balanceado = false;
                    }
                }
            }

        } while (leitura != '\r' && leitura != EOF);
        getchar(); // Consome o '\n' depois do '\r'.

        // Se sobrou algum elemento, a sequência não é balanceada.
        if (!is_empty(pilha)) balanceado = false;
        
        if (balanceado) printf("BALANCEADO");
        else printf("NÃO BALANCEADO");
        if (leitura != EOF) printf("\r\n");

        destroy(pilha);

    } while (leitura != EOF);
    
    return 0;
}

/**
 * @brief Checa se dois caracteres delimitadores (colchete, parênteses ou chave)
 * são do mesmo tipo e opostos (ou seja, se um "fecha" o outro).
 * 
 * @param a caractere que deve abrir a sequência;
 * @param b caractere que deve fechar a sequência;
 * @return true (são do mesmo tipo e opostos);
 * @return false.
 */
bool compativel(char a, char b)
{
    if (a == '[' && b == ']') return true;
    else if (a == '(' && b == ')') return true;
    else if (a == '{' && b == '}') return true;
    else return false;
}