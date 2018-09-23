%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suporte.h"

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

%token<nome> ID_NOME
%token<tipo> TIPO
%token<elemento> VALOR

%type<elemento> inicia_ou_id inicia_ou_lista_de_id expressao

%left '+' '-'
%left '*' '/'


%%

main: declaracoes
    ;

declaracoes:
    declaracao
    | declaracoes declaracao
    ;

declaracao:
    TIPO inicia_ou_lista_de_id ';' { if(!adiciona_elementos_tabela($1, $2)) { YYERROR; } imprime_elementos($2); }
    ;

inicia_ou_lista_de_id:
    inicia_ou_id                                { $$ = $1; }
    | inicia_ou_lista_de_id ',' inicia_ou_id    { $$ = adiciona_elemento($1, $3); }
    ;

inicia_ou_id:
    ID_NOME '=' expressao   { $3->nome = strdup($1); $$ = $3; }
    | ID_NOME               { $$ = cria_elemento(strdup($1)); if(!$$){ YYERROR; } }
    ;

expressao:
    expressao '+' expressao
    | expressao '-' expressao
    | expressao '*' expressao
    | expressao '/' expressao
    | '(' expressao ')'
	| VALOR { $$ = $1; }
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
	fprintf(stderr, "ERRO!: %s\n", s);
}
