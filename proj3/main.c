/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Projeto 03: Árvore Rubro-Negra (LLRB)
 *         
 * @date   2021-12-16
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "llrb.h"

enum
{
    INSERT = 1,
    SUCCESSOR,
    PREDECESSOR,
    MAXIMUM,
    MINIMUM,
    PREORDER,
    INORDER,
    POSTORDER
};

int main()
{
    int n;
    scanf("%d", &n);

    tree_t *llrb_tree = create();

    int command, data, value;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case INSERT:
            scanf("%d", &data);
            insert(llrb_tree, data);
            break;
        
        case SUCCESSOR:
            scanf("%d", &data);
            value = successor(llrb_tree, data);
            if (value == -1) printf("erro\n");
            else printf("%d\n", value);
            break;
        
        case PREDECESSOR:
            scanf("%d", &data);
            value = predecessor(llrb_tree, data);
            if (value == -1) printf("erro\n");
            else printf("%d\n", value);
            break;
        
        case MAXIMUM:
            value = maximum(llrb_tree);
            if (value == -1) printf("erro\n");
            else printf("%d \n", value);
            break;
        
        case MINIMUM:
            value = minimum(llrb_tree);
            if (value == -1) printf("erro\n");
            else printf("%d \n", value);
            break;
        
        case PREORDER:
            print_preorder(llrb_tree->root);
            printf("\n");
            break;
        
        case INORDER:
            print_inorder(llrb_tree->root);
            printf("\n");
            break;
        
        case POSTORDER:
            print_postorder(llrb_tree->root);
            printf("\n");
            break;
        }
    }
    
    destroy(llrb_tree);

    return 0;
}