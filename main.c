//=================================INCLUDES===================================//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//==================================DEFINES===================================//
#define WIN_WIDTH 120
#define WIN_HEIGHT 30
#define WIN_CLIENT 25
#define VAZIO -1
#define NO_MATCH -2
#define EXIT_PROG exit(0)
#define EXIT_USER '0'

//================================ENUMERAÇÕES=================================//
enum{PRETA,AZUL_ESCURO,VERDE_ESCURO,AZUL_AQUA,
     VERMELHA,ROXA,LARANJA,BRANCO_SUJO,
	 CINZA,AZUL_LAVADO,VERDE_CLARO,AZUL_CIANO,
	 ROSE,MAGENTA,AMARELA,BRANCO_NEVE};

//===============================VARIÁVEIS GLOBAIS============================//
char crossWordsLetters[11][21];
char correctWords[20][24];
char questionWords[20][60];
int numCorrectWords;
char coordWords[3];
char nextStage = '0'; 
int countCorrectWords = 0;

//=========================PROTÓTIPOS DE FUNÇÕES DO GAME======================//
void GameExecute(void);

//========================PROTÓTIPOS DE FUNÇÕES AUXILIARES====================//
void posCursor(int, int);
void colorText(int, int);
void dLine(int, int, int, int, int);
void dbaseBoard(void);
void consoleColor(int);
void endCursor(void);
void dPixel(int, int, int);
void dCrossWords(int);
void loadStage(char);
void setPosCrossWords(char, char);
int matchWord(void);
void loadQuestions(void);
void errorScreen(void);

//================================FUNÇÃO MAIN=================================//
int main()
{
	        
	GameExecute();
	      	   
return 0;
}

//========================DEFINIÇÕES DAS FUNÇÕES DO GAME======================//
void GameExecute()
{	
	while(TRUE)
	{
		nextStage++;
		if(nextStage<='9')		
			loadStage(nextStage);
		dbaseBoard();
		loadQuestions();	
		dCrossWords(VAZIO);	
		while(countCorrectWords!=numCorrectWords)		
			dCrossWords(matchWord());	
	}	
}

//========================DEFINIÇÕES DAS FUNÇÕES AUXILIARES===================//
void posCursor(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);	
}

void colorText(int letra, int fundo)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(letra+(fundo*16)));	
}

void consoleColor(int color)
{
	int x,y;
	
	for(x = 0; x<WIN_WIDTH; x++)
		for(y = 0; y<WIN_HEIGHT; y++)
		{
			colorText(color,color);
			printf(" ");	
		}		
}

void dLine(int x_ini,int y_ini,int x_end, int y_end, int color)
{
	int x,y;
	
	for(x = x_ini; x<=x_end; x++)
		for(y = y_ini; y<=y_end; y++)
		{	
			posCursor(x,y);		
			colorText(color,color);
			printf(" ");
		}
}

void dbaseBoard(void)
{
	int i,k;	
	char letra='A';
		
	consoleColor(BRANCO_SUJO);
	dLine(0,0,WIN_WIDTH-1,0,AZUL_LAVADO);
	dLine(0,0,0,WIN_CLIENT,AZUL_LAVADO);
	dLine(0,WIN_CLIENT,WIN_WIDTH-1,WIN_CLIENT,AZUL_LAVADO);
	dLine(WIN_WIDTH-1,0,WIN_WIDTH-1,WIN_CLIENT,AZUL_LAVADO);
	dLine(0,2,WIN_WIDTH-1,2,AZUL_LAVADO);
	dLine(78,0,78,WIN_CLIENT,AZUL_LAVADO);
	dPixel(78,1,BRANCO_SUJO);
	
	for(i=78,k=0;i<WIN_WIDTH-1;i++)
		if(i%2!=0)
		{
			dPixel(i,2,PRETA);
			posCursor(i,2);	
			colorText(BRANCO_NEVE,VERMELHA);
			printf("%c",letra+k);
			k++;
		}			
	
	for(i=2,k=0;i<WIN_CLIENT;i++)
		if(i%2!=0)
		{
			dPixel(78,i,PRETA);	
			posCursor(78,i);
			colorText(BRANCO_NEVE,VERDE_CLARO);
			printf("%c",letra+k);
			k++;	
		}
	dLine(1,23,77,23,AZUL_LAVADO);
	posCursor(1,24);
	colorText(PRETA,BRANCO_SUJO);
	printf("DIGITE UMA PALAVRA: ");		  
	for(i=3;i<25;i++)	
		dLine(79,i,118,i,PRETA);
		
	posCursor(45,1);
	colorText(VERMELHA,BRANCO_SUJO);
	printf("PALAVRAS-CRUZADAS");
	
	posCursor(0,26);
	colorText(PRETA,BRANCO_SUJO);
	printf("DIGITE 0 PARA SAIR.");
	
	dLine(0,30,120,30,BRANCO_SUJO);		
}

void endCursor(void)
{
	posCursor(0,26);
	colorText(BRANCO_SUJO,BRANCO_SUJO);
}

void dPixel(int x, int y, int color)
{
	posCursor(x,y);
	colorText(color,color);
	printf(" ");
}

void dCrossWords(int words)
{
	
	int index,word;	
	char lin,col;
	
	
	if(words==VAZIO)
	{
		for(word=0,lin='A';word<11;word++,lin++)
		{
			for(index=1,col='A';index<20;index++,col++)
			{
				if(crossWordsLetters[word][index] != '*')
				{
					setPosCrossWords(lin,col);
					colorText(BRANCO_NEVE,BRANCO_NEVE);
					printf(" ");				
				}
				else
				{
					setPosCrossWords(lin,col);
					colorText(PRETA,PRETA);
					printf(" ");						
				}						  		
			}						
		}						  		
	}
	else if(words!=NO_MATCH)
	{			
		switch(coordWords[2])
		{			
				
			case 'D':
				for(index=5;correctWords[words][index] != '\0';index++)
				{
					setPosCrossWords(coordWords[0],coordWords[1]);
					colorText(PRETA,BRANCO_NEVE);
					printf("%c",correctWords[words][index]);
					coordWords[1]++;
				}										
			break;
			case 'E':
				for(index=5;correctWords[words][index] != '\0';index++)
				{
					setPosCrossWords(coordWords[0],coordWords[1]);
					colorText(PRETA,BRANCO_NEVE);
					printf("%c",correctWords[words][index]);
					coordWords[1]--;
				}
			break;
			case 'C':
				for(index=5;correctWords[words][index] != '\0';index++)
				{
					setPosCrossWords(coordWords[0],coordWords[1]);
					colorText(PRETA,BRANCO_NEVE);
					printf("%c",correctWords[words][index]);
					coordWords[0]--;
				}
			break;
			case 'B':
				for(index=5;correctWords[words][index] != '\0';index++)
				{
					setPosCrossWords(coordWords[0],coordWords[1]);
					colorText(PRETA,BRANCO_NEVE);
					printf("%c",correctWords[words][index]);
					coordWords[0]++;
				}
			break;
		}  	
	}
	posCursor(20,24);
	colorText(PRETA,BRANCO_SUJO);
}

void setPosCrossWords(char linha, char coluna)
{
	int x,y;
	
	if(linha > 'Z')
		linha -= 32;
	if(coluna > 'Z')
		coluna -= 32;
	char cLin,cCol;
	for(x=79,cCol='A'; x <= 118; x+=2,cCol++)
		for(y=3,cLin='A'; y <= WIN_CLIENT; y+=2,cLin++)
			if(linha == cLin && coluna == cCol)
				posCursor(x,y);	   	
}

void loadStage(char numStage)
{
	char stage[] = "stagex.txt";
	int index,word;
	char carac[60];
	BOOLEAN read=TRUE;
	numCorrectWords = 0;
	stage[5] = numStage;	
	
	FILE *arq_stage = fopen(stage,"r");
	if(arq_stage == NULL)
	{
		errorScreen();
		exit(0);	
	}
	while(read == TRUE)
	{			
		fscanf(arq_stage,"%s",carac);
		switch(carac[0])
		{
			case '3':
				for(index=0; carac[index]!='\0' ; index++)
					crossWordsLetters[word][index] = carac[index];
			break;
			case '2':
				for(index=0; carac[index]!='\0'; index++)
					correctWords[word][index] = carac[index];
				numCorrectWords++;
			break;
			case '1':
				for(index=0; carac[index]!='\0'; index++)
					questionWords[word][index] = carac[index];
			break;
			case '5':
				word=-1;
			break;
		
			default:
				fclose(arq_stage);
				read=FALSE;			
		}	
		word++;
	}
}

int matchWord()
{
	int iDigi,iWord,nWord=0;	
	boolean match=FALSE;
	char digiWord[22];
	
	scanf("%s",digiWord);
	if(digiWord[0]==EXIT_USER)
	{
		posCursor(0,27);
		EXIT_PROG;
	}
		
	for(iDigi=0;digiWord[iDigi] != '\0';iDigi++)
		if(digiWord[iDigi]>='a' && digiWord[iDigi]<='z')
			digiWord[iDigi] -= 32;
	dLine(20,24,77,24,BRANCO_SUJO);
	do 
	{
		iWord=5;
		iDigi=0;
		while(correctWords[nWord][iWord] != '\0')		
			iWord++;
		while(*(digiWord+iDigi) != '\0' )
			iDigi++;
		if(iDigi==iWord-5)
		{
			int index;
			for(index=0; index<iDigi; index++)			
				if(*(digiWord+index) == correctWords[nWord][index+5])					
        			match=TRUE;
				else
				{
					match=FALSE;
					break;	
				}		  	
		}
		else		
			match=FALSE;
				
		nWord++;						
	}while(nWord<24 && match==FALSE);
	
	if(match==TRUE)
	{
		nWord--;
		coordWords[0] = correctWords[nWord][1];	
		coordWords[1] = correctWords[nWord][2];	
		coordWords[2] = correctWords[nWord][3];
		countCorrectWords++;		
	}
	else
		nWord = NO_MATCH;
	return nWord;				
}

void loadQuestions()
{
	int question,carac;	
	
	for(question=0;question<numCorrectWords;question++)
	{
		posCursor(1,3+question);
		for(carac=1;questionWords[question][carac] != '\0';carac++)
		{
			if(carac==1)
				colorText(BRANCO_NEVE,VERDE_CLARO);
			else if(carac==2)
				colorText(BRANCO_NEVE,VERMELHA);			
			else 
			{
				colorText(PRETA,BRANCO_SUJO);
				if(questionWords[question][carac] == '-')
					  questionWords[question][carac] = ' '; 	
			}
				
			printf("%c",questionWords[question][carac]);	
		}				
	}		
}
void errorScreen()
{
	consoleColor(BRANCO_SUJO);
	dLine(0,0,WIN_WIDTH-1,0,AZUL_LAVADO);
	dLine(0,0,0,WIN_CLIENT,AZUL_LAVADO);
	dLine(0,WIN_CLIENT,WIN_WIDTH-1,WIN_CLIENT,AZUL_LAVADO);
	dLine(WIN_WIDTH-1,0,WIN_WIDTH-1,WIN_CLIENT,AZUL_LAVADO);
	posCursor(41,12);
	colorText(VERMELHA,BRANCO_NEVE);
	printf("NAO FOI POSSIVEL ENCONTRAR O ARQUIVO!");
	posCursor(0,25);
	colorText(BRANCO_SUJO,BRANCO_SUJO);	
}
//=======================================FIM==================================//






































