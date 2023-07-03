#include "backend.h"

void initStack(Stack *stack) { stack->top = -1; }

int isStackEmpty(Stack *stack) { return (stack->top == -1); }

int stackPush(Leksem Lek, Stack *stack) {
  int res = SUCCESS;
  if (stack->top == MAX_SIZE - 1) {
    res = FAILURE;
  }
  stack->data[++(stack->top)] = Lek;
  return res;
}

int stackPop(Stack *stack, Leksem *Lek) {
  int res = FAILURE;
  if (stack->top >= 0) {
    *Lek = stack->data[stack->top--];
    res = SUCCESS;
  }
  return res;
}

int isOperator(char ch) {
  return (ch == PLUS || ch == MINUS || ch == MULT || ch == DIV || ch == POW ||
          ch == MOD);
}

int precedence(char ch) {
  int precedence = 0;
  switch (ch) {
    case PLUS:
    case MINUS:
      precedence = 1;
      break;
    case MULT:
    case DIV:
    case MOD:
      precedence = 2;
      break;
    case POW:
      precedence = 3;
      break;
    case SIN:
    case COS:
    case TAN:
    case ASIN:
    case ACOS:
    case ATAN:
    case SQRT:
    case LOG:
    case LN:
      precedence = 4;
      break;
  }
  return precedence;
}

int addNumber(const char *infix, Stack *stack) {
  int check = 0;
  Leksem Lek = {0, 0, 0};
  sscanf(infix, "%lf%n", &Lek.data, &check);
  stackPush(Lek, stack);
  return check - 1;
}

int addX(const char *infix, Stack *stack) {
  int check = 0;
  Leksem Lek = {0, 0, 'x'};
  sscanf(infix, "%c%n", &Lek.x, &check);
  stackPush(Lek, stack);
  return check - 1;
}

int isRightAssoc(char op) { return op == POW; }

void addOperator(char ch, Stack *stack, Stack *tempstack) {
  Leksem tempLek = {0, 0, 0};
  int popRes = SUCCESS;

  while (!(popRes = stackPop(tempstack, &tempLek)) &&
         ((precedence(ch) < precedence(tempLek.op)) ||
          (precedence(ch) == precedence(tempLek.op) && !isRightAssoc(ch)))) {
    stackPush(tempLek, stack);
  }
  if (!popRes) {
    stackPush(tempLek, tempstack);
  }

  Leksem Lek = {0, 0, ch};
  stackPush(Lek, tempstack);
}

int checkFunc(const char *infix, char *ch, size_t *i) {
  int res = SUCCESS;
  switch (infix[*i]) {
    case 's':
      if (infix[*i + 1] == 'q' && infix[*i + 2] == 'r' &&
          infix[*i + 3] == 't' &&
          (infix[*i + 4] == '(' || infix[*i + 4] == ' ')) {
        *ch = SQRT;
        *i += 3;
      } else if (infix[*i + 1] == 'i' && infix[*i + 2] == 'n' &&
                 (infix[*i + 3] == '(' || infix[*i + 3] == ' ')) {
        *ch = SIN;
        *i += 2;
      } else {
        res = FAILURE;
      }
      break;
    case 'c':
      if (infix[*i + 1] == 'o' && infix[*i + 2] == 's' &&
          (infix[*i + 3] == '(' || infix[*i + 3] == ' '))
        *ch = COS;
      *i += 2;
      break;
    case 't':
      if (infix[*i + 1] == 'a' && infix[*i + 2] == 'n' &&
          (infix[*i + 3] == '(' || infix[*i + 3] == ' '))
        *ch = TAN;
      *i += 2;
      break;
    case 'a':
      if (infix[*i + 1] == 's' && infix[*i + 2] == 'i' &&
          infix[*i + 3] == 'n' &&
          (infix[*i + 4] == '(' || infix[*i + 4] == ' ')) {
        *ch = ASIN;
        *i += 3;
      } else if (infix[*i + 1] == 'c' && infix[*i + 2] == 'o' &&
                 infix[*i + 3] == 's' &&
                 (infix[*i + 4] == '(' || infix[*i + 4] == ' ')) {
        *ch = ACOS;
        *i += 3;
      } else if (infix[*i + 1] == 't' && infix[*i + 2] == 'a' &&
                 infix[*i + 3] == 'n' &&
                 (infix[*i + 4] == '(' || infix[*i + 4] == ' ')) {
        *ch = ATAN;
        *i += 3;
      } else {
        res = FAILURE;
      }
      break;
    case 'l':
      if (infix[*i + 1] == 'o' && infix[*i + 2] == 'g' &&
          (infix[*i + 3] == '(' || infix[*i + 3] == ' ')) {
        *ch = LOG;
        *i += 2;
      } else if (infix[*i + 1] == 'n' &&
                 (infix[*i + 2] == '(' || infix[*i + 2] == ' ')) {
        *ch = LN;
        *i += 1;
      } else {
        res = FAILURE;
      }
      break;
    default:
      res = FAILURE;
      break;
  }
  return res;
}

char *processUnaryMinus(const char *infix) {
  char *processed = (char *)malloc((strlen(infix) * 3 + 1) * sizeof(char));
  size_t j = 0;

  for (size_t i = 0; i < strlen(infix); i++) {
    if (infix[i] == '-' &&
        (i == 0 || infix[i - 1] == '(' || isOperator(infix[i - 1]))) {
      processed[j++] = '(';
      processed[j++] = '0';
      processed[j++] = '-';
      processed[j++] = '1';
      processed[j++] = ')';
      processed[j++] = '*';
    } else if (infix[i] == '+' &&
               (i == 0 || infix[i - 1] == '(' || isOperator(infix[i - 1]))) {
      continue;
    } else {
      processed[j++] = infix[i];
    }
  }

  processed[j] = '\0';

  return processed;
}

int infixToPostfix(const char *infix, Stack *outStack) {
  if (infix == NULL || outStack == NULL) {
    return FAILURE;
  }

  char *processedInfix = processUnaryMinus(infix);

  Stack stack;
  initStack(&stack);
  Stack tempstack;
  initStack(&tempstack);

  int res = SUCCESS;

  size_t i = 0;
  char ch = '\0';

  while ((ch = processedInfix[i]) != '\0') {
    if (i >= strlen(processedInfix)) break;

    if (isdigit(ch)) {
      i += addNumber(processedInfix + i, &stack);
    } else if (isOperator(ch)) {
      addOperator(ch, &stack, &tempstack);
    } else if (isalpha(ch) && ch != 'x') {
      checkFunc(processedInfix, &ch, &i);
      addOperator(ch, &stack, &tempstack);
    } else if (ch == 'x') {
      addX(processedInfix + i, &stack);
    } else if (ch == '(') {
      Leksem Lek = {0, 0, ch};
      stackPush(Lek, &tempstack);
    } else if (ch == ')') {
      Leksem Lek = {0, 0, 0};
      while (!isStackEmpty(&stack) && !stackPop(&tempstack, &Lek) &&
             (Lek.op != '(')) {
        stackPush(Lek, &stack);
      }
      if (Lek.op != '(') {
        res = FAILURE;
      }
    }
    i += 1;
  }

  while (!isStackEmpty(&tempstack)) {
    Leksem Lek = {0, 0, 0};
    stackPop(&tempstack, &Lek);
    stackPush(Lek, &stack);
  }

  if (outStack != NULL) {
    *outStack = stack;
  }

  if (!isStackEmpty(&tempstack)) {
    res = FAILURE;
  }

  free(processedInfix);

  return res;
}

int lekIsOp(Leksem *lek) { return lek->op != '\0'; }

int lekIsX(Leksem *lek) { return lek->x != '\0'; }

int lekIsData(Leksem *lek) { return !lekIsOp(lek) && !lekIsX(lek); }

int calculate(Stack *resultStack, double x, double *result) {
  int res = SUCCESS;
  int curNum = 0;

  for (int i = 0; i <= resultStack->top && res == SUCCESS; i++) {
    Leksem lek = resultStack->data[i];

    if (lekIsData(&lek)) {
      result[curNum] = lek.data;
      curNum += 1;
    } else if (lekIsX(&lek)) {
      result[curNum] = x;
      curNum += 1;
    } else if (lekIsOp(&lek)) {
      switch (lek.op) {
        case PLUS:
          if (curNum >= 2) {
            result[curNum - 2] = result[curNum - 2] + result[curNum - 1];
            curNum -= 1;
          } else {
            res = FAILURE;
          }
          break;
        case MINUS:
          if (curNum >= 2) {
            result[curNum - 2] = result[curNum - 2] - result[curNum - 1];
            curNum -= 1;
          } else {
            res = FAILURE;
          }
          break;
        case MULT:
          if (curNum >= 2) {
            result[curNum - 2] = result[curNum - 2] * result[curNum - 1];
            curNum -= 1;
          } else {
            res = FAILURE;
          }
          break;
        case DIV:
          if (curNum >= 2) {
            result[curNum - 2] = result[curNum - 2] / result[curNum - 1];
            curNum -= 1;
          } else {
            res = FAILURE;
          }
          break;
        case POW:
          if (curNum >= 2) {
            result[curNum - 2] = pow(result[curNum - 2], result[curNum - 1]);
            curNum -= 1;
          } else {
            res = FAILURE;
          }
          break;
        case MOD:
          if (curNum >= 2) {
            result[curNum - 2] = fmod(result[curNum - 2], result[curNum - 1]);
            curNum -= 1;
          } else {
            res = FAILURE;
          }
          break;
        case SIN:
          if (curNum >= 1) {
            result[curNum - 1] = sin(result[curNum - 1]);
          } else {
            res = FAILURE;
          }
          break;
        case COS:
          if (curNum >= 1) {
            result[curNum - 1] = cos(result[curNum - 1]);
          } else {
            res = FAILURE;
          }
          break;
        case TAN:
          if (curNum >= 1) {
            result[curNum - 1] = tan(result[curNum - 1]);
          } else {
            res = FAILURE;
          }
          break;
        case ASIN:
          if (curNum >= 1) {
            result[curNum - 1] = asin(result[curNum - 1]);
          } else {
            res = FAILURE;
          }
          break;
        case ACOS:
          if (curNum >= 1) {
            result[curNum - 1] = acos(result[curNum - 1]);
          } else {
            res = FAILURE;
          }
          break;
        case ATAN:
          if (curNum >= 1) {
            result[curNum - 1] = atan(result[curNum - 1]);
          } else {
            res = FAILURE;
          }
          break;
        case SQRT:
          if (curNum >= 1) {
            result[curNum - 1] = sqrt(result[curNum - 1]);
          } else {
            res = FAILURE;
          }
          break;
        case LOG:
          if (curNum >= 1) {
            result[curNum - 1] = log10(result[curNum - 1]);
          } else {
            res = FAILURE;
          }
          break;
        case LN:
          if (curNum >= 1) {
            result[curNum - 1] = log(result[curNum - 1]);
          } else {
            res = FAILURE;
          }
          break;
        default:
          res = FAILURE;
          break;
      }
    }
  }
  if (curNum > 1) res = FAILURE;

  return res;
}

int graphic(const char *infix, double *x, double *y, size_t len) {
  int err = infix == NULL || x == NULL || y == NULL;

  Stack notationStack;
  if (!err) err = infixToPostfix(infix, &notationStack);

  if (!err) {
    double *numbers = malloc(notationStack.top * sizeof(double));
    if (numbers == NULL) {
      err = 1;
    } else {
      for (size_t i = 0; i < len && !err; ++i) {
        err = calculate(&notationStack, x[i], y + i);
      }
      if (numbers != NULL) free(numbers);
    }
  }
  return err;
}

int smartCalc(const char *expression, double *result) {
  if (expression == NULL || result == NULL) {
    return FAILURE;
  }

  Stack resultStack;
  initStack(&resultStack);

  int res = infixToPostfix(expression, &resultStack);

  if (res == SUCCESS) {
    for (int i = 0; i <= resultStack.top && res == SUCCESS; i++) {
      Leksem lek = resultStack.data[i];
      if (lekIsX(&lek)) {
        res = FAILURE;
      }
    }

    if (res == SUCCESS) {
      double *numbers = malloc((resultStack.top + 1) * sizeof(double));
      if (numbers == NULL) {
        res = FAILURE;
      } else {
        res = calculate(&resultStack, 0, numbers);
        if (res == SUCCESS) {
          *result = numbers[0];
        }
        free(numbers);
      }
    }
  }

  return res;
}
