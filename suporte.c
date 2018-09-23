#include <stdio.h>
#include <stdlib.h>
#include "suporte.h"

void adiciona_elemento_tabela(tipo t, elemento *e);
void imprime_elemento(elemento *e);

void tabela_add(tipo t, char *nome)
{
    printf("Adicionado %s: %d (mentira)\n");
}

elemento *cria_elemento(char *nome)
{
    elemento *e = (elemento *)calloc(1, sizeof(elemento));
    e->nome = nome;
    return e;
}

elemento *cria_elemento_valor(tipo t, valor v)
{
    elemento *e = (elemento *)calloc(1, sizeof(elemento));
    e->tipo = t;
    e->valor = v;
    return e;
}

elemento *valor_int(int i)
{
    valor v;
    v.intValue = i;
    return cria_elemento_valor(INT, v);
}

elemento* valor_float(float f)
{
    valor v;
    v.floatValue = f;
    return cria_elemento_valor(FLOAT, v);
}

elemento* valor_char(char c)
{
    valor v;
    v.charValue = c;
    return cria_elemento_valor(CHAR, v);
}

void inicializa_tabela()
{
    tabela_simbolos = (tabela *)calloc(1, sizeof(tabela));
}



void adiciona_elementos_tabela(tipo t, elemento *lista)
{
    
    if (tabela_simbolos->head) {
        elemento* e = tabela_simbolos->head;
        while(e->proximo){
            e = e->proximo;
        }
        e->proximo = lista;
    }
    else
    {
        tabela_simbolos->head = lista;
    }
    printf("\n");
}

elemento *adiciona_elemento(elemento *lista, elemento *e)
{
    elemento* l = lista;
    while(l->proximo){
        l = l->proximo;
    }
    l->proximo = e;

    return lista;
}



void imprime_elementos(elemento *lista)
{
    elemento *e = lista;
    do
    {
        imprime_elemento(e);

        if (e->proximo)
        {
            printf(", ");
        }

        e = e->proximo;
    } while (e);
    printf("\n");
}

void imprime_elemento(elemento *e)
{
    switch (e->tipo)
    {
    case INT:
        printf("%s(INT): %d", e->nome, e->valor.intValue);
        break;

    case FLOAT:
        printf("%s(FLOAT): %f", e->nome, e->valor.floatValue);
        break;

    case CHAR:
        printf("%s(CHAR): %c", e->nome, e->valor.charValue);
        break;

    default:
        break;
    }
}