#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//função que limpa variáveis de ínicio
void limpaVariaveis(int sudoku[9][9], int controleNum[9], int controleLinhas[18], int controleColunas[18])
{
	int i, j;
	
	//limpa variáveis	
	for (i = 0; i < 9; i++)
	{
		//limpa controles
		controleNum[i] = 0;
		controleNum[i + 9] = 0;
		
		controleLinhas[i] = 0;
		controleLinhas[i + 9] = 0;
		
		controleColunas[i] = 0;
		controleColunas[i + 9] = 0;

		for (j = 0; j < 9; j++)
			sudoku[i][j] = 0;//limpa sudoku
	}
}

//função que verifica conflitos de números em relação a linha, coluna e quadro 3 x 3(Retorna 1 se houver conflito)
bool verificaConflito(int sudoku[9][9], int linha, int coluna, int valor)
{
	int i, j;
	int quadro = 0;

	if (sudoku[linha][coluna] != 0)//se a posição já estiver preenchida
		return true;//então há conflito

	//definição do quadrante 3 x 3 para posição
	if (coluna <= 2)//colunas 0, 1 e 2
		quadro = 1;
	if (coluna > 2 && coluna < 6)//colunas 3, 4 e 5
		quadro = 2;
	if (coluna >= 6)//colunas 6, 7 e 8
		quadro = 3;
	//linhas 0, 1 e 2 não altera a variável quadro
	if (linha > 2 && linha < 6)//linhas 3, 4 e 5
		quadro += 3;
	if (coluna >= 6)//linhas 6, 7 e 8
		quadro += 6;

	//verifica conflito em relação ao quadro 3 x 3 correspondente ao valor
	switch (quadro)
	{
	case 1:
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (sudoku[i][j] == valor)
					return true;
			}
		}
		break;

	case 2:
		for (i = 0; i < 3; i++)
		{
			for (j = 3; j < 6; j++)
			{
				if (sudoku[i][j] == valor)
					return true;
			}
		}
		break;

	case 3:
		for (i = 0; i < 3; i++)
		{
			for (j = 6; j < 9; j++)
			{
				if (sudoku[i][j] == valor)
					return true;
			}
		}
		break;

	case 4:
		for (i = 3; i < 6; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (sudoku[i][j] == valor)
					return true;
			}
		}
		break;

	case 5:
		for (i = 3; i < 6; i++)
		{
			for (j = 3; j < 6; j++)
			{
				if (sudoku[i][j] == valor)
					return true;
			}
		}
		break;

	case 6:
		for (i = 3; i < 6; i++)
		{
			for (j = 6; j < 9; j++)
			{
				if (sudoku[i][j] == valor)
					return true;
			}
		}
		break;

	case 7:
		for (i = 6; i < 9; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (sudoku[i][j] == valor)
					return true;
			}
		}
		break;

	case (8):
		for (i = 6; i < 9; i++)
		{
			for (j = 3; j < 6; j++)
			{
				if (sudoku[i][j] == valor)
					return true;
			}
		}
		break;

	case 9:
		for (i = 6; i < 9; i++)
		{
			for (j = 6; j < 9; j++)
			{
				if (sudoku[i][j] == valor)
					return true;
			}
		}
		break;
	}

	for (i = 0; i < 9; i++)
	{
		if (sudoku[i][coluna] == valor || sudoku[linha][i] == valor)//verifica conflito em relação à linhas e colunas da posição selecionada
			return true;
	}

	return false;
}

//função que determina as posições e valores dos elementos pertencentes a formação inicial do sudoku
void iniciaSudoku(int sudoku[9][9])
{
	int controleNum[18], controleLinhas[18], controleColunas[18];//verificadores para criar sudoku inicial
	int i, j, k, aux;

	//limpar variáveis
	limpaVariaveis(sudoku, controleNum, controleLinhas, controleColunas);

	//definição da função rand
	srand(time(NULL));

	//definindo índices iniciais de linha e colunas
	for (k = 0; k < 18; k++)
	{
		i = rand() % 18;
		j = rand() % 18;
		aux = rand() % 18;

		while (controleLinhas[i] != 0)//preenche vetor de índices de linhas para os valores iniciais 
		{
			i++;
			i %= 18;
		}
		controleLinhas[i] = k % 9;
		
		while (controleColunas[j] != 0)//preenche vetor de índices de colunas para os valores iniciais
		{
			j++;
			j %= 18;
		}
		controleColunas[j] = k % 9;
		
		while (controleNum[aux] != 0)//preenche vetor de valores iniciais
		{
			aux++;
			aux %= 18;
		}
		controleNum[aux] = k % 9 + 1;
	}

	for(k = 0; k < 17; k++)
	{
		//posição (i, j) e valor do elemento k
		i = controleLinhas[k];
		j = controleColunas[k];
		aux = controleNum[k];

		sudoku[i][j] = aux;//insere valor no sudoku
	}
}

//função que exibe a disposição do sudoku na tela
void imprimeSudoku(int sudoku[9][9])
{
	int i, j;
	
	printf("\n\t\t\t");//pula linha + 3 tabulações

	for (i = 0; i < 9; i++)//varia a linha
	{
		for (j = 0; j < 9; j++)//varia a coluna
		{
			if (sudoku[i][j] != 0)//O valor 0 representa a posição vazia
			{
				printf(" %3d ", sudoku[i][j]);//imprime o valor da posição (i, j) com espaço para 3 números
			}
			else
			{
				printf("  -  ");//imprime "-" se o valor não estiver no intervalo [1..9]
			}
		}
		printf("\n\t\t\t");//pula linha + 3 tabulações
	}

	printf("\n");
}

//algoritmo guloso -> pode deixar espaços vazios, pois não garante solução ótima
void gulosoSudoku(int sudoku[9][9])
{
	int i, j, k;
	int count = 0;

	for (i = 0; i < 9; i++)//passa por cada linha do sudoku 9 x 9
	{
		for (j = 0; j < 9; j++)//passa por cada coluna do sudoku 9 x 9
		{
			for (k = 1; k < 10; k++)//varia os valores de inserção de 1 à 9
			{
				if (sudoku[i][j] != 0)//a posição (i, j) do sudoku já está ocupada
				{
					printf("A posicao (%d, %d) ja esta preenchida\n\n", i + 1, j + 1);
					break;//pula para a próxima posição
				}

				if (!verificaConflito(sudoku, i, j, k))//se não há conflito entre o valor atual e sua linha, coluna e quadro correspondente, o valor é inserido no sudoku
				{
					printf("O valor %d foi inserido na posicao %d %d\n\n", k, i + 1, j + 1);
					sudoku[i][j] = k;
					count++;//conta a quantidade de elementos inseridos na formação inicial
				}
				else
					printf("O valor %d conflita com linha %d ou coluna %d ou quadro\n", k, i + 1, j + 1);//há conflito com linha, coluna ou quadro correspondente a posição examinada
			}
		}
	}

	printf("\nFicaram %d espacos vazios\n", 64 - count);//81 espaços totais - 17 espaços iniciais - n espaços preenchidos = espaços vazios

}

int main()
{    
	int sudoku[9][9];//matriz do jogo

	iniciaSudoku(sudoku);

	imprimeSudoku(sudoku);

	gulosoSudoku(sudoku);

	imprimeSudoku(sudoku);

	system("pause");
	return 0;
}
