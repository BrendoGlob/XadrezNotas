/*JOGO DE XADREZ*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <windows.h>
#include <dos.h>
#include <dir.h>


int Board[8][8] = 
/*ESTE TABULEIRO EST? REPRESENTADO POR N?MEROS (8?8).
?NUMEROS PARES(BRANCAS), NUMEROS ?MPARES(PRETAS).
10(pe?o) 20(bispo) 30(cavalo) 40(torre) 50(rainha) 60(rei)*/
{
 41, 31, 21, 51, 61, 21, 31, 41,
 11, 11, 11, 11, 11, 11, 11, 11,
 00, 00, 00, 00, 00, 00, 00, 00,
 00, 00, 00, 00, 00, 00, 00, 00,
 00, 00, 00, 00, 00, 00, 00, 00,
 00, 00, 00, 00, 00, 00, 00, 00,
 10, 10, 10, 10, 10, 10, 10, 10,
 40, 30, 20, 50, 60, 20, 30, 40,
};

//FUN??ES:
void PrintBoard( void );//Imprime o Tabuleiro para o jogador.
void SelectPiece( int vez, bool &RokB1, bool &RokP1, bool &RokB2, bool &RokP2, int &DePassagemL, int &DePassagemC );//Seleciona e move uma pe?a.
void BoardClean ( void );//Limpa Tabuleiro(amea?a das pe?as representada por outros n?meros).
//FUN??ES!

int main()
{
	int vez = 0;
	bool RokeBranco1, RokePreto1, RokeBranco2, RokePreto2;
	int el_passantL, el_passantC;
	while(1)
	{
		PrintBoard();
		SelectPiece( vez, RokeBranco1, RokePreto1, RokeBranco2, RokePreto2, el_passantL, el_passantC );
		if (vez == 0) vez = 1; else vez = 0;
	}
	return 0;
}

//CORPOS DAS FUN??ES:
void PrintBoard( void )
{
	system("color F0");
	printf("\n*| 1 2 3 4 5 6 7 8|*\n--------------------\n");
	for(int ver=0; ver<8; ver++)
	{
		printf("%d|", 8-ver);
		for(int hor=0; hor<8; hor++)
		{
			switch( Board[ver][hor] )
			{
				case 2: printf(" X"); break;//Sele??o Branca.
				case 3: printf(" X"); break;//Sele??o Preta.
				
				case 10: printf(" P"); break;//Pe?o Branco.
				case 11: printf(" p"); break;//Pe?o Preto.
				case 20: printf(" B"); break;//Bispo Branco.
				case 21: printf(" b"); break;//Bispo Preto.
				case 30: printf(" C"); break;//Cavalo Branco.
				case 31: printf(" c"); break;//Cavalo Preto.
				case 40: printf(" T"); break;//Torre Branca.
				case 41: printf(" t"); break;//Torre Preta.
				case 50: printf(" R"); break;//Rainha Branca.
				case 51: printf(" r"); break;//Rainha Preta.
				case 60: printf(" K"); break;//Rei Branco.
				case 61: printf(" k"); break;//Rei Preto.

				case 12: printf(" X"); break;//Pe?o Branco Amea?ado.
				case 13: printf(" X"); break;//Pe?o Preto Amea?ado.
				case 22: printf(" X"); break;//Bispo Branco Amea?ado.
				case 23: printf(" X"); break;//Bispo Preto Amea?ado.
				case 32: printf(" X"); break;//Cavalo Branco Amea?ado.
				case 33: printf(" X"); break;//Cavalo Preto Amea?ado.
				case 42: printf(" X"); break;//Torre Branca Amea?ada.
				case 43: printf(" X"); break;//Torre Preta Amea?ada.
				case 52: printf(" X"); break;//Rainha Branca Amea?ada.
				case 53: printf(" X"); break;//Rainha Preta Amea?ada.
				case 62: printf(" X"); break;//Rei Branco Amea?ado.
				case 63: printf(" X"); break;//Rei Preto Amea?ado.

				default: if ((ver+hor) % 2 ==0) printf(" -"); else printf(" -"); break;//Case Vazia.
			}
		}
		printf("|%d\n", 8-ver);
	}
	printf("--------------------\n*| 1 2 3 4 5 6 7 8|*\n");
}

void SelectPiece( int vez, bool &RokB1, bool &RokP1, bool &RokB2, bool &RokP2, int &DePassagemL, int &DePassagemC )
{
		/***********************************
	?Selecionar a pe?a para mov?-la?
	??Mover a Pe?a para a nova posi??o??
	***********************************/

	int linha=0, coluna=0, DestLinha=0, DestColuna=0, peca, hor, ver, i, j, reibranco, reipreto;
	
	PONTO1:
	//?Selecionar uma pe?a:
	do
	{
	reibranco = 1;
	reipreto = 1;
	if (linha>=0 || linha<=0)
	{
		for (i=0; i<=8; i++)
		{
			for
		 	(j=0; j<=8; j++)
			{
				if (Board[i][j]==60)
				{
					reibranco = 0;
				}
				if (Board[i][j]==61)
				{
					reipreto = 0;
				}
			}
		}
	}
	if (reibranco==1)
	{
		printf("\nXeque Mate! Vit?ria das pretas\n\n");
		exit(0);
	}
	if (reipreto==1)
	{
		printf("\nXeque Mate! Vit?ria das brancas\n\n");
		exit(0);
	}
		
		setlocale(LC_ALL, "Portuguese");
		printf("\nDigite qual pe?a deseja mover: \n");
		printf("Linha : ");
		scanf("%d", &linha);
		printf("Coluna: ");
		scanf("%d", &coluna);
		system("cls");
		
		//Checa se a casa selecionada ? v?lida:
		if((linha<1 || linha >8)||(coluna<1 || coluna>8))
		{
			PrintBoard();
			setlocale(LC_ALL, "Portuguese");
			printf("\nVoc? digitou errado!Tente novamente!\n");
		}
		else
		//Checa se a casa selecionada est? vazia:
		if (Board[8-linha][coluna-1] == 0)
		{
			PrintBoard();
			setlocale(LC_ALL, "Portuguese");
			printf("\nVoc? selecionou uma casa vazia!Selecione uma pe?a!\n");
			linha = 0, coluna = 0;//?isso far? o la?o repetir!
		}
		else
		//Checa se ? a vez das brancas uma pe?a branca deve ser selecionada e vice versa:
		if (((Board[8-linha][coluna-1] % 2 == 0)&&(vez == 1))||((Board[8-linha][coluna-1] % 2 != 0)&&(vez == 0)))
		{
			PrintBoard();
			setlocale(LC_ALL, "Portuguese");
			printf("\nVoc? n?o pode selecionar uma pe?a do oponente!Seleciona as suas!\n");
			linha = 0, coluna = 0;//?isso far? o la?o repetir!
		}
	}while ((linha<1 || linha >8)||(coluna<1 || coluna>8));

	linha = 8-linha;//se digitado 1, dever? ser acessado 0 em "Board[0][].
	coluna -= 1;//se digitado 1, dever? ser acessado 0 em "Board[][0].

	//Nesses ifis? seleciona a pe?a e mostra seus possiveis destinos:

	if (Board[linha][coluna] == 10)//Pe?o Branco:
	{
		if (Board[linha-1][coluna] == 0)
		{
			Board[linha-1][coluna] = 2;
			if ((Board[linha-2][coluna] == 0)&&(linha == 6))
			Board[linha-2][coluna] = 2;
		}
		if ((linha<7)&&(coluna<7)) if ((Board[linha-1][coluna+1] % 2 !=0)&&(Board[linha-1][coluna+1] > 2)) Board[linha-1][coluna+1] += 2;
		if ((linha<7)&&(coluna>0)) if ((Board[linha-1][coluna-1] % 2 !=0)&&(Board[linha-1][coluna-1] > 2)) Board[linha-1][coluna-1] += 2;

		if((linha-1 == DePassagemL)&&(coluna+1 == DePassagemC)) Board[linha-1][coluna+1] = 2;
		if((linha-1 == DePassagemL)&&(coluna-1 == DePassagemC)) Board[linha-1][coluna-1] = 2;

		peca = Board[linha][coluna];
	}

	if (Board[linha][coluna] == 11)//Pe?o Preto:
	{
		if (Board[linha+1][coluna] == 0)
		{
			Board[linha+1][coluna] = 3;
			if ((Board[linha+2][coluna] == 0)&&(linha == 1))
			Board[linha+2][coluna] = 3;
		}
		if ((linha<7)&&(coluna<7)) if ((Board[linha+1][coluna+1] % 2 ==0)&&(Board[linha+1][coluna+1] > 3)) Board[linha+1][coluna+1] += 2;
		if ((linha<7)&&(coluna>0)) if ((Board[linha+1][coluna-1] % 2 ==0)&&(Board[linha+1][coluna-1] > 3)) Board[linha+1][coluna-1] += 2;

		if((linha+1 == DePassagemL)&&(coluna+1 == DePassagemC)) Board[linha+1][coluna+1] = 3;
		if((linha+1 == DePassagemL)&&(coluna-1 == DePassagemC)) Board[linha+1][coluna-1] = 3;

		peca = Board[linha][coluna];
	}

	if ((Board[linha][coluna] == 20+vez)||(Board[linha][coluna] == 50+vez))//Bispo e Rainha Branca e Preta:
	{
		hor = coluna;//Cima Esquerda
		for(ver = linha-1;ver>-1;ver--)
		{
			if (hor == 0) break;
			hor--;
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
			 if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
			 if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		hor = coluna;//Cima Direita
		for(ver = linha-1;ver>-1;ver--)
		{
			if (hor == 7) break;
			hor++;
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		hor = coluna;//Baixo Esquerda
		for(ver = linha+1;ver<8;ver++)
		{
			if (hor == 0) break;
			hor--;
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		hor = coluna;//Baixo Direita
		for(ver = linha+1;ver<8;ver++)
		{
			if (hor == 7) break;
			hor++;
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		peca = Board[linha][coluna];
	}

	if ((Board[linha][coluna] == 40+vez)||(Board[linha][coluna] == 50+vez))//Torres ou Rainha Brancas e Pretas:
	{
		hor = coluna;//Cima:
		for(ver = linha-1;ver>-1;ver--)
		{
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		hor = coluna;//Baixo
		for(ver = linha+1;ver<8;ver++)
		{
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		ver = linha;//Esquerda:
		for(hor = coluna-1;hor>-1;hor--)
		{
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		ver = linha;//Direita:
		for(hor = coluna+1;hor<8;hor++)
		{
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		peca = Board[linha][coluna];
	}

	if (Board[linha][coluna] == 30+vez)//Cavalo Branco e Preto.
	{
		//Cima esquerda:
		if ((linha > 1)&&(coluna > 0))
		{
			if (Board[linha-2][coluna-1] == 0) Board[linha-2][coluna-1] = 2+vez;
			if ((Board[linha-2][coluna-1] % 2 !=0)&&(vez == 0)) Board[linha-2][coluna-1] += 2;
			if ((Board[linha-2][coluna-1] % 2 ==0)&&(vez == 1)) Board[linha-2][coluna-1] += 2;
		}

		//Cima direita:
		if ((linha > 1)&&(coluna < 7))
		{
			if (Board[linha-2][coluna+1] == 0) Board[linha-2][coluna+1] = 2+vez;
			if ((Board[linha-2][coluna+1] % 2 !=0)&&(vez == 0)) Board[linha-2][coluna+1] += 2;
			if ((Board[linha-2][coluna+1] % 2 ==0)&&(vez == 1)) Board[linha-2][coluna+1] += 2;
		}

		//Baixo direita:
		if ((linha < 6)&&(coluna < 7))
		{
			if (Board[linha+2][coluna+1] == 0) Board[linha+2][coluna+1] = 2+vez;
			if ((Board[linha+2][coluna+1] % 2 !=0)&&(vez == 0)) Board[linha+2][coluna+1] += 2;
			if ((Board[linha+2][coluna+1] % 2 ==0)&&(vez == 1)) Board[linha+2][coluna+1] += 2;
		}

		//Baixo esquerda:
		if ((linha < 6)&&(coluna > 0))
		{
			if (Board[linha+2][coluna-1] == 0) Board[linha+2][coluna-1] = 2+vez;
			if ((Board[linha+2][coluna-1] % 2 !=0)&&(vez == 0)) Board[linha-2][coluna+1] += 2;
			if ((Board[linha+2][coluna-1] % 2 ==0)&&(vez == 1)) Board[linha-2][coluna+1] += 2;
		}

		//Esquerda cima:
		if ((linha > 0)&&(coluna > 1))
		{
			if (Board[linha-1][coluna-2] == 0) Board[linha-1][coluna-2] = 2+vez;
			if ((Board[linha-1][coluna-2] % 2 !=0)&&(vez == 0)) Board[linha-1][coluna-2] += 2;
			if ((Board[linha-1][coluna-2] % 2 ==0)&&(vez == 1)) Board[linha-1][coluna-2] += 2;
		}

		//Direita cima:
		if ((linha > 0)&&(coluna < 6))
		{
			if (Board[linha-1][coluna+2] == 0) Board[linha-1][coluna+2] = 2+vez;
			if ((Board[linha-1][coluna+2] % 2 !=0)&&(vez == 0)) Board[linha-1][coluna+2] += 2;
			if ((Board[linha-1][coluna+2] % 2 ==0)&&(vez == 1)) Board[linha-1][coluna+2] += 2;
		}

		//Esquerda baixo:
		if ((linha < 7)&&(coluna > 1))
		{
			if (Board[linha+1][coluna-2] == 0) Board[linha+1][coluna-2] = 2+vez;
			if ((Board[linha+1][coluna-2] % 2 !=0)&&(vez == 0)) Board[linha+1][coluna-2] += 2;
			if ((Board[linha+1][coluna-2] % 2 ==0)&&(vez == 1)) Board[linha+1][coluna-2] += 2;
		}

		//Direita baixo:
		if ((linha < 7)&&(coluna < 6))
		{
			if (Board[linha+1][coluna+2] == 0) Board[linha+1][coluna+2] = 2+vez;
			if ((Board[linha+1][coluna+2] % 2 !=0)&&(vez == 0)) Board[linha+1][coluna+2] += 2;
			if ((Board[linha+1][coluna+2] % 2 ==0)&&(vez == 1)) Board[linha+1][coluna+2] += 2;
		}

		peca = Board[linha][coluna];
	}

	if (Board[linha][coluna] == 60+vez)//Reis?:
	{
		//Casas vazias:
		if (Board[linha][coluna-1] == 0) Board[linha][coluna-1] = 2+vez;//Cima.
		if (Board[linha][coluna+1] == 0) Board[linha][coluna+1] = 2+vez;//Baixo.
		if (Board[linha-1][coluna] == 0) Board[linha-1][coluna] = 2+vez;//Esquerda.
		if (Board[linha+1][coluna] == 0) Board[linha+1][coluna] = 2+vez;//Direita.
		if (Board[linha-1][coluna-1] == 0) Board[linha-1][coluna-1] = 2+vez;//Diagonal cima esquerda.
		if (Board[linha+1][coluna-1] == 0) Board[linha+1][coluna-1] = 2+vez;//Diagonal cima direita.
		if (Board[linha+1][coluna+1] == 0) Board[linha+1][coluna+1] = 2+vez;//Diagonal baixo direita.
		if (Board[linha-1][coluna+1] == 0) Board[linha-1][coluna+1] = 2+vez;//Diagonal baixo esquerda.

		//Pe?as do aders?rio brancas:
		if ((Board[linha][coluna-1] %2 == 0)&&(vez == 1)) Board[linha][coluna-1] += 2;//Cima.
		if ((Board[linha][coluna+1] %2 == 0)&&(vez == 1)) Board[linha][coluna+1] += 2;//Baixo.
		if ((Board[linha-1][coluna] %2 == 0)&&(vez == 1)) Board[linha-1][coluna] += 2;//Esquerda.
		if ((Board[linha+1][coluna] %2 == 0)&&(vez == 1)) Board[linha+1][coluna] += 2;//Direita.
		if ((Board[linha-1][coluna-1] %2 == 0)&&(vez == 1)) Board[linha-1][coluna-1] += 2;//Diagonal cima esquerda.
		if ((Board[linha+1][coluna-1] %2 == 0)&&(vez == 1)) Board[linha+1][coluna-1] += 2;//Diagonal cima direita.
		if ((Board[linha+1][coluna+1] %2 == 0)&&(vez == 1)) Board[linha+1][coluna+1] += 2;//Diagonal baixo direita.
		if ((Board[linha-1][coluna+1] %2 == 0)&&(vez == 1)) Board[linha-1][coluna+1] += 2;//Diagonal baixo esquerda.

		//Pe?as do aders?rio pretas:
		if ((Board[linha][coluna-1] %2 != 0)&&(vez == 0)) Board[linha][coluna-1] += 2;//Cima.
		if ((Board[linha][coluna+1] %2 != 0)&&(vez == 0)) Board[linha][coluna+1] += 2;//Baixo.
		if ((Board[linha-1][coluna] %2 != 0)&&(vez == 0)) Board[linha-1][coluna] += 2;//Esquerda.
		if ((Board[linha+1][coluna] %2 != 0)&&(vez == 0)) Board[linha+1][coluna] += 2;//Direita.
		if ((Board[linha-1][coluna-1] %2 != 0)&&(vez == 0)) Board[linha-1][coluna-1] += 2;//Diagonal cima esquerda.
		if ((Board[linha+1][coluna-1] %2 != 0)&&(vez == 0)) Board[linha+1][coluna-1] += 2;//Diagonal cima direita.
		if ((Board[linha+1][coluna+1] %2 != 0)&&(vez == 0)) Board[linha+1][coluna+1] += 2;//Diagonal baixo direita.
		if ((Board[linha-1][coluna+1] %2 != 0)&&(vez == 0)) Board[linha-1][coluna+1] += 2;//Diagonal baixo esquerda.

		peca = Board[linha][coluna];

		if (vez == 0)//Roque:
		{
			if (RokB1 == 1)
			{ if ((Board[linha][coluna-2] == 0)&&(Board[linha][coluna-1] == 2+vez)) Board[linha][coluna-2] = 2+vez;/*Roque Esquerdo.*/ }
			if (RokB2 == 1)
			{ if ((Board[linha][coluna+2] == 0)&&(Board[linha][coluna+1] == 2+vez)) Board[linha][coluna+2] = 2+vez;/*Roque Direito.*/ }
		}
		if (vez == 1)
		{
			if (RokP1 == 1)
			{ if ((Board[linha][coluna-2] == 0)&&(Board[linha][coluna-1] == 2+vez)) Board[linha][coluna-2] = 2+vez;/*Roque Esquerdo.*/ }
			if (RokP2 == 1)
			{ if ((Board[linha][coluna+2] == 0)&&(Board[linha][coluna+1] == 2+vez)) Board[linha][coluna+2] = 2+vez;/*Roque Direito.*/ }
		}
	}//Reis?!

	PrintBoard();

	/***********************************
	?Selecionar a pe?a para mov?-la?
	?Mover a Pe?a para a nova posi??o?
	***********************************/

	do
	{
		setlocale(LC_ALL, "Portuguese");
		printf("\nDigite o local que deseja mover a pe?a? \n");
		printf("Linha : ");
		scanf("%d", &DestLinha);
		printf("Coluna: ");
		scanf("%d", &DestColuna);
		system("cls");

		//Checa se foi digitado um n?mero v?lido:
		if ((DestLinha<1 || DestLinha >8)||(DestColuna<1 || DestColuna>8))
		{
			setlocale(LC_ALL, "Portuguese");
			printf("\nVoc? digitou errado!Tente novamente!\n");
		}
		else
		//Checa se a casa selecionada est? vazia:
		if (Board[8-DestLinha][DestColuna-1] == 0)
		{
			setlocale(LC_ALL, "Portuguese");
			printf("\nVoc? selecionou uma casa inv?lida, selecione o 'X' ou uma outra pe?a!\n");
				linha = 0, coluna = 0, DestLinha = 0, DestColuna = 0, peca = 0;
				BoardClean();
				PrintBoard();
				goto PONTO1;
		}
		else
		//Checa se o jogador escolheu um local com uma pe?a aliada:
		for(int Blc = 6;Blc<67;Blc++)//Checa quais pe?as est?o amea?adas(14,15,24,25,34,35,44,45,46,47,54,55,56,57,64,65,66,67).
		{
			if (Blc % 2 ==0){ Blc += 8; }

			//Se a casa n?o estiver vazia, e n?o for uma casa selecionada para possivel jogada.
			if ((Board[8-DestLinha][DestColuna-1] >0)&&(Board[8-DestLinha][DestColuna-1] != 2+vez))
			//Se escolheu pe?a branca na vez das brancas, ou escolheu pe?a preta na vez das pretas:
			if (((Board[8-DestLinha][DestColuna-1] % 2 == 0)&&(vez == 0)) || ((Board[8-DestLinha][DestColuna-1] % 2 != 0)&&(vez == 1)))
			{
				setlocale(LC_ALL, "Portuguese");
				printf("\nVoc? n?o pode comer uma pe?a da sua 'cor'! Tente de novo ou selecione outra.\n");
				linha = 0, coluna = 0, DestLinha = 0, DestColuna = 0, peca = 0;
				BoardClean();
				PrintBoard();
				goto PONTO1;
			}
		}
	}while ((DestLinha<1 || DestLinha >8)||(DestColuna<1 || DestColuna>8));

	DestLinha = 8-DestLinha;//inverte os numeros ( 8 equivale a 0, 7 equivale a 1, 6 equivale a 2 ...)
	DestColuna -= 1;//se digitado 1, dever? ser acessado 0 em "Board[][0].

	//?Move a pe?a:
	if ((Board[DestLinha][DestColuna] == 2)||(Board[DestLinha][DestColuna] == 3))
	//Se uma casa selecionada:
	{
		Board[DestLinha][DestColuna] = peca;//Aloca a pe?a em seu destino.
		Board[linha][coluna] = 0;//Retira a pe?a de sua origem.
		if (( DestLinha == DePassagemL )&&( DestColuna == DePassagemC ))
		{
			if ( vez == 0)Board[DePassagemL+1][DePassagemC] = 0;
			if ( vez == 1)Board[DePassagemL-1][DePassagemC] = 0;
		}

		//Ativa a Jogada "El_passant" no Pe?o:
		if (( peca == 10 )&&(DestLinha == 4))
		{
			DePassagemL = DestLinha+1, DePassagemC = DestColuna;
		}
		else if (( peca == 11 )&&(DestLinha == 3))
		{
			DePassagemL = DestLinha-1, DePassagemC = DestColuna;
		}
		else{ DePassagemL = -1, DePassagemC = -1; }

	}//ou uma pe?a do oponente ? escolhida.
	else
	{
		for(int Blc = 4;Blc<64;Blc++)//Checa quais pe?as est?o amea?adas(12,13,22,23,32,33,42,43,42,43,52,53,62,63).
		{
			if (Blc % 2 == 0){ Blc += 8; }

			if (Board[DestLinha][DestColuna] == Blc)
			{
				Board[DestLinha][DestColuna] = peca;//Aloca a pe?a em seu destino.
				Board[linha][coluna] = 0;//Retira a pe?a de sua origem.
			}
		}
	}

	//Se um Rei ou uma Torre se moveu (Roques):
	if ((peca == 40+vez)||(peca == 60+vez))
	if(((RokB1 == 1)||(RokB2 == 1))||((RokP1 == 1)||(RokP2 == 1)))
	{
		if (peca == 60+vez)
		{
			if (peca %2 ==0)
			{
				if ((Board[7][2] == 60)&&(RokB1 == 1))
				{
					Board[7][0] = 0;
					Board[7][3] = 40;
				}
				if ((Board[7][6] == 60)&&(RokB2 == 1))
				{
					Board[7][7] = 0;
					Board[7][5] = 40;
				}
				RokB1 = 0, RokB2 = 0;
			}
			if (peca %2 !=0)
			{
				if ((Board[0][2] == 61)&&(RokP1 == 1))
				{
					Board[0][0] = 0;
					Board[0][3] = 41;
				}
				if ((Board[0][6] == 61)&&(RokP2 == 1))
				{
					Board[0][7] = 0;
					Board[0][5] = 41;
				}
				RokP1 = 0, RokP2 = 0;
			}
		}
		else
		{
			if (peca %2 == 0)
			{
				if (coluna == 7) RokB2 = 0;
				if (coluna == 0) RokB1 = 0;
			}
			if (peca %2 != 0)
			{
				if (coluna == 7) RokP2 = 0;
				if (coluna == 0) RokP1 = 0;
			}
		}
	}

	/***********************************
	??Selecionar a pe?a para mov?-la??
	?Mover a Pe?a para a nova posi??o?
	***********************************/

	BoardClean();//Limpa o Tabuleiro das amea?as!

	if (((Board[DestLinha][DestColuna] == 10)&&(DestLinha == 0))||((Board[DestLinha][DestColuna] == 11)&&(DestLinha == 7)))//Se um pe?o chegar ao lado oposto:
	{
		PrintBoard();
		setlocale(LC_ALL, "Portuguese");
		printf("***Parab?ns!***\nSeu pe?o chegou ao lado oposto, em qual pe?a gostaria de transform?-lo?");
		PONTO4:
		printf("\n1bispo.  2cavalo.  3torre.  4rainha.\n");
		scanf("%d", &Board[DestLinha][DestColuna]);
		system("cls");
		switch( Board[DestLinha][DestColuna] )
		{
			case 1: Board[DestLinha][DestColuna] = 20+vez; break;
			case 2: Board[DestLinha][DestColuna] = 30+vez; break;
			case 3: Board[DestLinha][DestColuna] = 40+vez; break;
			case 4: Board[DestLinha][DestColuna] = 50+vez; break;
			default: { printf("\nOp??o inv?linda!tente novamente!"); goto PONTO4; } break;
		}
	}
	
}

void BoardClean ( void )
{
	for(int ver=0; ver<8; ver++)//Limpa o Tabuleiro de amea?as:
	{
		for(int hor=0; hor<8; hor++)
		{
			if ((Board[ver][hor] == 2)||(Board[ver][hor] == 3))
			Board[ver][hor] = 0;
			
			for(int Blc = 4;Blc<64;Blc++)//Checa quais pe?as est?o amea?adas(12,13,22,23,32,33,42,43,52,53,62,63).
			{
				if (Blc % 2 ==0){ Blc += 8; }

				if (Board[ver][hor] == Blc)
				{
					Board[ver][hor] -=2;//Desamea?a a pe?a.
				}
			}
		}
	}
}
