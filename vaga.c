#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "vaga.h"

#define TAM_A 100
#define TAM_B 40
#define TAM_C 50
#define TAM_D 30

/*
struct _veiculo
{
	char *placa;
};
*/
//typedef struct veiculo Veiculo;

struct vaga
{
	int qtdA;
	Veiculo setorA[TAM_A];  //Carros
	int qtdB;
	Veiculo setorB[TAM_B];	//Caminhão
	int qtdC;
	Veiculo setorC[TAM_C];	//Carros
	int qtdD;
	Veiculo setorD[TAM_D];	//Motos

};

//typedef struct vaga Vagas;

Vagas* criar_vaga()
{
	Vagas *nova = (Vagas*) malloc(sizeof(Vagas));
	nova->qtdA = 0;
	nova->qtdB = 0;
	nova->qtdC = 0;
	nova->qtdD = 0;
	return nova;	
}

int salvar_arquivo(Vagas *v)
{
	FILE *p = fopen("banco","w");
	int i;
	Veiculo veiculo;
	if(p == NULL)
	{ 
		printf("ERRO\n");
	}
	else
	{
		fprintf(p, "A: ");
		if(v->qtdA > 0)
		{
			for (i = 0; i < v->qtdA-1; i++)
			{
				veiculo =  v->setorA[i];
				fprintf(p, "%s,", v->setorA[i].placa);
			}
			fprintf(p, "%s$",v->setorA[v->qtdA-1].placa);
		}

		fprintf(p, "\n");

		fprintf(p, "B: ");
		if(v->qtdB > 0)
		{
			for (i = 0; i < v->qtdB-1; i++)
			{
				veiculo =  v->setorB[i];
				fprintf(p, "%s,", v->setorB[i].placa);
			}
			fprintf(p, "%s$",v->setorB[v->qtdB-1].placa);
		}
		
		fprintf(p, "\n");

		fprintf(p, "C: ");
		if(v->qtdC > 0)
		{
			for (i = 0; i < v->qtdC-1; i++)
			{
				veiculo =  v->setorC[i];
				fprintf(p, "%s,", v->setorC[i].placa);
			}
			fprintf(p, "%s$",v->setorC[v->qtdC-1].placa);
		}
		
		fprintf(p, "\n");

		fprintf(p, "D: ");
		if(v->qtdD > 0)
		{
			for (i = 0; i < v->qtdD-1; i++)
			{
				veiculo =  v->setorD[i];
				fprintf(p, "%s,", v->setorD[i].placa);
			}
			fprintf(p, "%s$",v->setorD[v->qtdD-1].placa);
		}
		



		fclose(p);
		return 1;
	}
	return -1;
}

void carregar_arquivo(Vagas *vagas)
{
	FILE *p = fopen("banco", "r");
	//Vagas *vagas = (Vagas*)	malloc(sizeof(Vagas));
	char *placa = (char*) malloc(7 *sizeof(char));
	char *cursor = (char*) malloc(2 *sizeof(char));
	char c;
	if(p != NULL)	
	{	
		while(!feof(p))
		{
			fread (cursor,sizeof(char), 2, p);
			if(strcmp(cursor,"A:") == 0)
			{
				
				while ((c = fgetc(p)) != '$')
				{
					Veiculo veiculo;	
					fread (placa,sizeof(char), 7, p);		
					//printf("SetorA: %s\n", placa);
					veiculo.placa = placa;
					inserir_veiculo(vagas,veiculo,1);
				}
				//printf("saiu\n");
			}
			fseek(p, 1,SEEK_CUR);
			fread (cursor,sizeof(char), 2, p);
			if(strcmp(cursor,"B:") == 0)
			{
				
				while ((c = fgetc(p)) != '$')
				{
					Veiculo veiculo;
					//fseek(p, -1,SEEK_CUR);
					fread (placa,sizeof(char), 7, p);		
					//printf("SetorB: %s\n", placa);
					veiculo.placa = placa;
					inserir_veiculo(vagas,veiculo,2);
				}
				//printf("saiu\n");
			}
			fseek(p, 1,SEEK_CUR);
			fread (cursor,sizeof(char), 2, p);
			if(strcmp(cursor,"C:") == 0)
			{
				
				while ((c = fgetc(p)) != '$')
				{
					Veiculo veiculo;
					//fseek(p, -1,SEEK_CUR);
					fread (placa,sizeof(char), 7, p);		
					//printf("SetorC: %s\n", placa);
					veiculo.placa = placa;
					inserir_veiculo(vagas,veiculo,3);
				}
				//printf("saiu\n");
			}
			fseek(p, 1,SEEK_CUR);
			fread (cursor,sizeof(char), 2, p);
			if(strcmp(cursor,"D:") == 0)
			{

				while ((c = fgetc(p)) != '$')
				{
					Veiculo veiculo;
					//fseek(p, -1,SEEK_CUR);
					fread (placa,sizeof(char), 7, p);		
					//printf("SetorD: %s\n", placa);
					veiculo.placa = placa;
					inserir_veiculo(vagas,veiculo,4);
				}
				//printf("saiu\n");
			}
			break;
		}
		fclose(p);
		//return vagas;
	}
	//return NULL;
}

int inserir_veiculo(Vagas *vagas,Veiculo v, int id)
{
	int i;
	if(id == 1)
	{
		if(vagas->qtdA < TAM_A)
		{			
			for (i = 0; i < vagas->qtdA; ++i)
			{
				if(strcmp(vagas->setorA[i].placa,"vazio") == 0)
				{
					vagas->setorA[i] = v;
					return 1;
				}
			}
			
			vagas->setorA[vagas->qtdA] = v;
			vagas->qtdA++;
			return 1;
		}
		else return -1;
	}
	if(id == 2)
	{
		if(vagas->qtdB < TAM_B)
		{
			for (i = 0; i < vagas->qtdB; ++i)
			{
				if(strcmp(vagas->setorB[i].placa,"vazio") == 0)
				{
					vagas->setorB[i] = v;
					return 1;
				}
			}
			
			vagas->setorB[vagas->qtdB] = v;
			vagas->qtdB++;
			return 1;
		}
		else return -1;
	}
	if(id == 3)
	{
		if(vagas->qtdC < TAM_C)
		{
			for (i = 0; i < vagas->qtdC; ++i)
			{
				if(strcmp(vagas->setorC[i].placa,"vazio") == 0)
				{
					vagas->setorC[i] = v;
					return 1;
				}
			}
			
			vagas->setorC[vagas->qtdC] = v;
			vagas->qtdC++;
			return 1;
		}
		else return -1;
	}
	if(id == 4)
	{
		if(vagas->qtdD < TAM_D)
		{
			for (i = 0; i < vagas->qtdD; ++i)
			{
				if(strcmp(vagas->setorD[i].placa,"vazio") == 0)
				{
					vagas->setorD[i] = v;
					return 1;
				}
			}
			
			vagas->setorD[vagas->qtdD] = v;
			vagas->qtdD++;
			return 1;
		}
		else return -1;
	}
	return -1; //id invalido
}
void imprimir(Vagas *v)
{
	int i;
	printf("Setor A:\n");
	Veiculo carro;
	for (i = 0; i < v->qtdA; i++)
	{
		carro = v->setorA[i];
		printf("%s, ", carro.placa);
	}
	printf("\nSetor B:\n");

	for (i = 0; i < v->qtdB; i++)
	{
		carro = v->setorB[i];
		printf("%s,", carro.placa);
	}
	printf("\nSetor C:\n");

	for (i = 0; i < v->qtdC; i++)
	{
		carro = v->setorC[i];
		printf("%s, ", carro.placa);
	}
	printf("\nSetor D:\n");
	
	for (i = 0; i < v->qtdD; i++)
	{
		carro = v->setorD[i];
		printf("%s, ", carro.placa);
	}
}
int retirar_veiculo(Vagas *vagas, Veiculo v, int id)
{
	int i;
	
	if(id == 1)
	{
		for (i = 0; i < vagas->qtdA; i++)
		{
			if(strcmp(vagas->setorA[i].placa, v.placa) == 0)
			{
				vagas->setorA[i].placa = "vazio";
				return 1;
			}
		}
		return -1;
	}
	
	if(id == 2)
	{
		for (i = 0; i < vagas->qtdB; i++)
		{
			if(strcmp(vagas->setorB[i].placa,v.placa) == 0)
			{
				vagas->setorB[i].placa = "vazio";
				return 1;
			}
		}
		return -1;
	}
	if(id == 3)
	{
	
		for (i = 0; i < vagas->qtdC; ++i)
		{
			if(strcmp(vagas->setorC[i].placa,v.placa) == 0)
			{
				vagas->setorC[i].placa = "vazio";
				return 1;
			}
		}
		return -1;
	
		
	}
	if(id == 4)
	{
		for (i = 0; i < vagas->qtdD; ++i)
		{
			if(strcmp(vagas->setorD[i].placa,v.placa) == 0)
			{
				vagas->setorD[i].placa = "vazio";
				return 1;
			}
		}
		return -1;			
	}
	return -1;	
}
int vagaA_cheia(Vagas *v)
{
	return v->qtdA == TAM_A;
}
Veiculo* criar_veiculo(char *placa)
{
	Veiculo *novo = (Veiculo*) malloc(sizeof(Veiculo));
	novo->placa = placa;
	return novo;
}
/*
int main(int argc, char const *argv[])
{
	Vagas *c = carregar_arquivo();
	imprimir(c);
	return 0;
}
*/