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
    char nome[64];
    enum tipo tipo;
    valor valor;
    struct elemento* proximo;
} elemento;


struct tabela
{
    elemento* head;
} tabela;

void tabela_add(tipo t, char* nome);


#endif