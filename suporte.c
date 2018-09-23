#include <stdio.h>
#include <stdlib.h>
#include "suporte.h"

void tabela_add(tipo t, char* nome)
{
    printf("Adicionado %s: %d (mentira)\n");
}

elemento* cria_elemento(char* nome)
{
    elemento* e = (elemento*)malloc(sizeof(elemento));
    e->nome = nome;
    return e;
}

elemento* cria_elemento_valor(tipo t, valor v)
{
    elemento* e = (elemento*)malloc(sizeof(elemento));
    e->tipo = t;
    e->valor = v;
    return e;
}

elemento* valor_int(int i)
{
    valor v;
    v.intValue = i;
    return cria_elemento_valor(INT, v);
}