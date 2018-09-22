
typedef union valor
{
    char charValue;
    int intValue;
    float floatValue;

} valor;

typedef enum tipo
{
    CHAR, INT, FLOAT
} tipo;


typedef struct elemento
{
    char nome[64];
    tipo tipo;
    valor valor;
    elemento* proximo;
} elemento;


struct tabela
{
    elemento* head;
} tabela;

