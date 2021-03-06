%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include "modelo.h"
#include "parser.tab.h"
%}

id_nome [_a-zA-Z]([a-zA-Z0-9])*
valor_char '.'
valor_char_n [-]?([0-9]|[0-9][0-9]|1[0-1][0-9]|12[0-5])
valor_float [-]?[0-9]+\.[0-9]+
valor_int [-]?[0-9]+

%%

"int"                   { yylval.tipo = INT; return TIPO; }
"float"                 { yylval.tipo = FLOAT; return TIPO; }
"bool"                  { yylval.tipo = INT; return TIPO; }
"char"                  { yylval.tipo = CHAR; return TIPO; }
"imprime()"             { return IMPRIMIR; }

"true"                  { return VALOR; }
"false"                 { return VALOR; }

{valor_char}            { yylval.elemento = valor_char(yytext[1]); return VALOR; }
{valor_char_n}          { yylval.elemento = valor_char(atoi(yytext)); return VALOR; }
{valor_int}             { yylval.elemento = valor_int(atoi(yytext)); return VALOR; }
{valor_float}           { yylval.elemento = valor_float(atof(yytext)); return VALOR; }
{id_nome}               { yylval.nome = strdup(yytext); return ID_NOME; }

[ \r\t]*                ;

","                     { return ','; }
":"                     { return ':'; }
";"                     { return ';'; }
"="                     { return '='; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"**"                    { return EXP; }
"/"                     { return '/'; }
"("                     { return '('; }
")"                     { return ')'; }
"!"                     { return NOT; }
"&&"                    { return AND; }
"||"                    { return OR; }


%%