// Sudoku.cpp: Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fat(int);
void media(int, int*);

int fat(int n)
{
	if (n == 1)
		return 1;
	else
		return (n * fat(n - 1));
}

float vetor(int n, float *vnotas)
{
	int i;
	float m = 0, soma = 0;

	//fazendo a somatória das notas
	for (i = 0; i < n; i++)
		soma = soma + vnotas[i];

	//dividindo pela quantidade de elementos n
	m = soma / n;

	//retornando a média
	return m;
}

void imprimeSudoku(int sudoku[9][9])
{
	int i, j;
	
	printf("\n\t\t\t");//pula linha + 3 tabulações
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (sudoku[i][j] != 0)
			{
				printf(" %d ", sudoku[i][j]);
			}
			else
			{
				printf(" - ");//imprime "-" se o valor não estiver no intervalo [1..9]
			}
		}
		printf("\n\t\t\t");//pula linha + 3 tabulações
	}
	printf("\n");
}

int main()
{
    
	int i, j, k, l;//variáveis de loop
	int aux, num = 0, pula = 0;//variáveis auxiliares
	int sudoku[9][9];//matriz do jogo
	int controleNum[9], controleLinhas[9], controleColunas[9];//verificadores para criar sudoku inicial

	//limpa controles
	for (i = 0; i < 9; i++)
	{
		controleNum[i] = 0;
		controleLinhas[i] = 0;
		controleColunas[i] = 0;
	}

	//limpa sudoku
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			sudoku[i][j] = 0;
		}
	}
	
	//definição da função rand
	srand(time(NULL));

	//definindo posição e valores iniciais
	for (k = 0; k < 17; k++)
	{
		i = rand() % 9;
		//verifica a quantidade máxima de números iniciais por linha em 3
		while (controleLinhas[i] >= 3)
		{
			i = rand() % 9;
		}
		controleLinhas[i]++;//soma 1 à posição do vetor correspondente a essa linha

		j = rand() % 9;
		//verifica a quantidade máxima de números iniciais por coluna em 3
		while (controleColunas[j] >= 3)
		{
			j = rand() % 9;
		}
		controleColunas[j]++;//soma 1 à posição do vetor correspondente a essa coluna

		aux = rand() % 9;
		//verifica a quantidade máxima para cada número [0..9] como 4 em 17 posições iniciais
		while(controleNum[aux] >= 4)
		{
			aux = rand() % 9;
		}

		//
		for (l = 0; l < 9; l++)
		{
			if (sudoku[l][j] == aux || sudoku[i][l] == aux)//verificação de conflito para linhas e colunas...FALTA QUADRADO 3 X 3
			//---------------
		}
		//
		controleNum[aux]++;//soma 1 à posição do vetor correspondente a esse valor
		sudoku[i][j] = aux;//insere valor no sudoku

	}

	imprimeSudoku(sudoku);
	
	//algoritmo guloso -> deixa espaços vazios
	for (i = 0; i < 9; i++)//passa por cada linha do sudoku 9 x 9
	{
		for (j = 0; j < 9; j++)//passa por cada coluna do sudoku 9 x 9
		{
			if (sudoku[i][j] == 0)//verifica se sudoku[i][j] já está preenchido
			{
				pula = 0;
				num = 1;//valor inicial a ser inserido
				while (num <= 9 && pula != 1)
				{
					//configura incialmente como não existindo conflito entre o valor atual, linha, coluna e quadrado 3 x 3
					//pula = 1 significa que há conflito
					k = 0;
					while (k <= 9)//índice para passar pela linha e coluna da posiçao atual
					{
						pula = 0;
						if (sudoku[k][j] == num || sudoku[i][k] == num)//compara valor com linha e coluna
						//FALTA COMPARAÇÃO COM O QUADRADO 3 X 3
						{
							pula = 1;
							num++;
							k = 0;
						}
						else
							k++;
					}
					num %= 9;
					if (pula == 0 && num <= 9)
					{
						sudoku[i][j] = num;
						pula = 1;

						imprimeSudoku(sudoku);
					}
				}
			}
		}
	}

	system("pause");
	return 0;
}

