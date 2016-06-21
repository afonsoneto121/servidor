#ifndef VAGA_H
#define VAGA_H

typedef struct vaga Vaga;

Vaga* criar_vaga();
int inserir_veiculo(Vaga *vaga,char *placa, int id);
int salvar_arquivo(Vaga *v);
void carregar_arquivo(Vaga *v);
void imprimir(Vaga *v);
int retirar_veiculo(Vaga *vagas, char* v, int id);
int vagaA_cheia(Vaga *v);
int buscar(Vaga *vaga, char* v,int id);
#endif