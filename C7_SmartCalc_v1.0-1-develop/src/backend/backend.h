#ifndef __backcalc__
#define __backcalc__

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255

#define SUCCESS 0
#define FAILURE 1

#define SIN 's'
#define COS 'c'
#define TAN 't'
#define ASIN 'q'
#define ACOS 'w'
#define ATAN 'e'
#define SQRT 'r'
#define LOG 'l'
#define LN 'n'
#define POW '^'
#define MOD '%'
#define PLUS '+'
#define MINUS '-'
#define MULT '*'
#define DIV '/'

typedef struct {
  double data;
  char x;
  char op;
} Leksem;

typedef struct {
  Leksem data[MAX_SIZE];
  int top;
} Stack;

void initStack(Stack *stack);
int isStackEmpty(Stack *stack);
int stackPush(Leksem Lek, Stack *stack);
int stackPop(Stack *stack, Leksem *Lek);

int isRightAssoc(char op);
int isFunc(const char *infix, char *ch, size_t *i);
int isOperator(char ch);
void addOperator(
    char ch, Stack *stack,
    Stack *tempstack);  // Добавляет оператор в стек или перемещает операторы из
                        // временного стека в основной стек в соответствии с
                        // приоритетом операторов
int precedence(char ch);
int addNumber(const char *infix, Stack *stack);
int addX(const char *infix, Stack *stack);

int lekIsOp(Leksem *lek);
int lekIsX(Leksem *lek);
int lekIsData(Leksem *lek);

char *processUnaryMinus(const char *infix);  // Преобразование подаваемой строки
                                             // с учетом унарных знаков
int infixToPostfix(const char *infix, Stack *outStack);
int calculate(Stack *resultStack, double x, double *result);
int graphic(const char *infix, double *x, double *y, size_t len);
int smartCalc(const char *expression, double *result);

#endif  // __backcalc__
