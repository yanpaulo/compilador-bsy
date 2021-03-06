#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modelo.h"
#include "operacoes.h"

extern void yyerror(const char *s);

void adiciona_elemento_tabela(tipo t, elemento *e);
void imprime_elemento(elemento *e);

#pragma region Tabela
void inicializa_tabela()
{
    tabela_simbolos = (tabela *)calloc(1, sizeof(tabela));
}

void imprime_tabela()
{
    elemento *lista = tabela_simbolos->head;
    if (!lista)
    {
        printf("Tabela de simbolos vazia. Siacalme, vc esta muito neuvosor.\n");
        return;
    }

    imprime_elementos(lista);
}

tabela *adiciona_elementos_tabela(tipo tipo, elemento *lista)
{
    //Elemento para iteração
    elemento *e = lista;
    //Cópia da lista
    elemento *lista_copia = NULL;
    //Elemento para construção lista_copia
    elemento *var = NULL;

    do
    {
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

        elemento *novo = cria_elemento(e->nome);
        novo->tipo = tipo;
        e->tipo = e->tipo ? e->tipo : tipo;

        if (!operacao_atribuicao(novo, e))
        {
            return NULL;
        }

        if (!lista_copia)
        {
            lista_copia = var = novo;
        }
        else
        {
            var->proximo = novo;
            var = novo;
        }

        e = e->proximo;
    } while (e);

    if (tabela_simbolos->head)
    {
        e = tabela_simbolos->head;

        while (e->proximo)
        {
            e = e->proximo;
        }
        e->proximo = lista_copia;
    }
    else
    {
        tabela_simbolos->head = lista_copia;
    }
    imprime_elementos(lista_copia);

    return tabela_simbolos;
}

elemento *get_elemento_tabela(char *nome)
{
    if (tabela_simbolos)
    {
        elemento *e = tabela_simbolos->head;

        while (e)
        {
            if (!strcmp(e->nome, nome))
            {
                return e;
            }
            e = e->proximo;
        }
    }

    char str[64];
    sprintf(str, "URSO de variavel nao declarada '%s'.\n", nome);
    yyerror(str);

    return NULL;
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
            sprintf(msg, "Variavel duplicada %s.", e->nome);
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

elemento *copia_elemento(elemento *e)
{
    if (!e)
    {
        return NULL;
    }

    elemento *novo = cria_elemento(e->nome);
    novo->tipo = e->tipo;

    return operacao_atribuicao(novo, e);
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
        printf("%s(CHAR): %d (%c)", e->nome, e->valor.charValue, e->valor.charValue);
        break;

    default:
        break;
    }
}

#pragma endregion // Elemento

#pragma region Utilitários

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
