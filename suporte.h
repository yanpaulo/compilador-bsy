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


struct tabela
{
    elemento* head;
} tabela;

void tabela_add(tipo t, char* nome);

elemento* cria_elemento(char* nome);

elemento* cria_elemento_valor(tipo t, valor v);

elemento* valor_int(int i);


#endif