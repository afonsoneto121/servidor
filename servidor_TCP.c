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
#include "Vaga/vaga.h"



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
	int cont = 0;
	
	/*
	Vaga *v = criar_vaga();
	carregar_arquivo(v);
	inserir_veiculo(v,"dlc1235",3);
	inserir_veiculo(v,"dlc1235",1);
	inserir_veiculo(v,"dlc1235",2);
	//imprimir(v);
	salvar_arquivo(v);
	//imprimir(v);
	*/
	while(controla_loop)
	{			
		int cl = espera_cliente(&Novosocket,Meusocket,(struct sockaddr *)&endereco_dele);		
		if(cl == 1)
		{	
			cont++;
			pid_t pid = fork();	
			
			if (pid == -1) 
			{
				perror("fork");
				exit(1);
			}

			if(pid == 0)	
			{
				Vaga *v = criar_vaga();
				carregar_arquivo(v);
				int id = 0;
				while(1)
				{	
					if ((numbytes=recv(Novosocket, buf, 100, 0)) == -1) 
					{	
						perror("recv");
						exit(1);
					}
					buf[numbytes] = '\0';
					
					if(numbytes > 0)
					{
						FILE *log =fopen("log","a");
						fprintf(log, "Mensagem de Cliente %d: %s \n",cont, buf);
						fclose(log);					
				
						char tipo = buf[numbytes-1];
						buf[numbytes-1] = '\0';
						char *placa = (char*) malloc(7 * sizeof(char));
						char *enviar = (char*) malloc(7 * sizeof(char));
						int j;
				
						for (j = 0; j < 7; j++)
						{
							enviar[j] = buf[j];
						}

						if(tipo == 'A')
						{
							//Inserir
							id = 1 + rand() % 3;
							int c = inserir_veiculo(v,enviar, id);
							FILE *log = fopen("log","a");
							fprintf(log, "Veiculo Inserido, %s \n",enviar);
							fprintf(log, "id e c , %d %d \n",id,c);
							fclose(log);	
							salvar_arquivo(v);	
						}

						if(tipo == 'B')
						{
							//Pesquisa
							FILE *log = fopen("log","a");
							fprintf(log, "Pesquisa Solicitado %s \n",enviar );
							

							int c = buscar(v, enviar,1);
							int d = buscar(v, enviar,2);
							int e = buscar(v, enviar,3);
							fprintf(log, "Dados %d %d %d \n",c,d,e);
							fclose(log);
							if(c == 1 || d == 1 || e == 1)
							{
					    		FILE *log = fopen("log","a");
								fprintf(log, "Veiculo encontrado %s \n",enviar );
								fclose(log);
								if (send(Novosocket, "OK", 2, 0) < 0)
					    		{
					        		perror("send:");
					        		return 0;
					    		}
					    		
					    	}
					    	else
					    	{
				    			if (send(Novosocket, "ER", 2, 0) < 0)
					    		{
					        		perror("send:");
					        		return 0;
					    		}
					    	}
						}
						
						if(tipo == 'C')
						{
							//Excluir

							FILE *log = fopen("log","a");
							fprintf(log, "Excluir %s \n",buf);
							fclose(log);
							
							int c = retirar_veiculo(v, enviar, 1);
							int d = retirar_veiculo(v, enviar, 2);
							int e = retirar_veiculo(v, enviar, 3);
							
							salvar_arquivo(v);
							
							if (send(Novosocket, "OK", 2, 0) < 0)
				    		{
				        		perror("send:");
				        		return 0;
				    		}
						}
						//numbytes = 0;
					} //Num Bytes > 0
				}
			}

		}		
		//while(waitpid(-1,NULL,WNOHANG) > 0); /* Limpa o processo crianca.fork() */						
		//controla_loop = 0;
	}	
}	
