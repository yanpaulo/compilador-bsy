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
    CHAR=1, INT, FLOAT
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

tabela* adiciona_elementos_tabela(tipo t, elemento* e);

elemento* cria_elemento(char* nome);

elemento* adiciona_elemento(elemento* lista, elemento* e);

void imprime_elementos(elemento* lista);

void imprime_tabela_simbolos();

elemento* cria_elemento_valor(tipo t, valor v);

elemento* valor_int(int i);

elemento* valor_float(float f);

elemento* valor_char(char c);

char *nome_tipo(tipo t);

elemento* get_elemento_tabela(char* nome);

elemento* copia_elemento(elemento* e);

#endif