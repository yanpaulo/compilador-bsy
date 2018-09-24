Interpretador BSY
Interpretador interativo para a Lingaugem BSY: Linguagem de programação semelhante a um subset da linguagem C99 com algumas diferenças.

Tipos existentes:
char, int, float e bool (alias para int).

INSTRUÇÕES SUPORTADAS:

Declaração de variáveis:
int i;

Declaração com inicialização:
char c = 100;
char c = 'a';
int i=10;
float x=1.5;

Declaração de múltiplas variáveis:
int i=0, j,k=10;

Conversão implícita:
char c = 'a';
int i = c;
float f = i;
int j = f; //Erro: não é possível atribuir valores de maior precisão a variáveis de menor precisão
int k = i * 10.0; //Erro: A expressão à direita se torna do tipo float pela presença de um operando float

OPERADORES SUPORTADOS:

Operadores aritméticos por ordem de precedência:
+, -
*, /
** (exponenciação)

Operadores lógicos: &&, ||
Operador unário: !
Operador de atribuição: = (atribuições também são expressões, e como tal é possível usa-las em operações compostas)

Qualquer expressão válida pode ser agrupada com parênteses balanceados para controlar a precedência.

Exemplos de expressões:
i = 10;
i = 10*2;
i = i*2;
i = j**3;
j = (2+2)**2;
i = 1 && 0;
i = 1 || 0;
i = !i;
i = !(i*2);

TABELA DE SÍMBOLOS:

Função para imprimir a tabela de símbolos: imprime()