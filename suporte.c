#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suporte.h"

extern void yyerror(const char *s);

void adiciona_elemento_tabela(tipo t, elemento *e);
void imprime_elemento(elemento *e);

#pragma region Elemento
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

elemento *valor_float(float f)
{
    valor v;
    v.floatValue = f;
    return cria_elemento_valor(FLOAT, v);
}

elemento *valor_char(char c)
{
    valor v;
    v.charValue = c;
    return cria_elemento_valor(CHAR, v);
}
#pragma endregion // Elemento

#pragma region Tabela
void inicializa_tabela()
{
    tabela_simbolos = (tabela *)calloc(1, sizeof(tabela));
}

tabela *adiciona_elementos_tabela(tipo tipo, elemento *lista)
{
    elemento *e = lista;

    do
    {
        if (e->tipo != 0 && e->tipo != tipo)
        {
            char erro[128];
            sprintf(erro, "Nao e possivel converter implicitamente '%s' em '%s'.\n", nome_tipo(e->tipo), nome_tipo(tipo));
            yyerror(erro);
            return NULL;
        }
        e->tipo = tipo;

        if (tabela_simbolos->head)
        {
            elemento *t = tabela_simbolos->head;

            do
            {
                if (!strcmp(t->nome, e->nome))
                {
                    char msg[64];
                    sprintf(msg, "Variavel %s ja declarada.", e->nome);
                    yyerror(msg);
                    return NULL;
                }

                t = t->proximo;
            } while (t);
        }

        e = e->proximo;
    } while (e);

    if (tabela_simbolos->head)
    {
        elemento *l = lista;
        e = tabela_simbolos->head;

        while (e->proximo)
        {
            e = e->proximo;
        }
        e->proximo = lista;
    }
    else
    {
        tabela_simbolos->head = lista;
    }
    imprime_elementos(lista);

    return tabela_simbolos;
}

#pragma endregion //Tabela

#pragma region Lista
elemento *adiciona_elemento(elemento *lista, elemento *e)
{
    elemento *l = lista;

    do
    {
        if (l->nome != NULL && !strcmp(l->nome, e->nome))
        {
            char msg[64];
            sprintf(msg, "Variavel %s ja declarada.", e->nome);
            yyerror(msg);
            return NULL;
            return NULL;
        }

        l = l->proximo;
    } while (l);

    l = lista;

    while (l->proximo)
    {
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
#pragma endregion //Lista

#pragma region Utilitários
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

char *nome_tipo(tipo t)
{

    switch (t)
    {
    case INT:
        return "int";
        break;
    case CHAR:
        return "char";
        break;
    case FLOAT:
        return "float";
        break;
    default:
        break;
    }
}
#pragma endregion //Utilitários

elemento* get_elemento_tabela(char* nome)
{
    if (tabela_simbolos) {
        elemento* e = tabela_simbolos->head;
        
        while(e){
            if (!strcmp(e->nome, nome)) {
                return e;
            }
            e = e->proximo;
        }
    }
    
    char str[64];
    sprintf(str, "URSO de variavel nao declarada '%s'\n", nome);
    yyerror(str);

    return NULL;
}