#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"
 
 
struct lista
{
    char *placa;
    
    struct lista* prox;

};
 
Lista* lst_criar(void)
{
    return NULL;
}

void lst_liberar(Lista* l)
{
    Lista* p = l;
    while(p != NULL)
    {
        Lista* t = p->prox;
        free(p);
        p = t;
    }
}
 
Lista* lst_inserir(Lista* l, char *v)
{
    Lista* novo = (Lista*) malloc(sizeof(Lista*));
    novo->placa = v;
    novo->prox = l;
    return novo;
}

Lista* lst_retirar(Lista* l, char *v)
{
    Lista *ant = NULL;
    Lista *p = l; // percorrer lista l
 
    while(p != NULL && strcmp(p->placa, v) != 0)
    {
        ant = p;
        p = p->prox;
    }
    if(p==NULL)
    {
        return l; // não achou o valor retorna a lista original
    }
    if(ant == NULL)
    {
        l = p->prox; // retira o elemento no inicio na lista
    }
    else
    {
        ant->prox = p->prox; // retira o elemento no meio da lista
    }
    free(p);
    return l;
}
 
int lst_vazia(Lista* l)
{
    return (l==NULL);
}
 
Lista* lst_buscar(Lista* l,char *v)
{
    Lista *p;
    for(p=l; p!=NULL; p= p->prox)
    {
        if(strcmp(p->placa, v) == 0) return p;
    }
    return NULL;
}

void lst_imprimi(Lista* l)
{
    Lista *p;
    for(p = l; p != NULL;p = p->prox)
    {
        printf("%s\n",p->placa);
    }
}

Lista *proximo(Lista *l)
{
    return l->prox;
}

char *placa(Lista *l)
{
    return l->placa;
}

/*
int main(int argc, char const *argv[])
{
    Lista *l = lst_criar();
    l = lst_inserir(l,"1234567");
    l = lst_inserir(l,"7654321");
    lst_imprimi(l);
    return 0;
}
*/

