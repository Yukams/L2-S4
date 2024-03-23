// Need this to use the getline C function on Linux. Works without this on MacOs. Not tested on Windows.
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "token.h"
#include "queue.h"
#include "stack.h"


/** Main function for testing.
 * The main function expects one parameter that is the file where expressions to translate are
 * to be read.
 *
 * This file must contain a valid expression on each line
 *
 */
bool isSymbol(char c) {
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')') {
        return 1;
    }
    return 0;
}


Queue *stringToTokenQueue(const char *expression) {
    Queue *q = createQueue();
    const char *curpos = expression;
    int nb_char;
    Token *t;

    while(*curpos != '\0') {
        nb_char = 0;
        while((*curpos == ' ' || *curpos == '\n') && *curpos != '\0') {
            curpos += 1;
        }

        if (isSymbol(*curpos) && *curpos != '\0') {
            nb_char = 1;
        } else {
            while (*(curpos + nb_char) >= '0' && *(curpos + nb_char) <= '9' && *(curpos + nb_char) != '\0') {
                nb_char++;
            }
        }

        if (nb_char > 0) {
            t = createTokenFromString(curpos, nb_char);
            q = queuePush(q, t);
            curpos += nb_char;
        }
    }

    return q;

}


Queue *shuntingYard(Queue* infix) {
    Queue *out = createQueue();
    Stack *stack = createStack(32);
    Token *t;

    while (!queueEmpty(infix)) {
        t = queueTop(infix);
        queuePop(infix);

        if(tokenIsNumber(t)) {
            out = queuePush(out, t);
        } else if(tokenIsOperator(t)) {
            while(!stackEmpty(stack) && ((tokenGetOperatorPriority(stackTop(stack)) > tokenGetOperatorPriority(t)) || ((tokenGetOperatorPriority(stackTop(stack)) == tokenGetOperatorPriority(t) && tokenOperatorIsLeftAssociative(stackTop(stack))))) && tokenGetParenthesisSymbol(stackTop(stack)) != '(') {
                queuePush(out, stackTop(stack));
                stack = stackPop(stack);
            }
            stack = stackPush(stack, t);
        }
        else if(tokenGetParenthesisSymbol(t) == '(') {
            stack = stackPush(stack, t);
        } else if (tokenGetParenthesisSymbol(t) == ')') {
            while(tokenGetParenthesisSymbol(stackTop(stack)) != '(') {
                out = queuePush(out, stackTop(stack));
                stack = stackPop(stack);
            }
            stack = stackPop(stack);
        }
    }

    while(!stackEmpty(stack)) {
        out = queuePush(out, stackTop(stack));
        stack = stackPop(stack);
    }

    return out;
}

Token *evaluateOperator(Token *arg1, Token *op, Token *arg2) {
    char ope = tokenGetOperatorSymbol(op);
    float result;
    float val1 = tokenGetValue(arg1);
    float val2 = tokenGetValue(arg2);

    if(ope == '+') {
        result = val1 + val2;
    } else if(ope == '-') {
        result = val1 - val2;
    } else if(ope == '*') {
        result = val1 * val2;
    } else if(ope == '/') {
        result = val1 / val2;
    } else {
        result = pow(val1, val2);
    }
    Token* t = createTokenFromValue(result);
    return t;
}

float evaluateExpression(Queue* postfix) {
    Token *t = NULL;
    Stack *stack = createStack(32);

    while(!queueEmpty(postfix)) {
        t = queueTop(postfix);
        queuePop(postfix);

        if(tokenIsOperator(t)) {
            Token* op2 = stackTop(stack);
            stack = stackPop(stack);
            Token* op1 = stackTop(stack);
            stack = stackPop(stack);
            stack = stackPush(stack , evaluateOperator(op1, t, op2));
        } else if (tokenIsNumber(t)) {
            stack = stackPush(stack, t);
        }
    }

    return tokenGetValue(stackTop(stack));
}


void printToken(FILE *f, void *e) {
    tokenDump(f, e);
}


void computeExpressions(FILE *input) {
    size_t n = 0;
    char* linep = NULL;
    int nb_lu = 0;
    Queue *q = NULL;
    Queue *out = NULL;
    float post = 0;

    while((nb_lu = getline(&linep, &n, input)) != -1) {
        if(nb_lu > 1) {
            printf("Input : %s", linep);
            q = stringToTokenQueue(linep);
            printf("Infix : ");
            queueDump(stdout, q, printToken);
            printf("\nOutfix : ");
            out = shuntingYard(q);
            queueDump(stdout, out, printToken);
            post = evaluateExpression(out);
            printf("\nPostfix : %f", post);
            printf("\n\n");
        }
    }

    deleteQueue(&q);
}


int main(int argc, char **argv){
	FILE *input;
	
	if (argc<2) {
		fprintf(stderr,"usage : %s filename\n", argv[0]);
		return 1;
	}
	
	input = fopen(argv[1], "r");

	if ( !input ) {
		perror(argv[1]);
		return 1;
	}

	computeExpressions(input);

	fclose(input);
	return 0;
}
 
