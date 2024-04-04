#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int data;
    struct ListNode *next;
};

enum StatusCode
{
    FAILURE,
    SUCCESS
};

struct Status
{
    enum StatusCode code;
    int element;
};

struct MyList
{
    struct ListNode *head;
};

void initialize_list(struct MyList *list)
{
    list->head = NULL;
}

struct Status add_element(struct MyList *list, int element)
{
    struct Status list_status;
    list_status.element = element;

    struct ListNode *new_node = (struct ListNode *)malloc(sizeof(struct ListNode));
    
    if (new_node == NULL)
    {
        list_status.code = FAILURE;
        return list_status;
    }

    new_node->data = element;
    new_node->next = NULL;

    if (list->head == NULL || element < list->head->data)
    {
        new_node->next = list->head;
        list->head = new_node;
        list_status.code = SUCCESS;
        return list_status;
    }

    struct ListNode *prev_node = list->head;
    struct ListNode *curr_node = list->head->next;

    while (curr_node != NULL && curr_node->data < element)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    prev_node->next = new_node;
    new_node->next = curr_node;

    list_status.code = SUCCESS;
    return list_status;
}


struct Status remove_element(struct MyList *list, int element)
{
    struct Status list_status;
    list_status.element = element;

    if (list->head == NULL)
    {
        list_status.code = FAILURE;
        return list_status;
    }

    if (list->head->data == element)
    {
        struct ListNode *temp = list->head;
        list->head = list->head->next;
        free(temp);
        list_status.code = SUCCESS;
        return list_status;
    }
    
    struct ListNode *prev_node = list->head;
    struct ListNode *curr_node = list->head->next;
    
    while (curr_node != NULL && curr_node->data != element)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    if (curr_node != NULL)
    {
        prev_node->next = curr_node->next;
        free(curr_node);
        list_status.code = SUCCESS;
    }
    else
    {
        list_status.code = FAILURE;
    }

    return list_status;
}

void print_list(struct MyList *list)
{
    struct ListNode *curr_node = list->head;
    printf("List: ");
    while (curr_node != NULL)
    {
        printf("%d ", curr_node->data);
        curr_node = curr_node->next;
    }
    printf("\n");
}

int main()
{
    struct MyList myList;
    initialize_list(&myList);

    int elements[] = {10, 20, 30, 40, 10, 50, 70, 90};
    int n = sizeof(elements) / sizeof(elements[0]);

    struct Status status;

    for (int i = 0; i < n; i++)
    {
        status = add_element(&myList, elements[i]);
        if (status.code == 0)
        {
            printf("Unable to add element %d to the list.\n", status.element);
        }
    }

    print_list(&myList);

    return 0;
}
