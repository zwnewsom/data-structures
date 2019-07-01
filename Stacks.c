//
//  Stacks.c
//  
//
//  Created by Zach Newsom on 11/29/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define EMPTY_STACK_ERR INT_MIN

typedef struct Stack
{
    // this is the actual stack
    int *array;
    
    // how many elements are currently on the stack
    int size;
    
    // how many elements can the stack hold?
    int capacity;
} Stack;

Stack *createStack(int capacity)
{
    Stack *s;
    
    if ((s = malloc(sizeof(Stack))) == NULL)
        return NULL;
    
    if ((s->array = malloc(sizeof(int) * capacity)) == NULL)
    {
        free(s);
        return NULL;
    }
    
    s->size = 0;
    s->capacity = capacity;
    
    return s;
}

// Coded defensively to avoid segfaults
Stack *destroyStack(Stack *s)
{
    if (s == NULL)
        return NULL;
    
    free(s->array);
    free(s);
    
    return NULL;
}

int isEmpty(Stack *s)
{   
    return (s == NULL || s->size == 0);
}

int isFull(Stack *s)
{
    return (s == NULL || s->size == s->capacity);
}

void push(Stack *s, int data)
{
    if (isFull(s))
    {
        fprintf(stderr, "\nError: stack is full.\n");
        return;
    }
    
    s->array[ s->size++ ] = data;
}

int pop(Stack *s)
{
    if (s == NULL)
        return EMPTY_STACK_ERR;
    
    if (isEmpty(s))
    {
        fprintf(stderr, "\nError: stack is empty\n");
        return EMPTY_STACK_ERR;
    }
    
    return s->array[ --s->size ];
}

int peek(Stack *s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "\nError: stack is empty\n");
        return EMPTY_STACK_ERR;
    }
    
    return s->array[ s->size-1 ];
}

// Fancy function to print the stack. Can you figure out how it's working?
void printStack(Stack *s)
{
    int i; char str[32];

    printf("\n");

    if (s == NULL)
    {
        printf("   (no stack)\n");
        return;
    }

    if (s->size == 0)
    {
        printf("   (stack is empty)\n");
        return;
    }

    for (i = s->size - 1; i >= 0; i--)
    {
        printf("   |  %-4d  |%s\n", s->array[i],
               (i == s->size - 1) ? " <-- top" : "");
        printf("   +--------+\n");
    }
}

// Print list of commands for menu-driven interface.
void printMenu(void)
{
    printf("\n");
    printf("Stack ops:\n");
    printf("\n");
    printf("  new <n>    -- create a new stack with capacity set to <n>\n");
    printf("  destroy    -- completely destroy the current stack\n");
    printf("  push <n>   -- push <n> onto the stack\n");
    printf("  pop        -- pops the top element off the stack\n");
    printf("  peek       -- prints the stack's top element without removing it\n");
    printf("  empty      -- indicates whether the stack is empty\n");
    printf("  full       -- indicates whether the stack is full\n");
}

int main(void)
{
    char buffer[128]; int n;
    Stack *myStack = NULL;

    printMenu();
    printf("\n");

    // This loop is poorly commented, but hopefully it's fairly easy to follow.
    while (1)
    {
        printf("Enter a command ('?' for help, or 'exit' to quit).\n");
        printf("%% ");

        scanf("%s", buffer);

        if (strcmp(buffer, "?") == 0)
        {
            printMenu();
        }
        
        else if (strcmp(buffer, "new") == 0)
        {
            if (myStack != NULL)
                destroyStack(myStack);

            scanf("%d", &n);
            myStack = createStack(n);
        }

        else if (strcmp(buffer, "destroy") == 0)
        {
            if (myStack != NULL)
                myStack = destroyStack(myStack);
        }

        else if (strcmp(buffer, "push") == 0)
        {
            scanf("%d", &n);
            push(myStack, n);
        }

        else if (strcmp(buffer, "pop") == 0)
        {
            n = pop(myStack);

            if (n != EMPTY_STACK_ERR)
                printf("\n   -> popped %d\n", n);
        }

        else if (strcmp(buffer, "peek") == 0 || strcmp(buffer, "top") == 0)
        {
            n = peek(myStack);

            if (n != EMPTY_STACK_ERR)
                printf("\n   -> peek: %d\n", n);
        }

        else if (strcmp(buffer, "empty") == 0)
        {
            if (isEmpty(myStack))
                printf("\n   -> stack is empty\n");
            else
                printf("\n   -> stack is not empty\n");
        }

        else if (strcmp(buffer, "full") == 0)
        {
            if (isFull(myStack))
                printf("\n   -> stack is full\n");
            else
                printf("\n   -> stack is not full\n");
        }

        else if (strcmp(buffer, "exit") == 0)
        {
            break;
        }

        // Print the stack after each command.
        printStack(myStack);
        printf("\n");
    }

    // Clean up after yourself.
    destroyStack(myStack);

    return 0;
}
