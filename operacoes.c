#include <stdlib.h>
#include "suporte.h"
#include "operacoes.h"

extern void yyerror(const char *s);

#pragma region Macros
#define OPERACAO_ARITMETICA(OP)\
switch (e1->tipo)\
    {\
    case CHAR:\
        switch (e2->tipo)\
        {\
        case CHAR:\
            return valor_char(e1->valor.charValue OP e2->valor.charValue);\
        case INT:\
            return valor_int(e1->valor.charValue OP e2->valor.intValue);\
        case FLOAT:\
            return valor_float(e1->valor.charValue OP e2->valor.floatValue);\
        }\
\
    case INT:\
        switch (e2->tipo)\
        {\
        case CHAR:\
            return valor_int(e1->valor.intValue OP e2->valor.charValue);\
        case INT:\
            return valor_int(e1->valor.intValue OP e2->valor.intValue);\
        case FLOAT:\
            return valor_float(e1->valor.intValue OP e2->valor.floatValue);\
        }\
\
    case FLOAT:\
        switch (e2->tipo)\
        {\
        case CHAR:\
            return valor_float(e1->valor.floatValue OP e2->valor.charValue);\
        case INT:\
            return valor_float(e1->valor.floatValue OP e2->valor.intValue);\
        case FLOAT:\
            return valor_float(e1->valor.floatValue OP e2->valor.floatValue);\
        }\
    }\
\
    return NULL;

#define OPERACAO_LOGICA(OP)\
switch (e1->tipo)\
    {\
    case CHAR:\
        switch (e2->tipo)\
        {\
        case CHAR:\
            return valor_int(e1->valor.charValue OP e2->valor.charValue);\
        case INT:\
            return valor_int(e1->valor.charValue OP e2->valor.intValue);\
        case FLOAT:\
            return valor_int(e1->valor.charValue OP e2->valor.floatValue);\
        }\
\
    case INT:\
        switch (e2->tipo)\
        {\
        case CHAR:\
            return valor_int(e1->valor.intValue OP e2->valor.charValue);\
        case INT:\
            return valor_int(e1->valor.intValue OP e2->valor.intValue);\
        case FLOAT:\
            return valor_int(e1->valor.intValue OP e2->valor.floatValue);\
        }\
\
    case FLOAT:\
        switch (e2->tipo)\
        {\
        case CHAR:\
            return valor_float(e1->valor.floatValue OP e2->valor.charValue);\
        case INT:\
            return valor_float(e1->valor.floatValue OP e2->valor.intValue);\
        case FLOAT:\
            return valor_float(e1->valor.floatValue OP e2->valor.floatValue);\
        }\
    }\
\
    return NULL;
#pragma region //Macros

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