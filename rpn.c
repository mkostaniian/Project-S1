#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define MAX_STACK_SIZE 100  
int stack[MAX_STACK_SIZE]; // The stack can hold up to 100 integers
int top = -1; // the stack is initially empty


// At first checks if the stack is full,and pushes a new integer onto the top of the stack
void push(int value) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Stack overflow!\n");
        exit(1);
    }
    stack[++top] = value;
}
//This checks if the stack is empty,and then returns and removes the top value from the stack
int pop() {
    if (top < 0) {
        printf("Stack underflow!\n");
        exit(1);
  }
    return stack[top--];
}

int main() {
    char input[256];
    char *token; //Pointer to store each part (number or operator) of the input.
    int operand1, operand2, result;

    printf("Enter RPN expression (e.g., 3 4 + 2 *): "); //input from user
    fgets(input, sizeof(input), stdin);  //Helps us read user's input

    token = strtok(input, " \n"); //plits the input string into tokens separated by space ' ' or newline '\n'
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) { //is it number(positive and negative)
            push(atoi(token)); //Converts string to integer.
        } else { 
            operand2 = pop();
            operand1 = pop();

            switch (*token) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Division by zero!\n");
                        exit(1);
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Invalid operator: %s\n", token);
                    exit(1);
            }
            push(result);
        }
        token = strtok(NULL, " \n"); // move to next token,until all tokens are processed.
    }

    if (top == 0) { 
        printf("Result: %d\n", pop());
    } else {
        printf("Invalid RPN expression.\n");
    }

    return 0;
}
