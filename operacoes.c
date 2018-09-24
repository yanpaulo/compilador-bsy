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

elemento *operacao_ou(elemento *e1, elemento *e2)
{
    OPERACAO_LOGICA(||);
}

elemento *operacao_negacao(elemento *e1)
{
    switch (e1->tipo)
    {
    case CHAR:
        return valor_char(!e1->valor.charValue);
    case INT:
        return valor_int(!e1->valor.intValue);
    case FLOAT:
        return valor_float(!e1->valor.charValue);
    }
}

elemento *operacao_e(elemento *e1, elemento *e2)
{
    OPERACAO_LOGICA(&&);
}

elemento *operacao_exponenciacao(elemento *e1, elemento *e2)
{
    elemento *exp = cria_elemento("exp");
    exp->tipo = INT;
    exp = operacao_atribuicao(exp, e2);
    if (!exp)
    {
        return NULL;
    }

    elemento *copia = cria_elemento("e1");
    copia->tipo = e1->tipo;
    operacao_atribuicao(copia, e1);

    int n = exp->valor.intValue;
    if (n == 0) {
        copia = operacao_multiplicacao(copia, valor_char(0));
        copia = operacao_soma(copia, valor_char(1));
        return copia;
    }
    
    for (int i = 0; i < n - 1; i++)
    {
        e1 = operacao_multiplicacao(e1, copia);
    }

    return e1;
}

elemento *erro_conversao(elemento *e1, elemento *e2)
{
    char str[128];
    sprintf(str, "Nao e possivel converter implicitamente de '%s' para '%s' (tambem nao tem conversao explicita hehehehehe)\n", nome_tipo(e2->tipo), nome_tipo(e1->tipo));
    yyerror(str);
    return NULL;
}

elemento *operacao_atribuicao(elemento *e1, elemento *e2)
{
    if (!e1)
    {
        return NULL;
    }
    if (!e1->nome)
    {
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
            printf("%s = %c\n", e1->nome, e1->valor.charValue);
            return e1;
        }
        break;

    case INT:
        switch (e2->tipo)
        {
        case CHAR:
            e1->valor.intValue = e2->valor.charValue;
            printf("%s = %d\n", e1->nome, e1->valor.intValue);
            return e1;
        case INT:
            e1->valor.intValue = e2->valor.intValue;
            printf("%s = %d\n", e1->nome, e1->valor.intValue);
            return e1;
        }
        break;

    case FLOAT:
        switch (e2->tipo)
        {
        case CHAR:
            e1->valor.floatValue = e2->valor.charValue;
            printf("%s = %f\n", e1->nome, e1->valor.floatValue);
            return e1;
        case INT:
            e1->valor.floatValue = e2->valor.intValue;
            printf("%s = %f\n", e1->nome, e1->valor.floatValue);
            return e1;
        case FLOAT:
            e1->valor.floatValue = e2->valor.floatValue;
            printf("%s = %f\n", e1->nome, e1->valor.floatValue);
            return e1;
        }
        break;
    }

    return erro_conversao(e1, e2);
}

elemento *operacao_atribuicao_nome(char *nome, elemento *e2)
{
    return operacao_atribuicao(get_elemento_tabela(nome), e2);
}