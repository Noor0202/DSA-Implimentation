#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Node 
{
    int data;
    struct Node *next;
};

struct MyStack 
{
    struct Node *top;
    int capacity;
};

void initialize_stack(struct MyStack *stack, int size)
{
    stack->top = NULL;
    stack->capacity = size;
}

bool is_empty(struct MyStack *stack)
{
    return stack->top == NULL;
}

void push_into_stack(struct MyStack *stack, int data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    
    if (new_node == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    
    else if (stack->capacity == 0)
    {
        printf("Stack overflow.\n");
        exit(EXIT_FAILURE);
    }

    else
    {
        new_node->data = data;
        new_node->next = stack->top;
        stack->top = new_node;
        stack->capacity -= 1;
    }
    
}

int pop_from_stack(struct MyStack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack underflow.\n");
        exit(EXIT_FAILURE);
    }
    
    int data = stack->top->data;
    struct Node *temp = stack->top;
    stack->top = stack->top->next;
    
    free(temp);
    
    return data;
}

int peek_of_stack(struct MyStack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    
    return stack->top->data;
}

int main()
{

    struct MyStack myStack;
    initialize_stack(&myStack,12);

    int elements[] = {1,2,3,4,5,6,7,8,9,10,11,12}; 
    int n = sizeof(elements) / sizeof(elements[0]);

    for (int i = 0; i < n; i++)
    {
        push_into_stack(&myStack, elements[i]);
    }

    printf("Elements in the stack:\n");
    
    while (!is_empty(&myStack))
    {
        printf("%d ", pop_from_stack(&myStack));
    }

    // printf("\n");
    
    // pop_from_stack(&myStack);

    printf("\n");

    return 0;
}
