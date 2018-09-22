%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
void yyerror(const char* s);
%}

%token VALOR
%token LINHA

%left OP_SOMA OP_MULT
%%

main:
	operacao
	| operacao LINHA 	{ exit(0); }
	| LINHA 			{ exit(0); }
;

operacao:
	operacao soma LINHA	{ printf("%d\n", $2); }
	| soma LINHA		{ printf("%d\n", $1); }
;

soma:
	soma OP_SOMA mult	{ $$ = $1 + $3; }
	| mult				{ $$ = $1; }
;

mult:
	mult OP_MULT VALOR	{ $$ = $1 * $3; }
	| VALOR				{ $$ = $1; }
;

%%


int main() {
	while(1) {
		yyparse();
	}
	return 0;
}

void yyerror(const char* s) {
    printf("Erro: %s\n", s);
}