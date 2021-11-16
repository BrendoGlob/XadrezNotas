/*JOGO DE XADREZ*/

#include <stdio.h>
#include <stdlib.h>

int Board[8][8] = 
/*ESTE TABULEIRO ESTÁ REPRESENTADO POR NÚMEROS (8×8).
?NUMEROS PARES(BRANCAS), NUMEROS ÍMPARES(PRETAS).
10(peão) 20(bispo) 30(cavalo) 40(torre) 50(rainha) 60(rei)*/
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

//FUNÇÕES:
void PrintBoard( void );//Imprime o Tabuleiro para o jogador.
void SelectPiece( int vez, bool &RokB1, bool &RokP1, bool &RokB2, bool &RokP2, int &DePassagemL, int &DePassagemC );//Seleciona e move uma peça.
void BoardClean ( void );//Limpa Tabuleiro(ameaça das peças representada por outros números).
//FUNÇÕES!

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

//CORPOS DAS FUNÇÕES:
void PrintBoard( void )
{
	printf("\n*| a b c d e f g h|*\n--------------------\n");
	for(int ver=0; ver<8; ver++)
	{
		printf("%d|", 8-ver);
		for(int hor=0; hor<8; hor++)
		{
			switch( Board[ver][hor] )
			{
				case 2: printf(" X"); break;//Seleção Branca.
				case 3: printf(" X"); break;//Seleção Preta.

				case 10: printf(".1"); break;//Peão Branco.
				case 11: printf(".A"); break;//Peão Preto.
				case 20: printf(".2"); break;//Bispo Branco.
				case 21: printf(".B"); break;//Bispo Preto.
				case 30: printf(".3"); break;//Cavalo Branco.
				case 31: printf(".C"); break;//Cavalo Preto.
				case 40: printf(".4"); break;//Torre Branca.
				case 41: printf(".D"); break;//Torre Preta.
				case 50: printf(".5"); break;//Rainha Branca.
				case 51: printf(".E"); break;//Rainha Preta.
				case 60: printf(".6"); break;//Rei Branco.
				case 61: printf(".F"); break;//Rei Preto.

				case 12: printf("!1"); break;//Peão Branco Ameaçado.
				case 13: printf("!A"); break;//Peão Preto Ameaçado.
				case 22: printf("!2"); break;//Bispo Branco Ameaçado.
				case 23: printf("!B"); break;//Bispo Preto Ameaçado.
				case 32: printf("!3"); break;//Cavalo Branco Ameaçado.
				case 33: printf("!C"); break;//Cavalo Preto Ameaçado.
				case 42: printf("!4"); break;//Torre Branca Ameaçada.
				case 43: printf("!D"); break;//Torre Preta Ameaçada.
				case 52: printf("!5"); break;//Rainha Branca Ameaçada.
				case 53: printf("!E"); break;//Rainha Preta Ameaçada.
				case 62: printf("!6"); break;//Rei Branco em Cheque.
				case 63: printf("!F"); break;//Rei Preto em Cheque.

				default: if ((ver+hor) % 2 ==0) printf(" ."); else printf(" :"); break;//Case Vazia.
			}
		}
		printf("|%d\n", 8-ver);
	}
	printf("--------------------\n*| 1 2 3 4 5 6 7 8|*\n");
}

void SelectPiece( int vez, bool &RokB1, bool &RokP1, bool &RokB2, bool &RokP2, int &DePassagemL, int &DePassagemC )
{
		/***********************************
	?Selecionar a peça para movê-la?
	??Mover a Peça para a nova posição??
	***********************************/

	int linha=0, coluna=0, DestLinha=0, DestColuna=0, peca, hor, ver;

	PONTO1:
	//?Selecionar uma peça:
	do
	{
		printf("\nDigite qual peça deseja mover(exemplo: 2(linha) 4(coluna))? ");
		scanf("%d%d", &linha, &coluna);

		//Checa se a casa selecionada é válida:
		if((linha<1 || linha >8)||(coluna<1 || coluna>8))
		{
			printf("\nVocê digitou errado!Tente novamente!\n");
		}
		else
		//Checa se a casa selecionada está vazia:
		if (Board[8-linha][coluna-1] == 0)
		{
			printf("\nVocê selecionou uma casa vazia!Selecione uma peça!\n");
			linha = 0, coluna = 0;//?isso fará o laço repetir!
		}
		else
		//Checa se é a vez das brancas uma peça branca deve ser selecionada e vice versa:
		if (((Board[8-linha][coluna-1] % 2 == 0)&&(vez == 1))||((Board[8-linha][coluna-1] % 2 != 0)&&(vez == 0)))
		{
			printf("\nVocê não pode selecionar uma peça do oponente!Seleciona as suas!\n");
			linha = 0, coluna = 0;//?isso fará o laço repetir!
		}
	}while ((linha<1 || linha >8)||(coluna<1 || coluna>8));

	linha = 8-linha;//se digitado 1, deverá ser acessado 0 em "Board[0][].
	coluna -= 1;//se digitado 1, deverá ser acessado 0 em "Board[][0].

	//Nesses ifis? seleciona a peça e mostra seus possiveis destinos:

	if (Board[linha][coluna] == 10)//Peão Branco:
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

	if (Board[linha][coluna] == 11)//Peão Preto:
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

		//Peças do adersário brancas:
		if ((Board[linha][coluna-1] %2 == 0)&&(vez == 1)) Board[linha][coluna-1] += 2;//Cima.
		if ((Board[linha][coluna+1] %2 == 0)&&(vez == 1)) Board[linha][coluna+1] += 2;//Baixo.
		if ((Board[linha-1][coluna] %2 == 0)&&(vez == 1)) Board[linha-1][coluna] += 2;//Esquerda.
		if ((Board[linha+1][coluna] %2 == 0)&&(vez == 1)) Board[linha+1][coluna] += 2;//Direita.
		if ((Board[linha-1][coluna-1] %2 == 0)&&(vez == 1)) Board[linha-1][coluna-1] += 2;//Diagonal cima esquerda.
		if ((Board[linha+1][coluna-1] %2 == 0)&&(vez == 1)) Board[linha+1][coluna-1] += 2;//Diagonal cima direita.
		if ((Board[linha+1][coluna+1] %2 == 0)&&(vez == 1)) Board[linha+1][coluna+1] += 2;//Diagonal baixo direita.
		if ((Board[linha-1][coluna+1] %2 == 0)&&(vez == 1)) Board[linha-1][coluna+1] += 2;//Diagonal baixo esquerda.

		//Peças do adersário pretas:
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
	?Selecionar a peça para movê-la?
	?Mover a Peça para a nova posição?
	***********************************/

	do
	{
		printf("\nDigite o local que deseja mover a peça? ");
		scanf("%d%d", &DestLinha, &DestColuna);

		//Checa se foi digitado um número válido:
		if ((DestLinha<1 || DestLinha >8)||(DestColuna<1 || DestColuna>8))
		{
			printf("\nVocê digitou errado!Tente novamente!\n");
		}
		else
		//Checa se a casa selecionada está vazia:
		if (Board[8-DestLinha][DestColuna-1] == 0)
		{
			printf("\nVocê selecionou uma casa inválida, selecione o 'X' ou uma outra peça!\n");
		}
		else
		//Checa se o jogador escolheu um local com uma peça aliada:
		for(int Blc = 6;Blc<57;Blc++)//Checa quais peças estão ameaçadas(14,15,24,25,34,35,44,45,46,47,54,55,56,57).
		{
			if (Blc % 2 ==0){ Blc += 8; }

			//Se a casa não estiver vazia, e não for uma casa selecionada pora possivel jogada.
			if ((Board[8-DestLinha][DestColuna-1] >0)&&(Board[8-DestLinha][DestColuna-1] != 2+vez))
			//Se escolheu peça branca na vez das brancas, ou escolheu peça preta na vez das pretas:
			if (((Board[8-DestLinha][DestColuna-1] % 2 == 0)&&(vez == 0)) || ((Board[8-DestLinha][DestColuna-1] % 2 != 0)&&(vez == 1)))
			{
				printf("\nVocê não pode comer uma peça da sua 'cor'! Tente de novo ou selecione outra.\n");
				linha = 0, coluna = 0, DestLinha = 0, DestColuna = 0, peca = 0;
				BoardClean();
				PrintBoard();
				goto PONTO1;
			}
		}
	}while ((DestLinha<1 || DestLinha >8)||(DestColuna<1 || DestColuna>8));

	DestLinha = 8-DestLinha;//inverte os numeros ( 8 equivale a 0, 7 equivale a 1, 6 equivale a 2 ...)
	DestColuna -= 1;//se digitado 1, deverá ser acessado 0 em "Board[][0].

	//?Move a peça:
	if ((Board[DestLinha][DestColuna] == 2)||(Board[DestLinha][DestColuna] == 3))
	//Se uma casa selecionada:
	{
		Board[DestLinha][DestColuna] = peca;//Aloca a peça em seu destino.
		Board[linha][coluna] = 0;//Retira a peça de sua origem.
		if (( DestLinha == DePassagemL )&&( DestColuna == DePassagemC ))
		{
			if ( vez == 0)Board[DePassagemL+1][DePassagemC] = 0;
			if ( vez == 1)Board[DePassagemL-1][DePassagemC] = 0;
		}

		//Ativa a Jogada "El_passant" no Peão:
		if (( peca == 10 )&&(DestLinha == 4))
		{
			DePassagemL = DestLinha+1, DePassagemC = DestColuna;
			printf("De Passagem = linha %d, coluna %d\n", DePassagemL, DePassagemC );
		}
		else if (( peca == 11 )&&(DestLinha == 3))
		{
			DePassagemL = DestLinha-1, DePassagemC = DestColuna;
			printf("De Passagem = linha %d, coluna %d\n", DePassagemL, DePassagemC );
		}
		else{ DePassagemL = -1, DePassagemC = -1; }

	}//ou uma peça do oponente é escolhida.
	else
	{
		for(int Blc = 4;Blc<54;Blc++)//Checa quais peças estão ameaçadas(12,13,22,23,32,33,42,43,42,43,52,53).
		{
			if (Blc % 2 == 0){ Blc += 8; }

			if (Board[DestLinha][DestColuna] == Blc)
			{
				Board[DestLinha][DestColuna] = peca;//Aloca a peça em seu destino.
				Board[linha][coluna] = 0;//Retira a peça de sua origem.
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
	??Selecionar a peça para movê-la??
	?Mover a Peça para a nova posição?
	***********************************/

	BoardClean();//Limpa o Tabuleiro das ameaças!

	if (((Board[DestLinha][DestColuna] == 10)&&(DestLinha == 0))||((Board[DestLinha][DestColuna] == 11)&&(DestLinha == 7)))//Se um peão chegar ao lado oposto:
	{
		printf("***Parabéns!***\nSeu peão chegou ao lado oposto, em qual peça gostaria de transformá-lo?");
		PONTO4:
		printf("\n1?bispo. 2?cavalo. 3?torre. 4?rainha.\n?");
		scanf("%d", &Board[DestLinha][DestColuna]);
		switch( Board[DestLinha][DestColuna] )
		{
			case 1: Board[DestLinha][DestColuna] = 20+vez; break;
			case 2: Board[DestLinha][DestColuna] = 30+vez; break;
			case 3: Board[DestLinha][DestColuna] = 40+vez; break;
			case 4: Board[DestLinha][DestColuna] = 50+vez; break;
			default: { printf("\nOpção inválinda!tente novamente!"); goto PONTO4; } break;
		}
	}
}

void BoardClean ( void )
{
	for(int ver=0; ver<8; ver++)//Limpa o Tabuleiro de ameaças:
	{
		for(int hor=0; hor<8; hor++)
		{
			if ((Board[ver][hor] == 2)||(Board[ver][hor] == 3))
			Board[ver][hor] = 0;
			
			for(int Blc = 4;Blc<64;Blc++)//Checa quais peças estão ameaçadas(12,13,22,23,32,33,42,43,52,53,62,63).
			{
				if (Blc % 2 ==0){ Blc += 8; }

				if (Board[ver][hor] == Blc)
				{
					Board[ver][hor] -=2;//Desameaça a peça.
				}
			}
		}
	}
}
//CORPOS DAS FUNÇÕES!
