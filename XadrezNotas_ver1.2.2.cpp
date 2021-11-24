/*
	XADREZ NOTAS
			Desenvolvido por:	
							Brendo Anthony Borges
			Agradecimentos especiais:
							Eduardo de Oliveira Florencio
							Brian Keven Felizardo
			Fórum de pesquisa:	https://forum.scriptbrasil.com.br/topic/153713-jogo-de-xadrez/
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <windows.h>
#include <dos.h>
#include <dir.h>
#include <string.h>


using namespace std;

void SetWindow(int Width, int Height, int WidthBuffer, int HeightBuffer) { 
    _COORD coord; 
    coord.X = WidthBuffer; 
    coord.Y = HeightBuffer; 

    _SMALL_RECT Rect; 
    Rect.Top = 0; 
    Rect.Left = 0; 
    Rect.Bottom = Height - 1; 
    Rect.Right = Width - 1; 

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
}


int Board[8][8] = 
/*
ESSE TABULEIRO ESTÁ REPRESENTADO POR NÚMEROS (8×8).
*NUMEROS PARES(BRANCAS), NUMEROS ÍMPARES(PRETAS).
*10(peão) 20(bispo) 30(cavalo) 40(torre) 50(rainha) 60(rei) 00(casa vazia)
*/
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

int main(int argc, char *argv[])
{
	//Definir dimensões do executável
	int width = 33;
    int height = 26;
    int wbuffer = width;
    int hbuffer = height;

    if ( argc == 5 ){
        width = atoi(argv[1]);
        height = atoi(argv[2]);
        wbuffer = atoi(argv[3]);
        hbuffer = atoi(argv[4]);
    } else if ( argc > 1 ) {
        cout << "Usage: " << argv[0] << " [ width height bufferwidth bufferheight ]" << endl << endl;
        cout << "  Where" << endl;
        cout << "    width            console width" << endl;
        cout << "    height           console height" << endl;
        cout << "    bufferwidth      scroll buffer width" << endl;
        cout << "    bufferheight     scroll buffer height" << endl;
        return 4;
    }    

    SetWindow(width,height,wbuffer,hbuffer);
 

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
	system("color F0");
	printf("\n    : | 1 2 3 4 5 6 7 8 | :\n     ---------------------\n");
	for(int ver=0; ver<8; ver++)
	{
		printf("    %d |", 8-ver);
		for(int hor=0; hor<8; hor++)
		{
			switch( Board[ver][hor] )
			{
				case 2: printf(" X"); break;//Seleção Branca.
				case 3: printf(" X"); break;//Seleção Preta.
				
				case 10: printf(" P"); break;//Peão Branco.
				case 11: printf(" p"); break;//Peão Preto.
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

				case 12: printf(" X"); break;//Peão Branco Ameaçado.
				case 13: printf(" X"); break;//Peão Preto Ameaçado.
				case 22: printf(" X"); break;//Bispo Branco Ameaçado.
				case 23: printf(" X"); break;//Bispo Preto Ameaçado.
				case 32: printf(" X"); break;//Cavalo Branco Ameaçado.
				case 33: printf(" X"); break;//Cavalo Preto Ameaçado.
				case 42: printf(" X"); break;//Torre Branca Ameaçada.
				case 43: printf(" X"); break;//Torre Preta Ameaçada.
				case 52: printf(" X"); break;//Rainha Branca Ameaçada.
				case 53: printf(" X"); break;//Rainha Preta Ameaçada.
				case 62: printf(" X"); break;//Rei Branco Ameaçado.
				case 63: printf(" X"); break;//Rei Preto Ameaçado.

				default: if ((ver+hor) % 2 ==0) printf(" -"); else printf(" -"); break;//Case Vazia.
			}
		}
		printf(" | %d\n", 8-ver);
	}
	printf("     ---------------------\n    : | 1 2 3 4 5 6 7 8 | :\n");
}

void SelectPiece( int vez, bool &RokB1, bool &RokP1, bool &RokB2, bool &RokP2, int &DePassagemL, int &DePassagemC )
{
	/*
	*Selecionar a peça para movê-la
	*/

	int linha=0, coluna=0, DestLinha=0, DestColuna=0, peca, hor, ver, i, j, reibranco, reipreto, novam=0, novame=0, normal=0, normale=0;
	char certeza;
	char certezae;
	
	PONTO1:
	do
	{
		
		reibranco = 1;
		reipreto = 1;
		//Checa se o Rei está no tabuleiro
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
			setlocale(LC_ALL, "Portuguese");
			printf("\nXeque Mate! Vitória das pretas\n\n");
			exit(0);
		}
		if (reipreto==1)
		{
			setlocale(LC_ALL, "Portuguese");
			printf("\nXeque Mate! Vitória das brancas\n\n");
			exit(0);
		}
		//Seleciona uma peça
		if (normal == 0)
		{
			setlocale(LC_ALL, "Portuguese");
			printf(" _______________________________  \n");
			printf("|                               | \n");
			printf("|                               | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        SELECIONAR PEÇA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peça   | 0");
			scanf("%d", &linha);
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("|                               | \n");
				printf("|                               | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        SELECIONAR PEÇA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peça   | 0%d |\n",linha);
				printf("|Digite a COLUNA da peça   | 0");
				scanf("%d", &coluna);
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("|                               | \n");
					printf("|                               | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        SELECIONAR PEÇA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peça   | 0%d |\n",linha);
					printf("|Digite a COLUNA da peça   | 0%d |\n",coluna);
					printf("|-------------------------------|\n");
					printf("           TEM CERTEZA?\n");
					printf("               ");
					scanf("%s", &certeza);
					system("cls");
					novam = 0;
		}
	
		if (novam == 1)		
		{
			setlocale(LC_ALL, "Portuguese");
			printf(" _______________________________  \n");
			printf("|                               | \n");
			printf("|   Escolha a peça novamente    | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        SELECIONAR PEÇA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peça   | 0");
			scanf("%d", &linha);
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("|                               | \n");
				printf("|   Escolha a peça novamente    | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        SELECIONAR PEÇA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peça   | 0%d |\n",linha);
				printf("|Digite a COLUNA da peça   | 0");
				scanf("%d", &coluna);
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("|                               | \n");
					printf("|   Escolha a peça novamente    | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        SELECIONAR PEÇA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peça   | 0%d |\n",linha);
					printf("|Digite a COLUNA da peça   | 0%d |\n",coluna);
					printf("|-------------------------------|\n");
					printf("           TEM CERTEZA?\n");
					printf("               ");
					scanf("%s", &certeza);
					system("cls");
					normal = 0;
					novam = 0;
		}
	
		if (novam == 2)		
		{
			setlocale(LC_ALL, "Portuguese");
			printf(" _______________________________  \n");
			printf("|Você selecionou uma casa vazia!| \n");
			printf("|   Escolha a peça novamente    | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        SELECIONAR PEÇA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peça   | 0");
			scanf("%d", &linha);
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("|Você selecionou uma casa vazia!| \n");
				printf("|   Escolha a peça novamente    | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        SELECIONAR PEÇA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peça   | 0%d |\n",linha);
				printf("|Digite a COLUNA da peça   | 0");
				scanf("%d", &coluna);
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("|Você selecionou uma casa vazia!| \n");
					printf("|   Escolha a peça novamente    | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        SELECIONAR PEÇA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peça   | 0%d |\n",linha);
					printf("|Digite a COLUNA da peça   | 0%d |\n",coluna);
					printf("|-------------------------------|\n");
					printf("           TEM CERTEZA?\n");
					printf("               ");
					scanf("%s", &certeza);
					system("cls");
					normal = 0;
					novam = 0;
		}
	
		if (novam == 3)		
		{
			setlocale(LC_ALL, "Portuguese");
			printf(" _______________________________  \n");
			printf("| Peça do oponente selecionada! | \n");
			printf("|   Escolha a peça novamente    | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        SELECIONAR PEÇA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peça   | 0");
			scanf("%d", &linha);
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("| Peça do oponente selecionada! | \n");
				printf("|   Escolha a peça novamente    | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        SELECIONAR PEÇA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peça   | 0%d |\n",linha);
				printf("|Digite a COLUNA da peça   | 0");
				scanf("%d", &coluna);
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("| Peça do oponente selecionada! | \n");
					printf("|   Escolha a peça novamente    | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        SELECIONAR PEÇA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peça   | 0%d |\n",linha);
					printf("|Digite a COLUNA da peça   | 0%d |\n",coluna);
					printf("|-------------------------------|\n");
					printf("           TEM CERTEZA?\n");
					printf("               ");
					scanf("%s", &certeza);
					system("cls");
					normal = 0;
					novam = 0;
		}
		//Checha se foi digitado 'não' na certeza		
		if (certeza =='nao' || certeza=='NAO' || certeza=='não' || certeza=='NÃO' || certeza=='Não' || certeza=='Nao' || certeza=='n' || certeza=='N' || certeza=='Nn' || certeza=='nn' || certeza=='NN')
		{
			linha = 0, coluna = 0;
		}
		
		//Checa se a casa selecionada é válida:
		if((linha<1 || linha >8)||(coluna<1 || coluna>8))
		{
			PrintBoard();
			setlocale(LC_ALL, "Portuguese");
			novam = 1;
			normal = 1;
		}
		else
		//Checa se a casa selecionada está vazia:
		if (Board[8-linha][coluna-1] == 0)
		{
			PrintBoard();
			setlocale(LC_ALL, "Portuguese");
			normal = 1;
			novam = 2;
			linha = 0, coluna = 0;//Isso fará o laço repetir
		}
		else
		//Checa se é a vez das brancas uma peça branca deve ser selecionada e vice versa:
		if (((Board[8-linha][coluna-1] % 2 == 0)&&(vez == 1))||((Board[8-linha][coluna-1] % 2 != 0)&&(vez == 0)))
		{
			PrintBoard();
			setlocale(LC_ALL, "Portuguese");
			normal = 1;
			novam = 3;
			linha = 0, coluna = 0;//Isso fará o laço repetir
		}
	}while ((linha<1 || linha >8)||(coluna<1 || coluna>8));

	linha = 8-linha;//se digitado 1, deverá ser acessado 0 em "Board[0][].
	coluna -= 1;//se digitado 1, deverá ser acessado 0 em "Board[][0].

	//Nesses if's seleciona a peça e mostra seus possiveis destinos:

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

	if (Board[linha][coluna] == 60+vez)//Reis:
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
	}

	PrintBoard();
	
	/*
	Mover a peça para a nova posição
	*/
	PONTO9:
	do
	{
		
		if (normale==0)
		{
			setlocale(LC_ALL, "Portuguese");
			printf(" _______________________________  \n");
			printf("|                               | \n");
			printf("|                               | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        MOVIMENTAR PEÇA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peça   | 0");
			while(!scanf ("%d", &DestLinha)) //Digitar letra e reiniciar PONTO 9
			{
     	  		while(getchar() != '\n');
     	  		{
     	  			system("cls");
     				PrintBoard();
     	    		goto PONTO9;
     	   		}
   			}
   			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("|                               | \n");
				printf("|                               | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        MOVIMENTAR PEÇA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peça   | 0%d |\n",DestLinha);
				printf("|Digite a COLUNA da peça   | 0");
				while(!scanf ("%d", &DestColuna)) //Digitar letra e reiniciar PONTO 9
				{
     	  			while(getchar() != '\n');
     	  			{
     	  				system("cls");
     					PrintBoard();
     	    			goto PONTO9;
     	   			}
   				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("|                               | \n");
					printf("|                               | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        MOVIMENTAR PEÇA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peça   | 0%d |\n",DestLinha);
					printf("|Digite a COLUNA da peça   | 0%d |\n",DestColuna);
					printf("|-------------------------------|\n");
					system("cls");
					novame = 0;
					normal = 0;
					novam = 0;
		}
		
		if (novame == 1)		
		{
			setlocale(LC_ALL, "Portuguese");
			printf(" _______________________________  \n");
			printf("| Sua peça não se movimenta aí !| \n");
			printf("|   Escolha onde mover a peça   | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        MOVIMENTAR PEÇA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peça   | 0");
			while(!scanf ("%d", &DestLinha)) //Digitar letra e reiniciar PONTO 9 
			{
     	  		while(getchar() != '\n');
     	  		{
     	  			system("cls");
     				PrintBoard();
     	    		goto PONTO9;
     	   		}
   			}
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("| Sua peça não se movimenta aí !| \n");
				printf("|   Escolha onde mover a peça   | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        MOVIMENTAR PEÇA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peça   | 0%d |\n",DestLinha);
				printf("|Digite a COLUNA da peça   | 0");
				while(!scanf ("%d", &DestColuna)) //Digitar letra e reiniciar PONTO 9 
				{
     	  			while(getchar() != '\n');
     	  			{
     	  				system("cls");
     					PrintBoard();
     	    			goto PONTO9;
     	   			}
   				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("| Sua peça não se movimenta aí !| \n");
					printf("|   Escolha onde mover a peça   | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        MOVIMENTAR PEÇA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peça   | 0%d |\n",DestLinha);
					printf("|Digite a COLUNA da peça   | 0%d |\n",DestColuna);
					printf("|-------------------------------|\n");
					system("cls");
					normale = 0;
					novame = 0;
					normal = 0;
					novam = 0;
		}
		
		if (novame == 2)		
		{
			setlocale(LC_ALL, "Portuguese");
			printf(" _______________________________  \n");
			printf("|Você selecionou uma casa usada!| \n");
			printf("|   Escolha onde mover a peça   | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        MOVIMENTAR PEÇA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peça   | 0");
			while(!scanf ("%d", &DestLinha)) //Digitar letra e reiniciar PONTO 9 
			{
     	  		while(getchar() != '\n');
     	  		{
     	  			system("cls");
     				PrintBoard();
     	    		goto PONTO9;
     	   		}
   			}
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("|Você selecionou uma casa usada!| \n");
				printf("|   Escolha onde mover a peça   | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        MOVIMENTAR PEÇA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peça   | 0%d |\n",DestLinha);
				printf("|Digite a COLUNA da peça   | 0");
				while(!scanf ("%d", &DestColuna)) //Digitar letra e reiniciar PONTO 9 
				{
     	  			while(getchar() != '\n');
     	  			{
     	  				system("cls");
     					PrintBoard();
     	    			goto PONTO9;
     	   			}
   				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("|Você selecionou uma casa usada!| \n");
					printf("|   Escolha onde mover a peça   | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        MOVIMENTAR PEÇA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peça   | 0%d |\n",DestLinha);
					printf("|Digite a COLUNA da peça   | 0%d |\n",DestColuna);
					printf("|-------------------------------|\n");
					system("cls");
					normale = 0;
					novame = 0;
					normal = 0;
					novam = 0;
		}
		
		if (novame == 3)		
		{
			setlocale(LC_ALL, "Portuguese");
			printf(" _______________________________  \n");
			printf("|Não pode mover na peça inimiga!| \n");
			printf("|   Escolha onde mover a peça   | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        MOVIMENTAR PEÇA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peça   | 0");
			while(!scanf ("%d", &DestLinha)) //Digitar letra e reiniciar PONTO 9 
			{
     	  		while(getchar() != '\n');
     	  		{
     	  			system("cls");
     				PrintBoard();
     	    		goto PONTO9;
     	   		}
   			}
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("|Não pode mover na peça inimiga!| \n");
				printf("|   Escolha onde mover a peça   | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        MOVIMENTAR PEÇA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peça   | 0%d |\n",DestLinha);
				printf("|Digite a COLUNA da peça   | 0");
				while(!scanf ("%d", &DestColuna)) //Digitar letra e reiniciar PONTO 9 
				{
     	  			while(getchar() != '\n');
     	  			{
     	  				system("cls");
     					PrintBoard();
     	    			goto PONTO9;
     	   			}
   				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("|Não pode mover na peça inimiga!| \n");
					printf("|   Escolha onde mover a peça   | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        MOVIMENTAR PEÇA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peça   | 0%d |\n",DestLinha);
					printf("|Digite a COLUNA da peça   | 0%d |\n",DestColuna);
					printf("|-------------------------------|\n");
					system("cls");
					normale = 0;
					novame = 0;
					normal = 0;
					novam = 0;
		}
		
		//Checa se foi digitado um número válido:
		if ((DestLinha < 1 || DestLinha > 8) || (DestColuna < 1 || DestColuna > 8))
		{
			PrintBoard();
			normale = 1;
			novame = 1;
			goto PONTO9;
		}
		//Checa se a casa selecionada está vazia:
		if (Board[8-DestLinha][DestColuna-1] == 0)
		{
			PrintBoard();
			normale = 1;
			novame = 2;
			goto PONTO9;
		}

		//Se escolheu peça branca na vez das brancas, ou escolheu peça preta na vez das pretas:
		if (((Board[8-DestLinha][DestColuna-1] % 2 == 0)&&(vez == 1)) || ((Board[8-DestLinha][DestColuna-1] % 2 != 0)&&(vez == 0)))
		{
			PrintBoard();
			normale = 1;
	  		novame = 3;
			goto PONTO9;
		}
	}while ((DestLinha<1 || DestLinha >8)||(DestColuna<1 || DestColuna>8));

	DestLinha = 8-DestLinha;//inverte os numeros ( 8 equivale a 0, 7 equivale a 1, 6 equivale a 2 ...)
	DestColuna -= 1;//se digitado 1, deverá ser acessado 0 em "Board[][0].

	//Move a peça:
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
		}
		else if (( peca == 11 )&&(DestLinha == 3))
		{
			DePassagemL = DestLinha-1, DePassagemC = DestColuna;
		}
		else{ DePassagemL = -1, DePassagemC = -1; }

	}//ou uma peça do oponente é escolhida.
	else
	{
		for(int Blc = 4;Blc<64;Blc++)//Checa quais peças estão ameaçadas
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

	BoardClean();//Limpa o Tabuleiro das ameaças!

	//Se um peão chegar ao lado oposto:
	if (((Board[DestLinha][DestColuna] == 10)&&(DestLinha == 0))||((Board[DestLinha][DestColuna] == 11)&&(DestLinha == 7)))
	{
		PrintBoard();
		setlocale(LC_ALL, "Portuguese");
		printf("***Parabéns!***\nSeu peão chegou ao lado oposto, em qual peça gostaria de transformá-lo?");
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
			
			for(int Blc = 4;Blc<64;Blc++)//Checa quais peças estão ameaçadas
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
