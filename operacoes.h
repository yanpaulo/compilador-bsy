#ifndef OPERACOES_H
#define OPERACOES_H

#include "suporte.h"

elemento *operacao_soma(elemento *e1, elemento *e2);
elemento *operacao_subtracao(elemento *e1, elemento *e2);
elemento *operacao_multiplicacao(elemento *e1, elemento *e2);
elemento *operacao_divisao(elemento *e1, elemento *e2);

elemento *operacao_atribuicao(elemento *e1, elemento *e2);

#endif