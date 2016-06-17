#ifndef VAGA_H
#define VAGA_H

typedef struct _veiculo Veiculo;
typedef struct vaga Vagas;

Vagas* criar_vaga();
Veiculo *criar_veiculo(char *placa);
int inserir_veiculo(Vagas *vagas,Veiculo veiculo, int id);
int salvar_arquivo(Vagas *v);
Vagas* carregar_arquivo();
void imprimir(Vagas *v);
int retirar_veiculo(Vagas *vagas, Veiculo v, int id);
int vagaA_cheia(Vagas *v);

#endif