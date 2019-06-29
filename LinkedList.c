// These 1st few lines are what's known as "pre-processor directives."
// Suffice it to say that these 3 lines of code give you access to already written blocks of code
// that we use throughout our program here. For example, the function printf() is contained in the stdio.h 
// header file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Here we're declaring a blueprint for our data object that we'll call "node." Each node will contain some 
// data (in this case an integer however we could use any data type or perhaps several data types if we so choose) 
// and a pointer which will point to the next node in the list
typedef struct node
{
    struct node *next;
    int data;
} node;

node *create_node(int num)
{
    node *new = calloc(1, sizeof(node));
    new->data = num;
    
    return new;
}

node *tail_insert(node *head, int data)
{
    node *temp;
    
    // You'll see this quite often in C: checking inputs to functions to avoid errors. Here, if head is NULL 
    // I simply exit the function by calling another to create a new node 
    if (head == NULL)
        return create_node(data);
    
    temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    
    temp->next = create_node(data);
    
    return head;//always return the head
}

void print_list(node *head)
{
    node *temp;

    if (head == NULL)
        return;

    temp = head;
    while (temp->next != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->next;

        if (temp->next == NULL)
            printf("%d\n", temp->data);
    }
}

void print_list_recursive(node *head)
{
}

int main(void)
{
    int i, r;

    // The head of our linked list. If we don't initialize it to NULL, our
    // tail_insert() function might segfault.
    node *head = NULL;

    srand(time(NULL));

    // Populate the linked list with random integers. We are inserting into the
    // head of the list each time.
    for (i = 0; i < 10; i++)
    {
        printf("Inserting %d...\n", r = rand() % 20 + 1);
        head = tail_insert(head, r);
    }

    // Print the linked list.
    print_list(head);

    // Print the linked list using our recursive function.
    //print_list_recursive(head);

    return 0;
}
