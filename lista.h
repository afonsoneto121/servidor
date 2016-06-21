// TAD lista de inteiros
#ifndef LISTA_H
#define LISTA_H
typedef struct lista Lista;

Lista* lst_criar(void);
void lst_liberar(Lista* l);
 
Lista* lst_inserir(Lista* l, char* v);
Lista* lst_retirar(Lista* l, char* v);
 
int lst_vazia(Lista* l);
Lista* lst_buscar(Lista* l,char* v);
void lst_imprimi(Lista* l);

Lista* proximo(Lista *l);
char* placa(Lista *l);

#endif