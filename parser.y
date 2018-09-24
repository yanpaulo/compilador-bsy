%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suporte.h"
#include "operacoes.h"

#define VERIFICA(F) if(!F) YYERROR;
#define ATRIBUI(VAR, F) VAR = F; if(!VAR) YYERROR;

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
    char* nome;
    tipo tipo;
    elemento* elemento;
}

%token IMPRIMIR
%token<nome> ID_NOME
%token<tipo> TIPO
%token<elemento> VALOR

%type<elemento> inicia_ou_id inicia_ou_lista_de_id expressao

%left '='
%left AND OR NOT
%left '+' '-'
%left '*' '/'
%left EXP

%%

main:
    instrucoes
    ;

instrucoes:
    instrucao
    | instrucoes instrucao
    ;
instrucao:
    declaracao ';'
    | expressao ';'
    | IMPRIMIR ';'              { imprime_tabela(); }
    ;

declaracao:
    TIPO inicia_ou_lista_de_id  { VERIFICA(adiciona_elementos_tabela($1, $2)); }
    ;

inicia_ou_lista_de_id:
    inicia_ou_id                                { $$ = $1; }
    | inicia_ou_lista_de_id ',' inicia_ou_id    { ATRIBUI($$, adiciona_elemento($1, $3)); }
    ;

inicia_ou_id:
    ID_NOME '=' expressao   { $3->nome = strdup($1); $$ = $3; }
    | ID_NOME               { ATRIBUI($$, cria_elemento(strdup($1))); }
    ;

expressao:
    expressao '+' expressao     { $$ = operacao_soma($1, $3); }
    | expressao '-' expressao   { $$ = operacao_subtracao($1, $3); }
    | expressao '*' expressao   { $$ = operacao_multiplicacao($1, $3); }
    | expressao '/' expressao   { $$ = operacao_divisao($1, $3); }
    | expressao EXP expressao   { ATRIBUI($$, operacao_exponenciacao($1, $3)); }
    | expressao OR expressao    { $$ = operacao_ou($1, $3); }
    | expressao AND expressao   { $$ = operacao_e($1, $3); }
    | NOT expressao             { $$ = operacao_negacao($2); }
    | ID_NOME '=' expressao     { $$ = operacao_atribuicao_nome($1, $3); }
    | ID_NOME                   { ATRIBUI($$, copia_elemento(get_elemento_tabela($1))); }
    | '(' expressao ')'         { $$ = $2; }
	| VALOR                     { $$ = $1; }
    ;
 
%%

int main() {
    inicializa_tabela();
	while(1) {
		yyparse();
	}
	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "ERRO: %s\n", s);
}
