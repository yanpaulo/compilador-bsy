%{
#include <stdlib.h>
#include "parser.tab.h"
%}

%option noyywrap

%%
[ \r\t]*        ;
"\n"			{ return LINHA; }
[0-9]+			{ yylval = atoi(yytext); return VALOR; }
"+"				{ return OP_SOMA; }
"*"				{ return OP_MULT; }
%%