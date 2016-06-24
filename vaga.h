#ifndef VAGA_H
#define VAGA_H

struct _veiculo
{
	char *placa;
};

typedef struct _veiculo Veiculo;
typedef struct vaga Vagas;

Vagas* criar_vaga();
Veiculo *criar_veiculo(char *placa);
int inserir_veiculo(Vagas *vagas,Veiculo veiculo, int id);
int salvar_arquivo(Vagas *v);
void carregar_arquivo(Vagas **v);
void imprimir(Vagas *v);
int retirar_veiculo(Vagas *vagas, Veiculo v, int id);
int vagaA_cheia(Vagas *v);

#endif