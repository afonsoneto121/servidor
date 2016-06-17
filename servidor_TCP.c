#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "vaga.h"



#define MINHAPORTA 7890
#define BACKLOG 5
#define SIZEMAX 100

int espera_cliente(int *Novosocket,int Meusocket,const struct sockaddr *endereco_dele)
{
	printf("Esperando\n");
	int tamanho = sizeof(struct sockaddr_in);
	if ((*Novosocket = accept(Meusocket, (struct sockaddr *)&endereco_dele,&tamanho)) < 0){
		perror("accept");
		return 0;
	}
	else 
	{			
		printf("Pronto\n");
		FILE *log = fopen("log","a");
		fprintf(log, "Cliente Iniciado \n");
		fclose(log);
		return 1;
	}
}


int main()
{
	int Meusocket, Novosocket = -1;	  
	struct sockaddr_in meu_endereco;    
	struct sockaddr_in endereco_dele; 
	int tamanho, numbytes;
	char nova_vaga;
	FILE *log = fopen("log","a");
	if(log == NULL)
	{
		perror("arquivo");		
	}
	
	fprintf(log, "Servidor Iniciado Data :%s Hora:%s \n" ,__DATE__,__TIME__);
	char *buf = (char*) malloc (SIZEMAX * sizeof(char));

	if ((Meusocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		perror("socket");
		exit(1);
	}

	memset((char*)&meu_endereco, 0, sizeof(meu_endereco));
	meu_endereco.sin_family = AF_INET;
	meu_endereco.sin_port = htons(MINHAPORTA);
	meu_endereco.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(Meusocket, (struct sockaddr *)&meu_endereco, sizeof(struct sockaddr)) < 0) 
	{
		perror("bind");
		exit(1);
	}

	if (listen(Meusocket, BACKLOG) < 0) 
	{
		perror("listen");
		exit(1);
	}

	fprintf(log,"PORTA #%d\n",ntohs(meu_endereco.sin_port));
	fclose(log);
	int controla_loop = 1;
	/*
	tamanho = sizeof(struct sockaddr_in);
	if ((Novosocket = accept(Meusocket, (struct sockaddr *)&endereco_dele,&tamanho)) < 0){
		perror("accept");
	}
	else 
	{			
		log = fopen("log","a");
		fprintf(log, "Cliente Iniciado \n");
		fclose(log);
	}
	*/
	int status;
	int cont = 1;
	while(controla_loop)
	{			
		pid_t pid;
		int cl = espera_cliente(&Novosocket,Meusocket,(struct sockaddr *)&endereco_dele);
		if(cl == 1)
		{	
			cont++;
			pid = fork();	
			if (pid == -1) 
			{
				perror("fork");
				exit(1);
			}

			else if(pid == 0)	
			{
				Vagas *v = criar_vaga();
				v = carregar_arquivo();
				Veiculo *veiculo = criar_veiculo(buf);
				int id = 0;
				
				while(status == 1)
				{
					buf = "";
					if ((numbytes=recv(Novosocket, buf, 100, 0)) == -1) 
					{	
						perror("recv");
						exit(1);
					}
					if(numbytes > 0)
					{
						FILE *log = fopen("log","a"); 
						buf[numbytes] = '\0';
						fprintf(log,"Mensagem %d: %s ",cont,buf);
						fclose(log);
						numbytes = 0;
						if(strcmp(buf , "exit") == 0)
						{	
							FILE *log =fopen("log","a");
							fprintf(log, "Cliente %d finalizado",cont);
							fclose(log);
							salvar_arquivo(v);
							status = 0;
						}
						else
						{
							char tipo = buf[numbytes-1];
							buf[numbytes-1] = '\0';
							switch(tipo){
								case 'A': id = 1;break;
								case 'E': id = vagaA_cheia(v) == 1 ? 3 : 1; 
								//case 'B': id = 2;break;
								//case 'C': id = 3;break;
								case 'D': id = 4;break;
								default : id = 0;break;
							}
							
							//veiculo.placa = buf;
							int c; 
							c = inserir_veiculo(v,veiculo, id);

							if(c == 1)
							{
								FILE *log = fopen("log","a");
								fprintf(log, "Veiculo Inserido\n");
								fclose(log);
								if (send(Meusocket, "OK", 2, 0) < 0)
							    {
							        perror("send:");
							        return 0;
							    }
							}
							else
							{
								if (send(Meusocket, "OK", 2, 0) < 0)
							    {
							        perror("send:");
							        return 0;
							    }
							}
							salvar_arquivo(v);
						} //Mensagem != de exit
					} //Num Bytes > 0
				}
			}

			else
			{
				printf("Pai\n");
				
			}
		}		
		//while(waitpid(-1,NULL,WNOHANG) > 0); /* Limpa o processo crianca.fork() */						
		//controla_loop = 0;
	}	
}	