/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Projeto 02: Árvores Treaps
 *         
 * @date   2021-12-15
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treap.h"

void read_word_static(FILE *stream, char *word);

int main()
{
    int n;
    scanf("%d\r\n", &n);

    treap_t *treap = create();
    
    char command[10];
    char traversal_type[10];
    int key, priority;

    for (int i = 0; i < n; i++)
    {
        read_word_static(stdin, command);

        if (strcmp(command, "insercao") == 0)
        {
            scanf("%d %d\r\n", &key, &priority);
            if (!insert(treap, key, priority))
                printf("Elemento ja existente\n");
        }
        else if (strcmp(command, "remocao") == 0)
        {
            scanf("%d\r\n", &key);
            if (!remove_node(treap, key))
                printf("Chave nao localizada\n");
        }
        else if (strcmp(command, "buscar") == 0)
        {
            scanf("%d\r\n", &key);
            printf("%d\n", search(treap->root, key));
        }
        else if (strcmp(command, "impressao") == 0)
        {
            read_word_static(stdin, traversal_type);

            if (strcmp(traversal_type, "ordem") == 0)
                print_inorder(treap->root);
            else if (strcmp(traversal_type, "posordem") == 0)
                print_postorder(treap->root);
            else if (strcmp(traversal_type, "preordem") == 0)
                print_preorder(treap->root);
            else if (strcmp(traversal_type, "largura") == 0)
                print_level_order(treap->root);
            
            printf("\n");
        }
    }

    destroy(treap->root);
    free(treap);
    
    return 0;
}

/**
 * @brief Lê e armazena, em um vetor de caracteres estático, uma palavra do arquivo
 * dado até encontrar um espaço, uma quebra de linha ou o fim do arquivo (EOF).
 * Obs: o vetor precisa ter tamanho suficiente para armazenar a palavra; caso não
 * tenha, o programa será abortado ("stack smashing").
 * 
 * @param stream entrada (pode ser um arquivo ou a entrada padrão);
 * @param word vetor de caracteres onde será armazenada a palavra.
 */
void read_word_static(FILE *stream, char *word)
{
    int i = 0;
    do
    {
        word[i] = fgetc(stream);

        if (word[i] == ' ' || word[i] == '\r' || word[i] == '\n' || word[i] == EOF)
		{
			if (word[i] == '\r') fgetc(stream); // Consome o '\n' depois do '\r'
            word[i] = '\0';
		}
        
        i++;

    } while (word[i - 1] != '\0');
}