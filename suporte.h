#ifndef SUPORTE_H
#define SUPORTE_H

typedef union valor
{
    char charValue;
    int intValue;
    float floatValue;

} valor;

typedef enum tipo
{
    CHAR, INT, FLOAT
} tipo;


typedef struct elemento
{
    char* nome;
    tipo tipo;
    valor valor;
    struct elemento* proximo;
} elemento;


typedef struct tabela
{
    elemento* head;
} tabela;

tabela* tabela_simbolos;

void inicializa_tabela();

void adiciona_elementos_tabela(tipo t, elemento* e);

elemento* cria_elemento(char* nome);

elemento* adiciona_elemento(elemento* lista, elemento* e);

void imprime_elementos(elemento* lista);

elemento* cria_elemento_valor(tipo t, valor v);

elemento* valor_int(int i);


#endif