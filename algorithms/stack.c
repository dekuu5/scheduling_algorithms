#include "scheduling.h"
#include <stdlib.h>


Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack* stack, Process process) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->process = process;
    newNode->next = stack->top;
    stack->top = newNode;
}

Process pop(Stack* stack) {
    if (stack->top == NULL) {
        Process emptyProcess = {0};
        return emptyProcess;
    }
    StackNode* temp = stack->top;
    Process process = temp->process;
    stack->top = stack->top->next;
    free(temp);
    return process;
}

int isStackEmpty(Stack* stack) {
    return stack->top == NULL;
}