#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "vaga.h"

struct vaga
{
	int qtdA;
	int qtdB;
	int qtdC;
	Lista *setorA;	
	Lista *setorB;
	Lista *setorC;
};

Vaga* criar_vaga()
{
	Vaga *nova = (Vaga*) malloc(sizeof(Vaga));

	nova->qtdA=0;
	nova->qtdB=0;
	nova->qtdC=0;
	nova->setorA = lst_criar();
	nova->setorB = lst_criar();
	nova->setorC = lst_criar();
	return nova;
}

int inserir_veiculo(Vaga *vaga,char *placa, int id)
{
	if(id == 1)
	{
		vaga->setorA = lst_inserir(vaga->setorA,placa);
		vaga->qtdA++;
		return 1;
	}
	if(id == 2)
	{
		vaga->setorB = lst_inserir(vaga->setorB,placa);	
		vaga->qtdB++;
		return 1;
	}
	if(id == 3)
	{	
		vaga->setorC = lst_inserir(vaga->setorC,placa);
		vaga->qtdC++;
		return 1;
	}
	return -1;
}

int retirar_veiculo(Vaga *vaga, char *placa, int id)
{

	if(id == 1)
	{
		vaga->setorA = lst_retirar(vaga->setorA,placa);
		vaga->qtdA--;
		return 1;
	}
	if(id == 2)
	{
		vaga->setorB = lst_retirar(vaga->setorB,placa);	
		vaga->qtdB--;
		return 1;
	}
	if(id == 3)
	{	
		vaga->setorC = lst_retirar(vaga->setorC,placa);
		vaga->qtdC--;
		return 1;
	}
	return -1;
}

int buscar(Vaga *vaga, char* placa,int id)
{
	Lista *l;
	if(id == 1)
	{
		 l = lst_buscar(vaga->setorA,placa);
		return l == NULL;
	}
	if(id == 2)
	{
		l = lst_buscar(vaga->setorB,placa);	
		return l == NULL;
	}
	if(id == 3)
	{	
		l = lst_buscar(vaga->setorC,placa);
		return l == NULL;
	}
	return -1;
}

int salvar_arquivo(Vaga *v)
{
	Lista *l;
	int i;
	FILE *p = fopen("banco","w");
	if(p != NULL)
	{
		l = v->setorA;
	
		fprintf(p, "A: ");
		for (l = v->setorA ; l != NULL ; l = proximo(l))
		{
			char *pl = placa(l);
			fprintf(p, "%s,", pl);
		}
		fseek(p, -1,SEEK_CUR);
		fprintf(p, "$\n");
		
		fprintf(p, "B: ");
		for (l = v->setorB; l != NULL ; l = l = proximo(l))
		{
			char *pl = placa(l);
			fprintf(p, "%s,", pl);
		}
		fseek(p, -1,SEEK_CUR);
		fprintf(p, "$\n");
		

		fprintf(p, "C: ");
		for (l = v->setorC; l != NULL ; l = proximo(l))
		{
			char *pl = placa(l);
			fprintf(p, "%s,", pl);
		}
		fseek(p, -1,SEEK_CUR);
		fprintf(p, "$\n");
	
		fclose(p);
		return 1;
	}
	return -1;
}
void imprimir(Vaga *v)
{
	Lista *l;
	printf("A:\n");
	for (l = v->setorA ; l != NULL ; l = proximo(l))
	{
		char *pl = placa(l);
		printf("%s,", pl);
	}
	
	printf("\nB:\n");
	for (l = v->setorB ; l != NULL ; l = proximo(l))
	{
		char *pl = placa(l);
		printf("%s,", pl);
	}
	printf("\nC:\n");
	for (l = v->setorC ; l != NULL ; l = proximo(l))
	{
		char *pl = placa(l);
		printf("%s,", pl);
	}
}
void carregar_arquivo(Vaga *v)
{
	FILE *p = fopen("banco", "r");
	char *placa = (char*) malloc(7 *sizeof(char));
	char *cursor = (char*) malloc(2 *sizeof(char));
	char c;
	if(p != NULL)	
	{	
		fread (cursor,sizeof(char), 2, p);
		if(strcmp(cursor,"A:") == 0)
		{
			while ((c = fgetc(p)) != '$')
			{	
				fread (placa,sizeof(char), 7, p);		
				char *s = placa;
				int id = inserir_veiculo(v,s,1);
				
			}
				
		}
		
		fseek(p, 1,SEEK_CUR);
		fread (cursor,sizeof(char), 2, p);
		
		if(strcmp(cursor,"B:") == 0)
		{
			
			while ((c = fgetc(p)) != '$')
			{
				fread (placa,sizeof(char), 7, p);		
				char *s = placa; //printf("%s\n", s);
				inserir_veiculo(v,s,2);
			}
		}
		fseek(p, 1,SEEK_CUR);
		fread (cursor,sizeof(char), 2, p);

		if(strcmp(cursor,"C:") == 0)
		{
			
			while ((c = fgetc(p)) != '$')
			{
				fread (placa,sizeof(char), 7, p);			
				char *s = placa;
				//printf("%s\n", s);
				inserir_veiculo(v,s,3);
			}
			
		}
		fclose(p);
		
	}
}

int main(int argc, char const *argv[])
{
	Vaga* v = criar_vaga();
	carregar_arquivo(v);
	inserir_veiculo(v,"AFONSON",2);
	inserir_veiculo(v,"12TESTE",3);
	salvar_arquivo(v);
	//imprimir(v);
	/*
	inserir_veiculo(v,"234567A",1);
	inserir_veiculo(v,"ASDFGHJ",1);
	inserir_veiculo(v,"ZXCVBNM",2);
	inserir_veiculo(v,"QWERTYU",3);
	inserir_veiculo(v,"QWERTYU",3);
	inserir_veiculo(v,"QWERTYU",3);
	inserir_veiculo(v,"QWERTYU",3);
	inserir_veiculo(v,"234567A",3);
	inserir_veiculo(v,"QWERTYU",1);

	salvar_arquivo(v);
	*/
	return 0;
}
