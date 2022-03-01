/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 10: Árvores Binárias - Soma de Nós Filhos
 *         
 * @date   2021-12-06
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "ab.h"

int main()
{
    int n_nos;
    scanf("%d", &n_nos);

    arvore_t *arvore = criar();

    int id, info, id_esq, id_dir;
    scanf("%d %d %d %d", &id, &info, &id_esq, &id_dir);
    inserir_raiz(arvore, id, info, id_esq, id_dir);

    for (int i = 1; i < n_nos; i++)
    {
        scanf("%d %d %d %d", &id, &info, &id_esq, &id_dir);
        inserir_filho(arvore, id, info, id_esq, id_dir);
    }

    bool valor_igual_soma_filhos = verificar_soma_arvore(arvore);

    if (valor_igual_soma_filhos == true) printf("VERDADEIRO");
    else printf("FALSO");
    
    finalizar(arvore->raiz);
    if (arvore != NULL) free(arvore);

    return 0;
}