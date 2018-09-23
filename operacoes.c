#include <stdio.h>
#include <stdlib.h>
#include "suporte.h"
#include "operacoes.h"

extern void yyerror(const char *s);

#pragma region Macros

#define OPERACAO_ARITMETICA(OP)                                               \
    switch (e1->tipo)                                                         \
    {                                                                         \
    case CHAR:                                                                \
        switch (e2->tipo)                                                     \
        {                                                                     \
        case CHAR:                                                            \
            return valor_char(e1->valor.charValue OP e2->valor.charValue);    \
        case INT:                                                             \
            return valor_int(e1->valor.charValue OP e2->valor.intValue);      \
        case FLOAT:                                                           \
            return valor_float(e1->valor.charValue OP e2->valor.floatValue);  \
        }                                                                     \
                                                                              \
    case INT:                                                                 \
        switch (e2->tipo)                                                     \
        {                                                                     \
        case CHAR:                                                            \
            return valor_int(e1->valor.intValue OP e2->valor.charValue);      \
        case INT:                                                             \
            return valor_int(e1->valor.intValue OP e2->valor.intValue);       \
        case FLOAT:                                                           \
            return valor_float(e1->valor.intValue OP e2->valor.floatValue);   \
        }                                                                     \
                                                                              \
    case FLOAT:                                                               \
        switch (e2->tipo)                                                     \
        {                                                                     \
        case CHAR:                                                            \
            return valor_float(e1->valor.floatValue OP e2->valor.charValue);  \
        case INT:                                                             \
            return valor_float(e1->valor.floatValue OP e2->valor.intValue);   \
        case FLOAT:                                                           \
            return valor_float(e1->valor.floatValue OP e2->valor.floatValue); \
        }                                                                     \
    }                                                                         \
                                                                              \
    return NULL;

#define OPERACAO_LOGICA(OP)                                                   \
    switch (e1->tipo)                                                         \
    {                                                                         \
    case CHAR:                                                                \
        switch (e2->tipo)                                                     \
        {                                                                     \
        case CHAR:                                                            \
            return valor_int(e1->valor.charValue OP e2->valor.charValue);     \
        case INT:                                                             \
            return valor_int(e1->valor.charValue OP e2->valor.intValue);      \
        case FLOAT:                                                           \
            return valor_int(e1->valor.charValue OP e2->valor.floatValue);    \
        }                                                                     \
                                                                              \
    case INT:                                                                 \
        switch (e2->tipo)                                                     \
        {                                                                     \
        case CHAR:                                                            \
            return valor_int(e1->valor.intValue OP e2->valor.charValue);      \
        case INT:                                                             \
            return valor_int(e1->valor.intValue OP e2->valor.intValue);       \
        case FLOAT:                                                           \
            return valor_int(e1->valor.intValue OP e2->valor.floatValue);     \
        }                                                                     \
                                                                              \
    case FLOAT:                                                               \
        switch (e2->tipo)                                                     \
        {                                                                     \
        case CHAR:                                                            \
            return valor_float(e1->valor.floatValue OP e2->valor.charValue);  \
        case INT:                                                             \
            return valor_float(e1->valor.floatValue OP e2->valor.intValue);   \
        case FLOAT:                                                           \
            return valor_float(e1->valor.floatValue OP e2->valor.floatValue); \
        }                                                                     \
    }                                                                         \
                                                                              \
    return NULL;

#pragma endregion //Macros

elemento *operacao_soma(elemento *e1, elemento *e2)
{
    OPERACAO_ARITMETICA(+);
}

elemento *operacao_subtracao(elemento *e1, elemento *e2)
{
    OPERACAO_ARITMETICA(-);
}

elemento *operacao_multiplicacao(elemento *e1, elemento *e2)
{
    OPERACAO_ARITMETICA(*);
}

elemento *operacao_divisao(elemento *e1, elemento *e2)
{
    OPERACAO_ARITMETICA(/);
}

elemento *erro_conversao(elemento *e1, elemento *e2)
{
    char str[64];
    sprintf(str, "Nao e possivel converter implicitamente de '%s' para '%s'\n", nome_tipo(e1->tipo), nome_tipo(e2->tipo));
    yyerror(str);
    return NULL;
}

elemento *operacao_atribuicao(elemento *e1, elemento *e2)
{
    if (!e1) {
        return NULL;
    }
    if (!e1->nome) {
        char str[64];
        sprintf(str, "Tentativa de atribuicao a constante. Enlouqueceu?");
        yyerror(str);
        return NULL;
    }
    
    
    switch (e1->tipo)
    {
    case CHAR:
        switch (e2->tipo)
        {
        case CHAR:
            e1->valor.charValue = e2->valor.charValue;
            break;
        default:
            return erro_conversao(e1, e2);
        }

    case INT:
        switch (e2->tipo)
        {
        case CHAR:
            e1->valor.intValue = e2->valor.charValue;
            break;
        case INT:
            e1->valor.intValue = e2->valor.intValue;
            break;
        default:
            return erro_conversao(e1, e2);
        }

    case FLOAT:
        switch (e2->tipo)
        {
        case CHAR:
            e1->valor.floatValue = e2->valor.charValue;
            break;
        case INT:
            e1->valor.floatValue = e2->valor.intValue;
            break;
        case FLOAT:
            e1->valor.floatValue = e2->valor.floatValue;
            break;
        }
    }
    return e1;
}

elemento* operacao_atribuicao_nome(char* nome, elemento* e2)
{
    return operacao_atribuicao(get_elemento_tabela(nome), e2);
}