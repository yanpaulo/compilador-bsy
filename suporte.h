#ifndef SUPORTE_H
#define SUPORTE_H

#pragma region Estruturas
//Valor de constante ou variável
typedef union valor
{
    char charValue;
    int intValue;
    float floatValue;

} valor;

//Tipo de valor
typedef enum tipo
{
    CHAR=1, INT, FLOAT
} tipo;

//Elemento representa uma constante ou variável.
typedef struct elemento
{
    //Nome (quando se trata de uma variável)
    char* nome;
    tipo tipo;
    valor valor;
    //Próximo elemento.
    //Usado quando o elemento está em uma lista (exelmplos: tabela de símbolos e lista de declarações).
    struct elemento* proximo;
} elemento;

//Tabela de símbolos
typedef struct tabela
{
    elemento* head;
} tabela;


//Instância da tabela de símbolos
tabela* tabela_simbolos;
#pragma endregion //Estruturas


#pragma region Tabela
//Inicializa a tabela de símbolos
void inicializa_tabela();

//Imprime a tabela de símbolos
void imprime_tabela_simbolos();

//Adiciona uma lista com 1 ou mais elementos na tabela de símbolos
tabela* adiciona_elementos_tabela(tipo t, elemento* e);

//Retorna um (hum) elemento da tabela de símbolos
elemento* get_elemento_tabela(char* nome);
#pragma endregion //Tabela


#pragma region Lista
//Adiciona um elemento na lista especificada
elemento* adiciona_elemento(elemento* lista, elemento* e);

//Imprime os elementos da lista especificada
void imprime_elementos(elemento* lista);
#pragma endregion //Lista


#pragma region Elemento
//Cria um elemento com o nome especificado
elemento* cria_elemento(char* nome);

//Cria um elemento com o tipo e valor especificados
elemento* cria_elemento_valor(tipo t, valor v);

//Cria uma cópia do elemento e (o elemento de origem deve ter nome)
elemento* copia_elemento(elemento* e);

//Cria um elemento com valor inteiro i
elemento* valor_int(int i);

//Cria um elemento com valor floar f
elemento* valor_float(float f);

//Cria um elemento com valor char c
elemento* valor_char(char c);
#pragma endregion //Elemento

//Retorna o nome do tipo t
char *nome_tipo(tipo t);

#endif