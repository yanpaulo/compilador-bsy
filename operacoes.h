#ifndef OPERACOES_H
#define OPERACOES_H

#include "modelo.h"

//Operações aritméticas
elemento *operacao_soma(elemento *e1, elemento *e2);
elemento *operacao_subtracao(elemento *e1, elemento *e2);
elemento *operacao_multiplicacao(elemento *e1, elemento *e2);
elemento *operacao_divisao(elemento *e1, elemento *e2);
elemento* operacao_exponenciacao(elemento* e1, elemento* e2);

//Operações lógicas
elemento *operacao_ou(elemento *e1, elemento *e2);
elemento *operacao_e(elemento *e1, elemento *e2);
elemento *operacao_negacao(elemento *e1);

//Operações de atribuição
elemento *operacao_atribuicao(elemento *e1, elemento *e2);
elemento* operacao_atribuicao_nome(char* nome, elemento* e2);

#endif