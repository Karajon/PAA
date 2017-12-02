// SUDOKU PAA.cpp: Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"
#include <stdlib.h>

//protótipos
void iniciaMatrizNum(int[9][9], int[9][9][9]);
void atualizaMatrizNum(int[9][9], int[9][9][9], int, int);

//estratégia gulosa
/*
1 - gerar disposição inicial do sudoku
2 - gerar matriz para cada número, que mostra onde são possíveis inserções
2.1 - marcar em todas as matrizes os valores iniciais
-> percorrer o sudoku e se estiver preenchido, marcar em cada matriz
2.2 - marcar as linhas, colunas e quadros que não será mais possível inserir o número após uma inserção
-> marcar os elementos da linha correspondente
-> marcar os elementos da coluna correspondente
-> marcar os elementos do quadro correspondente
3 - marcar mais posições que não é posível inserir um número

-> se uma linha tiver apenas uma posição com possibilidade de inserção
-> se uma coluna tiver apenas uma posição com possibilidade de inserção
-> se um quadro tiver apenas uma posição com possibilidade de inserção

-> se apenas a linha de determinado quadro tiver posições vazias, as outras linhas desse quadro são marcadas
-> se apenas a coluna de determinado quadro tiver posições vazias, as outras colunas desse quadro são marcadas

-> se apenas uma das linhas de um quadro estiver vazia, marcar os quadros vizinho nesta linha
-> se apenas uma das colunas de um quadro estiver vazia, marcar os quadros vizinhos nesta coluna

*/
void deslocamentoQ1(int linha, int coluna, int *iDeslocamento, int *jDeslocamento)
{
	*iDeslocamento = linha;
	*iDeslocamento -= linha % 3;

	*jDeslocamento = coluna;
	*jDeslocamento -= coluna % 3;
}

void anda(int *indice, int inicio, int fim)
{
	if (*indice == fim)
		*indice = inicio;
	else
		*indice += 1;
}

void andaQuadro(int *indiceLinha, int *indiceColuna)
{
	if (*indiceColuna == 2)
		anda(indiceLinha, 0, 2);

	anda(indiceColuna, 0, 2);
}

void limpaD2(int matriz[9][9])
{
	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
			matriz[i][j] = 0;
	}
}

void limpaD3(int matrizNum[9][9][9])
{
	int i, j, k;

	for (k = 0; k < 9; k++)
	{
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				matrizNum[k][i][j] = 0;
			}
		}
	}
}

void imprimeD2(int matriz[9][9])
{
	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (matriz[i][j] == 0)
				printf(" - ");
			else
				printf(" %d ", matriz[i][j]);
		}
		printf("\n");
	}
}

void imprimeD3(int matriz[9][9][9])
{
	int i, j, k;

	for (k = 0; k < 9; k++)
	{
		printf("\n%d\n\n", k + 1);

		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (matriz[k][i][j] == 0)
					printf(" - ");
				else
					printf(" %d ", matriz[k][i][j]);
			}
			printf("\n");
		}
	}
	printf("\n\n");
}

void iniciaSudoku(int sudoku[9][9], int matrizNum[9][9][9])
{
	limpaD2(sudoku);

	//1
	sudoku[0][0] = 2;
	//2
	sudoku[0][1] = 8;
	//3
	sudoku[0][4] = 4;
	//4
	sudoku[1][7] = 3;
	//5
	sudoku[1][8] = 1;
	//6
	sudoku[2][7] = 6;
	//7
	sudoku[3][0] = 7;
	//8
	sudoku[3][3] = 2;
	//9
	sudoku[3][6] = 8;
	//10
	sudoku[4][1] = 3;
	//11
	sudoku[4][3] = 1;
	//12
	sudoku[5][3] = 6;
	//13
	sudoku[5][5] = 8;
	//14
	sudoku[6][4] = 7;
	//15
	sudoku[6][6] = 5;
	//16
	sudoku[7][2] = 1;
	//17
	sudoku[8][0] = 4;

	iniciaMatrizNum(sudoku, matrizNum);
	imprimeD2(sudoku);
}

void iniciaMatrizNum(int sudoku[9][9], int matrizNum[9][9][9])
{
	int i, j, k;

	limpaD3(matrizNum);

	for (k = 0; k < 9; k++)
	{
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (sudoku[i][j] != 0)
					atualizaMatrizNum(sudoku, matrizNum, i, j);
			}
		}
	}

	imprimeD3(matrizNum);
}

void atualizaMatrizNumLinhaColuna(int sudoku[9][9], int matrizNum[9][9][9], int linha, int coluna)
{
	int k;

	int indiceLinha, indiceColuna, indiceNum;

	indiceLinha = linha;
	indiceColuna = coluna;
	indiceNum = sudoku[linha][coluna] - 1;

	for (k = 0; k < 8; k++)//há 8 posições para percorrer exceto a própria
	{
		anda(&indiceLinha, 0, 8);
		anda(&indiceColuna, 0, 8);
		matrizNum[indiceNum][linha][indiceColuna] = 1;
		matrizNum[indiceNum][indiceLinha][coluna] = 1;
	}
}

void atualizaMatrizNumQuadro(int sudoku[9][9], int matrizNum[9][9][9], int linha, int coluna)
{
	int linhaQuadro, colunaQuadro, iDeslocamento, jDeslocalmento, indice, k;

	indice = sudoku[linha][coluna] - 1;

	linhaQuadro = linha % 3;
	colunaQuadro = coluna % 3;

	deslocamentoQ1(linha, coluna, &iDeslocamento, &jDeslocalmento);

	for (k = 0; k < 8; k++)
	{
		andaQuadro(&linhaQuadro, &colunaQuadro);
		matrizNum[indice][linhaQuadro + iDeslocamento][colunaQuadro + jDeslocalmento] = 1;
	}
}

void atualizaMatrizNum(int sudoku[9][9], int matrizNum[9][9][9], int linha, int coluna)
{
	int k;

	for (k = 0; k < 9; k++)
	{
		matrizNum[k][linha][coluna] = 1;//marca na matriz de cada número que um elemento foi inserido ali
	}

	atualizaMatrizNumLinhaColuna(sudoku, matrizNum, linha, coluna);//marca o quadro na matriz do número inserido
	atualizaMatrizNumQuadro(sudoku, matrizNum, linha, coluna);//marca o quadro na matriz do número inserido
}

void atualizaVazioLinhaColuna(int matrizNum[9][9][9], int sudoku[9][9], int linha, int coluna, int vazioLinha[9][9], int vazioColuna[9][9])
{
	int k;

	int indiceLinha, indiceColuna, indiceNum, contColuna = 0, contLinha = 0;

	indiceLinha = linha;
	indiceColuna = coluna;
	//indiceNum = sudoku[linha][coluna] - 1;

	for (indiceNum = 0; indiceNum < 9; indiceNum++)
	{
		contLinha = 0;
		contColuna = 0;

		for (k = 0; k < 9; k++)
		{
			anda(&indiceLinha, 0, 8);
			anda(&indiceColuna, 0, 8);
			if (matrizNum[indiceNum][linha][indiceColuna] == 0)//varre a linha
				contLinha++;
			if (matrizNum[indiceNum][indiceLinha][coluna] == 0)//varre a coluna
				contColuna++;
		}

		//if (contColuna == 1)
		vazioColuna[indiceNum][coluna] = contColuna;
		//printf("vazioColuna[%d][%d] = %d\n", indiceNum, coluna, contColuna);//printf para visualização e teste

		//if (contLinha == 1)
		vazioLinha[indiceNum][linha] = contLinha;
		printf("vazioLinha[%d][%d] = %d\n", indiceNum + 1, linha, contLinha);//printf para visualização e teste
	}
}

void deslocamentoDeterminaQuadro(int iDeslocamento, int jDeslocamento, int *quadro)
{
	//determina coluna de quadro através dos jDeslocamentos
	if (jDeslocamento == 0)
		*quadro = 1;

	if (jDeslocamento == 3)
		*quadro = 2;

	if (jDeslocamento == 6)
		*quadro = 3;

	//determina linha de quadro através dos iDeslocamentos
	if (iDeslocamento == 3)
		*quadro += 3;

	if (iDeslocamento == 6)
		*quadro += 6;
}

void atualizaVazioQuadro(int matrizNum[9][9][9], int sudoku[9][9], int linha, int coluna, int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	int linhaQuadro, colunaQuadro, iDeslocamento, jDeslocamento, indice, k, count = 0, quadro, linhaAux, colunaAux;
	//quadros vizinhos
	int iDeslocamentoA, jDeslocamentoA;
	int iDeslocamentoB, jDeslocamentoB;
	int iDeslocamentoC, jDeslocamentoC;
	int iDeslocamentoD, jDeslocamentoD;
	int iAux, jAux;
	int countA, countB, countC, countD;
	int quadroA, quadroB, quadroC, quadroD;

	//indice = sudoku[linha][coluna] - 1;
	linhaQuadro = linha % 3;
	colunaQuadro = coluna % 3;
	linhaAux = linha % 3;
	colunaAux = coluna % 3;
	//auxiliares de posição para encontrar deslocamento dos quadros vizinhos
	iAux = linha;
	jAux = coluna;

	deslocamentoQ1(linha, coluna, &iDeslocamento, &jDeslocamento);
	//deslocamentos dos quadros vizinhos
	anda(&jAux, 0, 8);
	anda(&jAux, 0, 8);
	anda(&jAux, 0, 8);
	//desloca para quadro à direita
	deslocamentoQ1(iAux, jAux, &iDeslocamentoA, &jDeslocamentoA);
	anda(&jAux, 0, 8);
	anda(&jAux, 0, 8);
	anda(&jAux, 0, 8);
	//desloca para quadro à direita novamente
	deslocamentoQ1(iAux, jAux, &iDeslocamentoB, &jDeslocamentoB);
	anda(&jAux, 0, 8);
	anda(&jAux, 0, 8);
	anda(&jAux, 0, 8);
	//desloca para quadro à direita mais uma vez, retornando à posição original
	anda(&iAux, 0, 8);
	anda(&iAux, 0, 8);
	anda(&iAux, 0, 8);
	//desloca para quadro abaixo
	deslocamentoQ1(iAux, jAux, &iDeslocamentoC, &jDeslocamentoC);
	anda(&iAux, 0, 8);
	anda(&iAux, 0, 8);
	anda(&iAux, 0, 8);
	//desloca para quadro abaixo novamente
	deslocamentoQ1(iAux, jAux, &iDeslocamentoD, &jDeslocamentoD);

	deslocamentoDeterminaQuadro(iDeslocamento, jDeslocamento, &quadro);
	//quadros vizinhos
	deslocamentoDeterminaQuadro(iDeslocamentoA, jDeslocamentoA, &quadroA);
	deslocamentoDeterminaQuadro(iDeslocamentoB, jDeslocamentoB, &quadroB);
	deslocamentoDeterminaQuadro(iDeslocamentoC, jDeslocamentoC, &quadroC);
	deslocamentoDeterminaQuadro(iDeslocamentoD, jDeslocamentoD, &quadroD);

	//prints para visualização e testes
	//printf("atualizaVazioQuadro [%d,%d] -> q:%d\n", linha, coluna, quadro);

	for (indice = 0; indice < 9; indice++)//varia os números em relação à matrizNum
	{
		count = 0;
		//quadros vizinhos
		countA = 0;
		countB = 0;
		countC = 0;
		countD = 0;

		for (k = 0; k < 9; k++)
		{
			andaQuadro(&linhaQuadro, &colunaQuadro);

			if (matrizNum[indice][linhaQuadro + iDeslocamento][colunaQuadro + jDeslocamento] == 0)
				count++;

			//quadro vizinhos
			//usa o mesmo andaQuadro, com deslocamentos diferentes
			if (matrizNum[indice][linhaQuadro + iDeslocamentoA][colunaQuadro + jDeslocamentoA] == 0)
				countA++;
			if (matrizNum[indice][linhaQuadro + iDeslocamentoB][colunaQuadro + jDeslocamentoB] == 0)
				countB++;
			if (matrizNum[indice][linhaQuadro + iDeslocamentoC][colunaQuadro + jDeslocamentoC] == 0)
				countC++;
			if (matrizNum[indice][linhaQuadro + iDeslocamentoD][colunaQuadro + jDeslocamentoD] == 0)
				countD++;
		}

		//varre a diagonal do quadro, para atualizar linhas e colunas que se relacionam ao quadro
		//atualizaVazioLinhaColuna(matrizNum, sudoku, (linhaAux + iDeslocamento), (colunaAux + jDeslocamento), vazioLinha, vazioColuna);
		/*anda(&linhaAux, 0, 2);
		anda(&colunaAux, 0, 2);
		atualizaVazioLinhaColuna(matrizNum, sudoku, (linhaAux + iDeslocamento), (colunaAux + jDeslocamento), vazioLinha, vazioColuna);
		anda(&linhaAux, 0, 2);
		anda(&colunaAux, 0, 2);
		atualizaVazioLinhaColuna(matrizNum, sudoku, (linhaAux + iDeslocamento), (colunaAux + jDeslocamento), vazioLinha, vazioColuna);
		anda(&linhaAux, 0, 2);
		anda(&colunaAux, 0, 2);
		*/

		//if (count == 1)
		//printf("atualizaVazioQuadro vazioQuadro[%d][%d] = %d\n", indice, quadro, count);//printf para visualização e teste
		vazioQuadro[indice][quadro - 1] = count;
		//quadros vizinhos
		//printf("atualizaVazioQuadro vazioQuadroA[%d][%d] = %d\n", indice, quadroA, countA);//printf para visualização e teste
		//printf("atualizaVazioQuadro vazioQuadroB[%d][%d] = %d\n", indice, quadroB, countB);//printf para visualização e teste
		//printf("atualizaVazioQuadro vazioQuadroC[%d][%d] = %d\n", indice, quadroC, countC);//printf para visualização e teste
		//printf("atualizaVazioQuadro vazioQuadroD[%d][%d] = %d\n", indice, quadroD, countD);//printf para visualização e teste
		vazioQuadro[indice][quadroA - 1] = countA;
		vazioQuadro[indice][quadroB - 1] = countB;
		vazioQuadro[indice][quadroC - 1] = countC;
		vazioQuadro[indice][quadroD - 1] = countD;

	}

}

void iniciaVazio(int matrizNum[9][9][9], int sudoku[9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	int i = 0, j = 0, k;
	int a, b;

	for (a = 0; a < 9; a++)
	{
		for (b = 0; b < 9; b++)
		{
			vazioLinha[a][b] = 0;
			vazioColuna[a][b] = 0;
			vazioQuadro[a][b] = 0;
			//limpa as matrizes "vazio"
		}
	}

	for (k = 0; k < 9; k++)
	{
		atualizaVazioLinhaColuna(matrizNum, sudoku, k, k, vazioLinha, vazioColuna);
		atualizaVazioQuadro(matrizNum, sudoku, i * 3, j * 3, vazioLinha, vazioColuna, vazioQuadro);//percorre os 9 quadros
		andaQuadro(&i, &j);//o movimento de posições em um quadro 3 x 3 é transformado no movimento entre quadro ao se multiplicar os índices por 3
	}
}

void atualizaVazio(int matrizNum[9][9][9], int sudoku[9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9], int linha, int coluna)
{
	iniciaVazio(matrizNum, sudoku, vazioLinha, vazioColuna, vazioQuadro);
	//atualizaVazioQuadro(matrizNum, sudoku, linha, coluna, vazioLinha, vazioColuna, vazioQuadro);
	//atualizaVazioLinhaColuna(matrizNum, sudoku, linha, coluna, vazioLinha, vazioColuna);
}

void insere(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9], int linha, int coluna, int valor)
{
	sudoku[linha][coluna] = valor;
	printf("insere sudoku[%d,%d] <- %d\n", linha, coluna, valor);//printf para visualização e teste
	atualizaMatrizNum(sudoku, matrizNum, linha, coluna);
	atualizaVazio(matrizNum, sudoku, vazioLinha, vazioColuna, vazioQuadro, linha, coluna);
}

void vazioInsereLinha(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9], int numero)
{
	int i, coluna;

	for (i = 0; i < 9; i++)
	{
		//printf("vazioLinha[%d][%d]:%d\n", numero, i, vazioLinha[numero][i]);//para visualização e teste

		if (vazioLinha[numero][i] == 1)//encontrou a única posição vazia
		{
			coluna = 0;
			while (matrizNum[numero][i][coluna] != 0)
				coluna++;

			printf("vazioInsereLinha sudoku[%d, %d] <= %d\n", i, coluna, (numero + 1));//para visualização e teste
			insere(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, i, coluna, (numero + 1));
		}
	}
}

void vazioInsereColuna(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9], int numero)
{
	int i, linha;

	for (i = 0; i < 9; i++)
	{
		if (vazioColuna[numero][i] == 1)//encontrou a única posição vazia
		{
			linha = 0;
			while (matrizNum[numero][i][linha] != 0 && linha < 9)
				linha++;

			printf("vazioInsereColuna sudoku[%d, %d] <= %d\n", linha, i, (numero + 1));//para visualização e teste
			insere(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, linha, i, (numero + 1));
		}
	}
}

void vazioInsereQuadro(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9], int numero)
{
	int q, k, linha, coluna, linhaInicioQuadro = 0, colunaInicioQuadro = 0, auxLinha, auxColuna;

	for (q = 0; q < 9; q++)
	{
		if (vazioQuadro[numero][q] == 1)//encontrou a única posição vazia
		{
			linha = 3 * linhaInicioQuadro;
			coluna = 3 * colunaInicioQuadro;
			auxLinha = 0;
			auxColuna = 0;

			k = 0;
			while (matrizNum[numero][linha + auxLinha][coluna + auxColuna] != 0 && k < 9)
			{
				printf("....... q(%d, %d) -> [%d, %d]\n", linhaInicioQuadro, colunaInicioQuadro, linha + auxLinha, coluna + auxColuna);//printf para visualização e teste
				andaQuadro(&auxLinha, &auxColuna);
				k++;
			}

			printf("vazioInsereQuadro sudoku[%d, %d] <= %d\n", linha + auxLinha, coluna + auxColuna, (numero + 1));//para visualização e teste
			insere(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, linha + auxLinha, coluna + auxColuna, (numero + 1));
		}
		andaQuadro(&linhaInicioQuadro, &colunaInicioQuadro);//o movimento de posições em um quadro 3 x 3 é transformado no movimento entre quadro ao se multiplicar os índices por 3
	}
}

int vazioL(int vazioLinha[9][9])
{
	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (vazioLinha[i][j] == 1)
				return true;
		}
	}
	return false;
}

int vazioC(int vazioColuna[9][9])
{
	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (vazioColuna[i][j] == 1)
				return true;
		}
	}
	return false;
}

int vazioQ(int vazioQuadro[9][9])
{
	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (vazioQuadro[i][j] == 1)
				return true;
		}
	}
	return false;
}

void vazioInsereTudoLinha(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	int numero;

	while (vazioL(vazioLinha))
	{
		for (numero = 0; numero < 9; numero++)
		{
			//vazioInsereQuadro(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
			vazioInsereLinha(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
			//vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
		}
	}
}

void vazioInsereTudoColuna(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	int numero;

	while (vazioC(vazioColuna))
	{
		for (numero = 0; numero < 9; numero++)
		{
			//vazioInsereQuadro(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
			//vazioInsereLinha(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
			vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
		}
	}
}

void vazioInsereTudoQuadro(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	int numero;

	while(vazioQ(vazioQuadro))
	{
		for (numero = 0; numero < 9; numero++)
		{
			vazioInsereQuadro(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
			//vazioInsereLinha(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
			//vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, numero);
		}
	}
}

void vazioInsereTudo(int sudoku[9][9], int matrizNum[9][9][9], int vazioLinha[9][9], int vazioColuna[9][9], int vazioQuadro[9][9])
{
	while (vazioQ(vazioQuadro) || vazioL(vazioLinha) || vazioC(vazioColuna))
	{
		vazioInsereTudoQuadro(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro);
		vazioInsereTudoLinha(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro);
		vazioInsereTudoColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro);
	}
}

/*
//void quadroEspecialLinha()
//void quadroEspecialColuna()

//void linhaEspecialQuadro()
//void colunaEspecialQuadro()

*/



int main()
{
	int sudoku[9][9], matrizNum[9][9][9], vazioLinha[9][9], vazioColuna[9][9], vazioQuadro[9][9];

	/*int linha = 0, coluna = 0 , i;
	
	for (i = 0; i < 9; i++)
	{
		printf("linha:%d coluna:%d\n", linha, coluna);
		andaQuadro(&linha, &coluna);
	}

	int quadro = 0, i, j;

	i = 3;
	j = 6;

	deslocamentoDeterminaQuadro(i, j, &quadro);
	printf("quadro:%d\n", quadro);
	*/

	iniciaSudoku(sudoku, matrizNum);

	iniciaVazio(matrizNum, sudoku, vazioLinha, vazioColuna, vazioQuadro);//inicia e nesse contexto atualiza

	printf("vazioLinha\n");
	imprimeD2(vazioLinha);

	printf("vazioColuna\n");
	imprimeD2(vazioColuna);

	printf("vazioQuadro\n");
	imprimeD2(vazioQuadro);

	//insere(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, 7, 1, 3);
	//insere(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, 2, 1, 4);

	printf("\nSudoku\n");
	imprimeD2(sudoku);
	
	printf("---------------------------------------\n");

	vazioInsereTudo(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro);
	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>1<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	
	printf("vazioColuna\n");
	imprimeD2(vazioColuna); 
	printf("MatrizNum\n");
	imprimeD3(matrizNum);


	vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, 1);
	/*printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>2<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, 2);
	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>3<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, 3);
	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>4<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, 4);
	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>5<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, 5);
	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>6<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, 6);
	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>7<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, 7);
	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>8<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	vazioInsereColuna(sudoku, matrizNum, vazioLinha, vazioColuna, vazioQuadro, 8);
	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>9<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	*/

	printf("MatrizNum\n");
	imprimeD3(matrizNum);
	
	printf("vazioQuadro\n");
	imprimeD2(vazioQuadro);

	printf("vazioLinha\n");
	imprimeD2(vazioLinha);

	printf("vazioColuna\n");
	imprimeD2(vazioColuna);

	
	printf("\nSudoku\n");
	imprimeD2(sudoku);

	printf("vazioQuadro\n");
	imprimeD2(vazioQuadro);

	printf("vazioLinha\n");
	imprimeD2(vazioLinha);


	printf("vazioColuna\n");
	imprimeD2(vazioColuna);



	system("pause");
	return 0;
}


