#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fenv.h>

#pragma STDC FENV_ACCESS ON

int validateInput (int length, char *input[]);
int validateFloat (char *input);

void calculate (float num1, float num2, char op, float *result);

void logOutput       (float num1, float num2, char op, float result);
void logBits         (float num);
void logFEExceptions ();

int main(int argc, char *argv[])
{
    if (validateInput(argc, argv))
        return 1;

    feclearexcept(FE_ALL_EXCEPT);

    float num1, num2, result;
    char  op;  

    num1 = atof(argv[1]);
    num2 = atof(argv[3]);
    op   = argv[2][0];

    calculate(num1, num2, op, &result);

    logOutput(num1, num2, op, result);

    return 0;
}

int validateInput(int length, char *input[])
{
    if (length != 4)    
    {
        printf("Informe uma entrada valida no formato:\nnum1 op num2\n");
        return 1;
    }

    if (strlen(input[2]) != 1)
    {
        printf("Entrada invalida: op deve ser um unico caractere\n");
        return 1;
    }

    char op = input[2][0];

    if (op != 'x' && op != 'X' && op != '.' && op != '+' && op != '-' && op != '/')
    {
        printf("Entrada invalida: op deve ser uma das seguintes operacoes:\nSoma: +\nSubtracao: -\nMultiplicacao: x, X, .\nDivisao: /\n");
        return 1;
    }

    if (validateFloat(input[1]) || validateFloat(input[3]))
        return 1;
    
    return 0;
}

int validateFloat(char *input)
{
    float validate;

    if (sscanf(input, "%f", &validate) != 1)
    {
        printf("Entrada invalida: valor informado nao e float: %s\n", input);
        return 1;
    }

    return 0;
}           

void calculate(float num1, float num2, char op, float *result)
{
    switch (op)
    {
        case '+':
            *result = num1 + num2;;
            break;
        case '-':
            *result = num1 - num2;
            break;
        case 'x':
        case 'X':
        case '.':
            *result = num1 * num2;
            break;
        case '/':
            *result = num1 / num2;
            break;
    }
}

void logOutput(float num1, float num2, char op, float result)
{
    printf("\nRecebi %f %c %f e resultado deu %f\n", num1, op, num2, result);

    printf("\nval1 = ");
    logBits(num1);

    printf("val2 = ");
    logBits(num2);
    
    printf("res  = ");
    logBits(result);

    printf("\n");

    logFEExceptions();
    printf("\n");
}

void logBits(float num)
{
    unsigned int *bits = (unsigned int *)&num;

    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (*bits >> i) & 1);
        if (i == 31 || i == 23)
            printf(" ");
    }
    
    printf("\n");
}

void logFEExceptions()
{
    printf("Excecao FE_INEXACT: %d\n", fetestexcept(FE_INEXACT));
    printf("Excecao FE_DIVBYZERO: %d\n", fetestexcept(FE_DIVBYZERO));
    printf("Excecao FE_UDNERFLOW: %d\n", fetestexcept(FE_UNDERFLOW));
    printf("Excecao FE_OVERFLOW: %d\n", fetestexcept(FE_OVERFLOW));
    printf("Excecao FE_INVALID: %d\n", fetestexcept(FE_INVALID));
}