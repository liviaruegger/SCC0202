/**
 * @file   main.c
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SCC0202 - Algoritmos e Estruturas de Dados I
 *         Exercício 11: Impressão de Árvores Binárias de Busca
 *         
 * @date   2021-12-13
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

void read_word_static(FILE *stream, char *word);

int main(void)
{
	char comando[10];
	char ordem[10];

	arvore_t *a = criar();
	
	while (!feof(stdin))
	{
		read_word_static(stdin, comando);

		if (strcmp(comando, "insercao") == 0)
		{
			int valor;
			scanf("%d", &valor);
			getchar(); // Consome o '\r'
			getchar(); // Consome o '\n'

			inserir(&a->raiz, valor);
		}
		else if (strcmp(comando, "impressao") == 0)
		{
			read_word_static(stdin, ordem);

			if (esta_vazia(a)) printf("VAZIA");
			else if (strcmp(ordem, "pre-ordem") == 0) pre_ordem(a->raiz);
			else if (strcmp(ordem, "em-ordem") == 0) em_ordem(a->raiz);
			else if (strcmp(ordem, "pos-ordem") == 0) pos_ordem(a->raiz);
			printf("\r\n");
		}
	}

	finalizar(a->raiz);
	free(a);
	
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