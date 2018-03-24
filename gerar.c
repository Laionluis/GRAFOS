#include <stdio.h>
#include <string.h>

char inicial[12] = {'"','.','X','.','.','.','.','.','O','.','"','\0'};
char aux[12];
char aux1[12];

void continua_X(char v[],FILE *arq);
void continua_O(char v[],FILE *arq);
int checar_vencedor(char v[]);

void copia(char v[], char v1[])
{
	int i;
	for(i=0;i<12;i++)
	{
		v[i] = v1[i];
	}
}

int main(int argc, char const *argv[])
{
	char url[]="teste.txt";
	FILE *arq;
	arq = fopen(url, "wr");

	//fprintf(arq,"%s ->  \n", inicial);
	copia(aux,inicial);
	continua_X(inicial,arq);
	fclose(arq);
	return 0;
}

int checar_vencedor(char a[])
{
	int checar = 0;
	if ((a[1]== 'X') && (a[2]== 'X') && (a[3]=='X'))
		checar = 1;
	else if ((a[4]== 'X') && (a[5]== 'X') && (a[6]=='X'))
		checar = 1;
	else if ((a[7]== 'X') && (a[8]== 'X') && (a[9]=='X'))
		checar = 1;
	else if ((a[1]== 'X') && (a[4]== 'X') && (a[7]=='X'))
		checar = 1;
	else if ((a[2]== 'X') && (a[5]== 'X') && (a[8]=='X'))
		checar = 1;
	else if ((a[3]== 'X') && (a[6]== 'X') && (a[9]=='X'))
		checar = 1;
	else if ((a[1]== 'X') && (a[5]== 'X') && (a[9]=='X'))
		checar = 1;
	else if ((a[3]== 'X') && (a[5]== 'X') && (a[7]=='X'))
		checar = 1;
	else if ((a[1]== 'O') && (a[2]== 'O') && (a[3]=='O'))
		checar = 1;
	else if ((a[4]== 'O') && (a[5]== 'O') && (a[6]=='O'))
		checar = 1;
	else if ((a[7]== 'O') && (a[8]== 'O') && (a[9]=='O'))
		checar = 1;
	else if ((a[1]== 'O') && (a[4]== 'O') && (a[7]=='O'))
		checar = 1;
	else if ((a[2]== 'O') && (a[5]== 'O') && (a[8]=='O'))
		checar = 1;
	else if ((a[3]== 'O') && (a[6]== 'O') && (a[9]=='O'))
		checar = 1;
	else if ((a[1]== 'O') && (a[5]== 'O') && (a[9]=='O'))
		checar = 1;
	else if ((a[3]== 'O') && (a[5]== 'O') && (a[7]=='O'))
		checar = 1;
	return checar; 
}

void continua_O(char v[],FILE *arq)
{
	char v1[12];
	int i;
	for(i=1;i<10;i++)  // faz para as primeiras configuracoes
	{
		copia(v1,v);
		if(v[i]=='.')
		{
			fprintf(arq,"%s -> ", v);
			v1[i] = 'O';			
			fprintf(arq,"%s \n",v1 );
			copia(aux,v1);
			if(checar_vencedor(v1) == 0) // se alguem ganhou acabou o jogo
			{
				//chama funcao que vai fazer o resto das possibilidades para essa configuracao
				continua_X(v1,arq);
			}			
		}
	}
}

void continua_X(char v[],FILE *arq)
{
	char v1[12];
	int i;
	for(i=1;i<10;i++)  // faz para as primeiras configuracoes
	{
		copia(v1,v);
		if(v[i]=='.')
		{
			fprintf(arq,"%s -> ", v);
			v1[i] = 'X';			
			fprintf(arq,"%s \n",v1);
			copia(aux,v1);
			if(checar_vencedor(v1) == 0) //se alguem ganhou acabou o jogo
			{
				//chama funcao que vai fazer o resto das possibilidades para essa configuracao
				continua_O(v1,arq);		
			}		
		}
	}
}
