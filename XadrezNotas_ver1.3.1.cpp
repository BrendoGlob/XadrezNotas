/*
	XADREZ NOTAS
			Desenvolvido por:	
							Brendo Anthony Borges
			Agradecimentos especiais:
							Brian Keven Felizardo
							Eduardo de Oliveira Florencio
							Raqueliani Nogueira de Assis
			Mecânica base do jogo de xadrez: https://forum.scriptbrasil.com.br/topic/153713-jogo-de-xadrez/
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
#include <fcntl.h>
#include <io.h>
#include <stddef.h>
#define PEAOP L"\u2659"
#define PEAOB L"\u265f"
#define BISPOP L"\u2657"
#define BISPOB L"\u265d"
#define CAVALOP L"\u2658"
#define CAVALOB L"\u265e"
#define TORREP L"\u2656"
#define TORREB L"\u265c"
#define RAINHAP L"\u2655"
#define RAINHAB L"\u265b"
#define REIP L"\u2654"
#define REIB L"\u265a"
#define BRANCO_FUNDO "\x1b[44m"
#define PRETO_FUNDO "\x1b[48m"
#define VERMELHO_FUNDO "\x1b[41m"
#define RESETA_TUDO "\x1b[0m"

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
	system("title XADREZ NOTAS");
	_setmode(_fileno(stdout), _O_TEXT);
	//Definir dimensões do executável
	int width = 34;
    int height = 25;
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
	CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 10;
    cfi.dwFontSize.Y = 20;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    
    _setmode(_fileno(stdout), _O_U16TEXT);
    
    wcscpy(cfi.FaceName, L"NSimSun");
    
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	
    SetConsoleOutputCP(65001);
	
	_setmode(_fileno(stdout), _O_TEXT);
	
	printf(RESETA_TUDO);
	
	printf("\n     : | 1 2 3 4 5 6 7 8 | :\n      ---------------------\n");
	for(int ver=0; ver<8; ver++)
	{
		printf("     %d | ", 8-ver);
		for(int hor=0; hor<8; hor++)
		{
			switch( Board[ver][hor] )
			{
				case 2:  printf(VERMELHO_FUNDO "  "); 
				break;//Seleção Branca.
				
				case 3: printf(VERMELHO_FUNDO "  "); 
				break;//Seleção Preta.
				
				case 10: 
						if ((ver+hor) % 2 ==0) 
						{
						 printf(BRANCO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(PEAOB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(""); 
						 printf(RESETA_TUDO);
						} 
						 else 
						{ 
						 printf(PRETO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(PEAOB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(""); 
						 printf(RESETA_TUDO);
						}
						 break; //Peão Branco.
				case 11: 
						if ((ver+hor) % 2 ==0) 
						{
						 printf(BRANCO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(PEAOP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						} 
						 else 
						{ 
						 printf(PRETO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(PEAOP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						}
						 break; //Peão Preto.
				case 20: 
						if ((ver+hor) % 2 ==0) 
						{
						 printf(BRANCO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(BISPOB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						} 
						 else 
						{ 
						 printf(PRETO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(BISPOB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						}
						 break; //Bispo Branco.
				case 21: 
						if ((ver+hor) % 2 ==0) 
						{
						 printf(BRANCO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(BISPOP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						} 
						 else 
						{ 
						 printf(PRETO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(BISPOP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						}
						 break; //Bispo Preto.
				case 30: 
						if ((ver+hor) % 2 ==0) 
						{
						 printf(BRANCO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(CAVALOB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						} 
						 else 
						{ 
						 printf(PRETO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(CAVALOB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						}
						 break; //Cavalo Branco.
				case 31: 
						if ((ver+hor) % 2 ==0) 
						{
						 printf(BRANCO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(CAVALOP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						} 
						 else 
						{ 
						 printf(PRETO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(CAVALOP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						}
						 break; //Cavalo Preto.
				case 40:
						if ((ver+hor) % 2 ==0) 
						{
						 printf(BRANCO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(TORREB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						} 
						 else 
						{ 
						 printf(PRETO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(TORREB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						}
						 break; //Torre Branca.
				case 41:
						if ((ver+hor) % 2 ==0) 
						{
						 printf(BRANCO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(TORREP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						} 
						 else 
						{ 
						 printf(PRETO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(TORREP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						}
						 break; //Torre Preta.
				case 50: 
						if ((ver+hor) % 2 ==0) 
						{
						 printf(BRANCO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(RAINHAB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						} 
						 else 
						{ 
						 printf(PRETO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(RAINHAB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						}
						 break; //Rainha Branca.
				case 51: 
						if ((ver+hor) % 2 ==0) 
						{
						 printf(BRANCO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(RAINHAP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						} 
						 else 
						{ 
						 printf(PRETO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(RAINHAP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						}
						 break; //Rainha Preta.
				case 60:
						if ((ver+hor) % 2 ==0) 
						{
						 printf(BRANCO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(REIB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						} 
						 else 
						{ 
						 printf(PRETO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(REIB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						}
						 break; //Rei Branco.
				case 61:
						if ((ver+hor) % 2 ==0) 
						{
						 printf(BRANCO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(REIP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						} 
						 else 
						{ 
						 printf(PRETO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(REIP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO);
						}
						 break; //Rei Preto.

				case 12: printf(VERMELHO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(PEAOB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(""); 
						 printf(RESETA_TUDO); break;//Peão Branco Ameaçado.
				case 13: printf(VERMELHO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(PEAOP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO); break;//Peão Preto Ameaçado.
				case 22: printf(VERMELHO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(BISPOB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO); break;//Bispo Branco Ameaçado.
				case 23: printf(VERMELHO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(BISPOP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO); break;//Bispo Preto Ameaçado.
				case 32: printf(VERMELHO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(CAVALOB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO); break;//Cavalo Branco Ameaçado.
				case 33: printf(VERMELHO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(CAVALOP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO); break;//Cavalo Preto Ameaçado.
				case 42: printf(VERMELHO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(TORREB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO); break;//Torre Branca Ameaçada.
				case 43: printf(VERMELHO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(TORREP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO); break;//Torre Preta Ameaçada.
				case 52: printf(VERMELHO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(RAINHAB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO); break;//Rainha Branca Ameaçada.
				case 53: printf(VERMELHO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(RAINHAP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO); break;//Rainha Preta Ameaçada.
				case 62: printf(VERMELHO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(REIB); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO); break;//Rei Branco Ameaçado.
				case 63: printf(VERMELHO_FUNDO); 
						 _setmode(_fileno(stdout), _O_TEXT); 
						 _setmode(_fileno(stdout), _O_U16TEXT);	wprintf(REIP); 
						 _setmode(_fileno(stdout), _O_TEXT);	printf(" "); 
						 printf(RESETA_TUDO); break;//Rei Preto Ameaçado.

				default: if ((ver+hor) % 2 ==0) {
						printf(RESETA_TUDO); printf(BRANCO_FUNDO "  "); printf(RESETA_TUDO); } else { printf(RESETA_TUDO); printf(PRETO_FUNDO "  "); printf(RESETA_TUDO); ;} break;//Case Vazia.
			}
		}
		printf(RESETA_TUDO);
		printf("| %d\n", 8-ver);
	
	}
	printf("      ---------------------\n     : | 1 2 3 4 5 6 7 8 | :\n");
	
	_setmode(_fileno(stdout), _O_TEXT);
}

void SelectPiece( int vez, bool &RokB1, bool &RokP1, bool &RokB2, bool &RokP2, int &DePassagemL, int &DePassagemC )
{
	printf(RESETA_TUDO);
	/*
	*Selecionar a peça para movê-la
	*/

	int linha=0, coluna=0, DestLinha=0, DestColuna=0, peca, hor, ver, horr, verr, i, j, reibranco, reipreto, novam=0, novame=0, normal=0, normale=0;
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
			printf(" _______________________________  \n");
			printf("|                               | \n");
			printf("|                               | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        SELECIONAR PECA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peca   | 00 |\n");
			printf("|Digite a COLUNA da peca   | 00 |\n");
			printf("|-------------------------------|\n");
			linha = getch();
			if ((linha >= 48) || (linha <= 57))
			{
				linha = linha - 48;
			}
			if (vez == 0)
			{
				Beep(600,200);
			}
			if (vez == 1)
			{
				Beep(400,300);
			}
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("|                               | \n");
				printf("|                               | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        SELECIONAR PECA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peca   | 0%d |\n",linha);
				printf("|Digite a COLUNA da peca   | 00 |\n");
				printf("|-------------------------------|\n");
				coluna = getch();
				if ((coluna >= 48) || (coluna <= 57))
				{
					coluna = coluna - 48;
				}	
				if (vez == 0)
				{
					Beep(600,200);
				}
				if (vez == 1)
				{
					Beep(400,300);
				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("|                               | \n");
					printf("|                               | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        SELECIONAR PECA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peca   | 0%d |\n",linha);
					printf("|Digite a COLUNA da peca   | 0%d |\n",coluna);
					printf("|-------------------------------|\n");
					system("cls");	
					
			novam = 0;
		}
	
		if (novam == 1)		
		{
			printf(" _______________________________  \n");
			printf("|                               | \n");
			printf("|   Escolha a peca novamente    | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        SELECIONAR PECA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peca   | 00 |\n");
			printf("|Digite a COLUNA da peca   | 00 |\n");
			printf("|-------------------------------|\n");
			linha = getch();
			if ((linha >= 48) || (linha <= 57))
			{
				linha = linha - 48;
			}
			if (vez == 0)
			{
				Beep(600,200);
			}
			if (vez == 1)
			{
				Beep(400,300);
			}
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("|                               | \n");
				printf("|   Escolha a peca novamente    | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        SELECIONAR PECA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peca   | 0%d |\n",linha);
				printf("|Digite a COLUNA da peca   | 00 |\n");
				printf("|-------------------------------|\n");
				coluna = getch();
				if ((coluna >= 48) || (coluna <= 57))
				{
					coluna = coluna - 48;
				}	
				if (vez == 0)
				{
					Beep(600,200);
				}
				if (vez == 1)
				{
					Beep(400,300);
				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("|                               | \n");
					printf("|   Escolha a peca novamente    | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        SELECIONAR PECA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peca   | 0%d |\n",linha);
					printf("|Digite a COLUNA da peca   | 0%d |\n",coluna);
					printf("|-------------------------------|\n");
					system("cls");	
					normal = 0;
					novam = 0;
		}
	
		if (novam == 2)		
		{
			printf(" _______________________________  \n");
			printf("|Voce selecionou uma casa vazia!| \n");
			printf("|   Escolha a peca novamente    | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        SELECIONAR PECA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peca   | 00 |\n");
			printf("|Digite a COLUNA da peca   | 00 |\n");
			printf("|-------------------------------|\n");
			linha = getch();
			if ((linha >= 48) || (linha <= 57))
			{
				linha = linha - 48;
			}
			if (vez == 0)
			{
				Beep(600,200);
			}
			if (vez == 1)
			{
				Beep(400,300);
			}
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("|Voce selecionou uma casa vazia!| \n");
				printf("|   Escolha a peca novamente    | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        SELECIONAR PECA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peca   | 0%d |\n",linha);
				printf("|Digite a COLUNA da peca   | 00 |\n");
				printf("|-------------------------------|\n");
				coluna = getch();
				if ((coluna >= 48) || (coluna <= 57))
				{
					coluna = coluna - 48;
				}	
				if (vez == 0)
				{
					Beep(600,200);
				}
				if (vez == 1)
				{
					Beep(400,300);
				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("|Voce selecionou uma casa vazia!| \n");
					printf("|   Escolha a peca novamente    | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        SELECIONAR PECA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peca   | 0%d |\n",linha);
					printf("|Digite a COLUNA da peca   | 0%d |\n",coluna);
					printf("|-------------------------------|\n");
					system("cls");	
					normal = 0;
					novam = 0;
		}
	
		if (novam == 3)		
		{
			printf(" _______________________________  \n");
			printf("| Peca do oponente selecionada! | \n");
			printf("|   Escolha a peca novamente    | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        SELECIONAR PECA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peca   | 00 |\n");
			printf("|Digite a COLUNA da peca   | 00 |\n");
			printf("|-------------------------------|\n");
			linha = getch();
			if ((linha >= 48) || (linha <= 57))
			{
				linha = linha - 48;
			}
			if (vez == 0)
			{
				Beep(600,200);
			}
			if (vez == 1)
			{
				Beep(400,300);
			}
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("| Peca do oponente selecionada! | \n");
				printf("|   Escolha a peca novamente    | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        SELECIONAR PECA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peca   | 0%d |\n",linha);
				printf("|Digite a COLUNA da peca   | 00 |\n");
				printf("|-------------------------------|\n");
				coluna = getch();
				if ((coluna >= 48) || (coluna <= 57))
				{
					coluna = coluna - 48;
				}
				if (vez == 0)
				{
					Beep(600,200);
				}
				if (vez == 1)
				{
					Beep(400,300);
				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("| Peca do oponente selecionada! | \n");
					printf("|   Escolha a peca novamente    | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        SELECIONAR PECA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peca   | 0%d |\n",linha);
					printf("|Digite a COLUNA da peca   | 0%d |\n",coluna);
					printf("|-------------------------------|\n");
					system("cls");	
					normal = 0;
					novam = 0;
		}
		
		if (novam == 4)		
		{
			printf(" _______________________________  \n");
			printf("|Peca esta bloqueada de se mover| \n");
			printf("|   Escolha a peca novamente    | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        SELECIONAR PECA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peca   | 00 |\n");
			printf("|Digite a COLUNA da peca   | 00 |\n");
			printf("|-------------------------------|\n");
			linha = getch();
			if ((linha >= 48) || (linha <= 57))
			{
				linha = linha - 48;
			}
			if (vez == 0)
			{
				Beep(600,200);
			}
			if (vez == 1)
			{
				Beep(400,300);
			}
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("|Peca esta bloqueada de se mover| \n");
				printf("|   Escolha a peca novamente    | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        SELECIONAR PECA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peca   | 0%d |\n",linha);
				printf("|Digite a COLUNA da peca   | 00 |\n");
				printf("|-------------------------------|\n");
				coluna = getch();
				if ((coluna >= 48) || (coluna <= 57))
				{
					coluna = coluna - 48;
				}
				if (vez == 0)
				{
					Beep(600,200);
				}
				if (vez == 1)
				{
					Beep(400,300);
				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("|Peca esta bloqueada de se mover| \n");
					printf("|   Escolha a peca novamente    | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        SELECIONAR PECA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peca   | 0%d |\n",linha);
					printf("|Digite a COLUNA da peca   | 0%d |\n",coluna);
					printf("|-------------------------------|\n");
					system("cls");	
					normal = 0;
					novam = 0;
		}
		
		if (novam == 5)		
		{
			printf(" _______________________________  \n");
			printf("| Nao foi escolhida uma casa do | \n");
			printf("|  tabuleiro, digite novamente  | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        SELECIONAR PECA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peca   | 00 |\n");
			printf("|Digite a COLUNA da peca   | 00 |\n");
			printf("|-------------------------------|\n");
			linha = getch();
			if ((linha >= 48) || (linha <= 57))
			{
				linha = linha - 48;
			}
			if (vez == 0)
			{
				Beep(600,200);
			}
			if (vez == 1)
			{
				Beep(400,300);
			}
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("| Nao foi escolhida uma casa do | \n");
				printf("|  tabuleiro, digite novamente  | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        SELECIONAR PECA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peca   | 0%d |\n",linha);
				printf("|Digite a COLUNA da peca   | 00 |\n");
				printf("|-------------------------------|\n");
				coluna = getch();
				if ((coluna >= 48) || (coluna <= 57))
				{
					coluna = coluna - 48;
				}
				if (vez == 0)
				{
					Beep(600,200);
				}
				if (vez == 1)
				{
					Beep(400,300);
				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("| Nao foi escolhida uma casa do | \n");
					printf("|  tabuleiro, digite novamente  | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        SELECIONAR PECA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peca   | 0%d |\n",linha);
					printf("|Digite a COLUNA da peca   | 0%d |\n",coluna);
					printf("|-------------------------------|\n");
					system("cls");	
					normal = 0;
					novam = 0;
		}
		
		if ((linha == 0)&&(coluna == 0))
		{
			PrintBoard();
			normal = 1;//Definirá que não é mais uma seleção normal
			novam = 5;//Em que parte vai repetir com mensagem única
			linha = 0, coluna = 0;//Isso fará o laço repetir
		}
		
		
		int linhaesquerdacima, colunaesquerdacima, linhadireitacima, colunadireitacima, linhaesquerdabaixo, colunaesquerdabaixo, linhadireitabaixo, colunadireitabaixo;
		
			//Cima
			linhacima = linha + 1;
			//Baixo
			linhabaixo = linha - 1;
			//Esquerda
			colunaesquerda = coluna - 1;
			//Direita
			colunadireita = coluna + 1;
			//Cima diagonal esquerda
			linhaesquerdacima = linha + 1;
			colunaesquerdacima = coluna - 1;
			//Cima diagonal direita
			linhadireitacima = linha + 1;
			colunadireitacima = coluna + 1;
			//Baixo diagonal esquerda
			linhaesquerdabaixo = linha - 1;
			colunaesquerdabaixo = coluna - 1;
			//Baixo diagonal direita
			linhadireitabaixo = linha - 1;
			colunadireitabaixo = coluna + 1;
		
		//Checa se foi selecionado um bispo branco
		if (Board[8-linha][coluna-1] == 20)
		{
			
			//Checa se o bispo branco está bloqueado no centro da primeira linha
			if ((linha == 1)&&(coluna == 2 || coluna == 3 || coluna == 4 || coluna == 5 || coluna == 6 || coluna == 7))
			{
				if ((Board[8-linhaesquerdacima][colunaesquerdacima-1] == 10 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 20 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 30 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 40 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 50 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 60)&&(Board[8-linhadireitacima][colunadireitacima-1] == 10 || Board[8-linhadireitacima][colunadireitacima-1] == 20 || Board[8-linhadireitacima][colunadireitacima-1] == 30 || Board[8-linhadireitacima][colunadireitacima-1] == 40 || Board[8-linhadireitacima][colunadireitacima-1] == 50 || Board[8-linhadireitacima][colunadireitacima-1] == 60))
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no canto esquerdo da primeira linha
			if ((linha == 1)&&(coluna == 1))
			{
				if (Board[8-linhadireitacima][colunadireitacima-1] == 10 || Board[8-linhadireitacima][colunadireitacima-1] == 20 || Board[8-linhadireitacima][colunadireitacima-1] == 30 || Board[8-linhadireitacima][colunadireitacima-1] == 40 || Board[8-linhadireitacima][colunadireitacima-1] == 50 || Board[8-linhadireitacima][colunadireitacima-1] == 60)
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no canto direito da primeira linha
			if ((linha == 1)&&(coluna == 8))
			{
				if (Board[8-linhaesquerdacima][colunaesquerdacima-1] == 10 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 20 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 30 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 40 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 50 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 60)
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no centro da oitava linha
			if ((linha == 8)&&(coluna == 2 || coluna == 3 || coluna == 4 || coluna == 5 || coluna == 6 || coluna == 7))
			{
				if ((Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 10 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 20 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 30 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 40 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 50 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 60)&&(Board[8-linhadireitabaixo][colunadireitabaixo-1] == 10 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 20 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 30 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 40 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 50 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 60))
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no canto esquerdo da oitava linha
			if ((linha == 8)&&(coluna == 1))
			{
				if (Board[8-linhadireitabaixo][colunadireitabaixo-1] == 10 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 20 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 30 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 40 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 50 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 60)
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no canto direito da oitava linha
			if ((linha == 8)&&(coluna == 8))
			{
				if (Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 10 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 20 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 30 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 40 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 50 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 60)
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no centro da primeira coluna
			if ((coluna == 1)&&(linha == 2 || linha == 3 || linha == 4 || linha == 5 || linha == 6 || linha == 7))
			{
				if ((Board[8-linhadireitacima][colunadireitacima-1] == 10 || Board[8-linhadireitacima][colunadireitacima-1] == 20 || Board[8-linhadireitacima][colunadireitacima-1] == 30 || Board[8-linhadireitacima][colunadireitacima-1] == 40 || Board[8-linhadireitacima][colunadireitacima-1] == 50 || Board[8-linhadireitacima][colunadireitacima-1] == 60)&&(Board[8-linhadireitabaixo][colunadireitabaixo-1] == 10 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 20 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 30 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 40 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 50 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 60))
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no centro da oitava coluna
			if ((coluna == 8)&&(linha == 2 || linha == 3 || linha == 4 || linha == 5 || linha == 6 || linha == 7))
			{
				if ((Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 10 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 20 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 30 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 40 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 50 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 60)&&(Board[8-linhaesquerdacima][colunaesquerdacima-1] == 10 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 20 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 30 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 40 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 50 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 60))
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			
			//Checa se o bispo branco está bloqueado nas quatro direções
			if ((linha == 2 || linha == 3 || linha == 4 || linha == 5 || linha == 6 || linha == 7)&&(coluna == 2 || coluna == 3 || coluna == 4 || coluna == 5 || coluna == 6 || coluna == 7))
			{
				if ((Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 10 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 20 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 30 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 40 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 50 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 60)&&(Board[8-linhaesquerdacima][colunaesquerdacima-1] == 10 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 20 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 30 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 40 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 50 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 60)&&(Board[8-linhadireitabaixo][colunadireitabaixo-1] == 10 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 20 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 30 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 40 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 50 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 60)&&(Board[8-linhadireitacima][colunadireitacima-1] == 10 || Board[8-linhadireitacima][colunadireitacima-1] == 20 || Board[8-linhadireitacima][colunadireitacima-1] == 30 || Board[8-linhadireitacima][colunadireitacima-1] == 40 || Board[8-linhadireitacima][colunadireitacima-1] == 50 || Board[8-linhadireitacima][colunadireitacima-1] == 60))
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
				
		}
		else
		//Checa se foi selecionado um bispo preto
		if (Board[8-linha][coluna-1] == 21)
		{
			
			//Checa se o bispo branco está bloqueado no centro da primeira linha
			if ((linha == 1)&&(coluna == 2 || coluna == 3 || coluna == 4 || coluna == 5 || coluna == 6 || coluna == 7))
			{
				if ((Board[8-linhaesquerdacima][colunaesquerdacima-1] == 11 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 21 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 31 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 41 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 51 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 61)&&(Board[8-linhadireitacima][colunadireitacima-1] == 11 || Board[8-linhadireitacima][colunadireitacima-1] == 21 || Board[8-linhadireitacima][colunadireitacima-1] == 31 || Board[8-linhadireitacima][colunadireitacima-1] == 41 || Board[8-linhadireitacima][colunadireitacima-1] == 51 || Board[8-linhadireitacima][colunadireitacima-1] == 61))
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no canto esquerdo da primeira linha
			if ((linha == 1)&&(coluna == 1))
			{
				if (Board[8-linhadireitacima][colunadireitacima-1] == 11 || Board[8-linhadireitacima][colunadireitacima-1] == 21 || Board[8-linhadireitacima][colunadireitacima-1] == 31 || Board[8-linhadireitacima][colunadireitacima-1] == 41 || Board[8-linhadireitacima][colunadireitacima-1] == 51 || Board[8-linhadireitacima][colunadireitacima-1] == 61)
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no canto direito da primeira linha
			if ((linha == 1)&&(coluna == 8))
			{
				if (Board[8-linhaesquerdacima][colunaesquerdacima-1] == 11 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 21 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 31 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 41 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 51 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 61)
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no centro da oitava linha
			if ((linha == 8)&&(coluna == 2 || coluna == 3 || coluna == 4 || coluna == 5 || coluna == 6 || coluna == 7))
			{
				if ((Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 11 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 21 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 31 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 41 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 51 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 61)&&(Board[8-linhadireitabaixo][colunadireitabaixo-1] == 11 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 21 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 31 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 41 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 51 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 61))
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no canto esquerdo da oitava linha
			if ((linha == 8)&&(coluna == 1))
			{
				if (Board[8-linhadireitabaixo][colunadireitabaixo-1] == 11 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 21 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 31 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 41 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 51 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 61)
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no canto direito da oitava linha
			if ((linha == 8)&&(coluna == 8))
			{
				if (Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 11 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 21 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 31 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 41 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 51 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 61)
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no centro da primeira coluna
			if ((coluna == 1)&&(linha == 2 || linha == 3 || linha == 4 || linha == 5 || linha == 6 || linha == 7))
			{
				if ((Board[8-linhadireitacima][colunadireitacima-1] == 11 || Board[8-linhadireitacima][colunadireitacima-1] == 21 || Board[8-linhadireitacima][colunadireitacima-1] == 31 || Board[8-linhadireitacima][colunadireitacima-1] == 41 || Board[8-linhadireitacima][colunadireitacima-1] == 51 || Board[8-linhadireitacima][colunadireitacima-1] == 61)&&(Board[8-linhadireitabaixo][colunadireitabaixo-1] == 11 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 21 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 31 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 41 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 51 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 61))
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			//Checa se o bispo branco está bloqueado no centro da oitava coluna
			if ((coluna == 8)&&(linha == 2 || linha == 3 || linha == 4 || linha == 5 || linha == 6 || linha == 7))
			{
				if ((Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 11 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 21 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 31 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 41 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 51 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 61)&&(Board[8-linhaesquerdacima][colunaesquerdacima-1] == 11 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 21 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 31 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 41 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 51 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 61))
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
			
			//Checa se o bispo branco está bloqueado nas quatro direções
			if ((linha == 2 || linha == 3 || linha == 4 || linha == 5 || linha == 6 || linha == 7)&&(coluna == 2 || coluna == 3 || coluna == 4 || coluna == 5 || coluna == 6 || coluna == 7))
			{
				if ((Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 11 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 21 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 31 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 41 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 51 || Board[8-linhaesquerdabaixo][colunaesquerdabaixo-1] == 61)&&(Board[8-linhaesquerdacima][colunaesquerdacima-1] == 11 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 21 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 31 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 41 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 51 || Board[8-linhaesquerdacima][colunaesquerdacima-1] == 61)&&(Board[8-linhadireitabaixo][colunadireitabaixo-1] == 11 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 21 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 31 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 41 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 51 || Board[8-linhadireitabaixo][colunadireitabaixo-1] == 61)&&(Board[8-linhadireitacima][colunadireitacima-1] == 11 || Board[8-linhadireitacima][colunadireitacima-1] == 21 || Board[8-linhadireitacima][colunadireitacima-1] == 31 || Board[8-linhadireitacima][colunadireitacima-1] == 41 || Board[8-linhadireitacima][colunadireitacima-1] == 51 || Board[8-linhadireitacima][colunadireitacima-1] == 61))
				{
					PrintBoard();
					normal = 1;//Definirá que não é mais uma seleção normal
					novam = 4;//Em que parte vai repetir com mensagem única
					linha = 0, coluna = 0;//Isso fará o laço repetir
				}
			}
				
		}
		else
		
		//Checa se a casa selecionada é válida:
		if((linha<0 || linha >8)||(coluna<0 || coluna>8))
		{
			PrintBoard();
			novam = 1;//Em que parte vai repetir com mensagem única
			normal = 1;//Definirá que não é mais uma seleção normal
		}
		else
		//Checa se a casa selecionada está vazia:
		if (Board[8-linha][coluna-1] == 0)
		{
			PrintBoard();
			normal = 1;//Definirá que não é mais uma seleção normal
			novam = 2;//Em que parte vai repetir com mensagem única
			linha = 0, coluna = 0;//Isso fará o laço repetir
		}
		else
		if ((linha == 0)&&(coluna >= 1 || coluna <= -1 ))
		{
			PrintBoard();
			normal = 1;//Definirá que não é mais uma seleção normal
			novam = 5;//Em que parte vai repetir com mensagem única
			linha = 0, coluna = 0;//Isso fará o laço repetir
		}
		else
		if ((coluna == 0)&&(linha >= 1 || linha <= -1 ))
		{
			PrintBoard();
			normal = 1;//Definirá que não é mais uma seleção normal
			novam = 5;//Em que parte vai repetir com mensagem única
			linha = 0, coluna = 0;//Isso fará o laço repetir
		}
		else
		//Checa se é a vez das brancas uma peça branca deve ser selecionada e vice versa:
		if (((Board[8-linha][coluna-1] % 2 == 0)&&(vez == 1))||((Board[8-linha][coluna-1] % 2 != 0)&&(vez == 0)))
		{
			PrintBoard();
			normal = 1;//Definirá que não é mais uma seleção normal
			novam = 3;//Em que parte vai repetir com mensagem única
			linha = 0, coluna = 0;//Isso fará o laço repetir
		}
		i = 0;
		j = 0;
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
			printf(" _______________________________  \n");
			printf("|                               | \n");
			printf("|                               | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        MOVIMENTAR PECA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peca   | 00 |\n");
			printf("|Digite a COLUNA da peca   | 00 |\n");
			printf("|-------------------------------|\n");
			DestLinha = getch();
			if ((DestLinha >= 48) || (DestLinha  <= 57))
			{
				DestLinha = DestLinha - 48;
			}
			if (vez == 0)
			{
				Beep(600,200);
			}
			if (vez == 1)
			{
				Beep(400,300);
			}
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("|                               | \n");
				printf("|                               | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        MOVIMENTAR PECA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peca   | 0%d |\n",DestLinha);
				printf("|Digite a COLUNA da peca   | 00 |\n");
				printf("|-------------------------------|\n");
				DestColuna = getch();
				if ((DestColuna >= 48) || (DestColuna <= 57))
				{
					DestColuna = DestColuna - 48;
				}	
				if (vez == 0)
				{
					Beep(600,200);
				}
				if (vez == 1)
				{
					Beep(400,300);
				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("|                               | \n");
					printf("|                               | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        MOVIMENTAR PECA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peca   | 0%d |\n",DestLinha);
					printf("|Digite a COLUNA da peca   | 0%d |\n",DestColuna);
					printf("|-------------------------------|\n");
					system("cls");	
					novame = 0;
					normal = 0;
					novam = 0;
		}
		
		if (novame == 1)		
		{
			printf(" _______________________________  \n");
			printf("| Sua peca nao se movimenta ai !| \n");
			printf("|   Escolha onde mover a peca   | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        MOVIMENTAR PECA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peca   | 00 |\n");
			printf("|Digite a COLUNA da peca   | 00 |\n");
			printf("|-------------------------------|\n");
			DestLinha = getch();
			if ((DestLinha >= 48) || (DestLinha  <= 57))
			{
				DestLinha = DestLinha - 48;
			}
			if (vez == 0)
			{
				Beep(600,200);
			}
			if (vez == 1)
			{
				Beep(400,300);
			}
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("| Sua peca nao se movimenta ai !| \n");
				printf("|   Escolha onde mover a peca   | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        MOVIMENTAR PECA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peca   | 0%d |\n",DestLinha);
				printf("|Digite a COLUNA da peca   | 00 |\n");
				printf("|-------------------------------|\n");
				DestColuna = getch();
				if ((DestColuna >= 48) || (DestColuna <= 57))
				{
					DestColuna = DestColuna - 48;
				}	
				if (vez == 0)
				{
					Beep(600,200);
				}
				if (vez == 1)
				{
					Beep(400,300);
				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("| Sua peca nao se movimenta ai !| \n");
					printf("|   Escolha onde mover a peca   | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        MOVIMENTAR PECA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peca   | 0%d |\n",DestLinha);
					printf("|Digite a COLUNA da peca   | 0%d |\n",DestColuna);
					printf("|-------------------------------|\n");
					system("cls");	
					normale = 0;
					novame = 0;
					normal = 0;
					novam = 0;
		}
		
		if (novame == 2)		
		{
			printf(" _______________________________  \n");
			printf("|Voce selecionou uma casa usada!| \n");
			printf("|   Escolha onde mover a peca   | \n");
			printf("|_______________________________| \n");
			printf("|                               | \n");
			printf("|        MOVIMENTAR PECA        | \n");
			printf("|_______________________________| \n");
			printf("|Digite a LINHA  da peca   | 00 |\n");
			printf("|Digite a COLUNA da peca   | 00 |\n");
			printf("|-------------------------------|\n");
			DestLinha = getch();
			if ((DestLinha >= 48) || (DestLinha  <= 57))
			{
				DestLinha = DestLinha - 48;
			}
			if (vez == 0)
			{
				Beep(600,200);
			}
			if (vez == 1)
			{
				Beep(400,300);
			}
			system("cls");
				PrintBoard();
				printf(" _______________________________  \n");
				printf("|Voce selecionou uma casa usada!| \n");
				printf("|   Escolha onde mover a peca   | \n");
				printf("|_______________________________| \n");
				printf("|                               | \n");
				printf("|        MOVIMENTAR PECA        | \n");
				printf("|_______________________________| \n");
				printf("|Digite a LINHA  da peca   | 0%d |\n",DestLinha);
				printf("|Digite a COLUNA da peca   | 00 |\n");
				printf("|-------------------------------|\n");
				DestColuna = getch();
				if ((DestColuna >= 48) || (DestColuna <= 57))
				{
					DestColuna = DestColuna - 48;
				}	
				if (vez == 0)
				{
					Beep(600,200);
				}
				if (vez == 1)
				{
					Beep(400,300);
				}
				system("cls");
					PrintBoard();
					printf(" _______________________________  \n");
					printf("|Voce selecionou uma casa usada!| \n");
					printf("|   Escolha onde mover a peca   | \n");
					printf("|_______________________________| \n");
					printf("|                               | \n");
					printf("|        MOVIMENTAR PECA        | \n");
					printf("|_______________________________| \n");
					printf("|Digite a LINHA  da peca   | 0%d |\n",DestLinha);
					printf("|Digite a COLUNA da peca   | 0%d |\n",DestColuna);
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
		printf("***Parabens!***\nSeu peao chegou ao lado oposto, em qual peca gostaria de transforma-lo?");
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
			default: { printf("\nOpcao invalinda!tente novamente!"); goto PONTO4; } break;
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
