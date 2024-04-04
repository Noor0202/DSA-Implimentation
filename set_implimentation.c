#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

enum StatusCode {
    FAILURE,
    SUCCESS
};

struct Status {
    enum StatusCode code;
    int element;
};

struct MySet {
    int *arr;
    int arr_size;
    int arr_capacity;
};

int check_element(struct MySet *set, int element);

void initializeSet(struct MySet *set) {
    set->arr_capacity = MAX_SIZE;
    set->arr = (int *)malloc(set->arr_capacity * sizeof(int));
    set->arr_size = 0;
}

struct Status add_element(struct MySet *set, int element) {
    struct Status set_status;
    set_status.element = element;

    if (!check_element(set, element))
    {

        if (set->arr_size >= set->arr_capacity)
        {
            set->arr_capacity *= 2;
            set->arr = (int *)realloc(set->arr, set->arr_capacity * sizeof(int));
        }
        
        set->arr[set->arr_size++] = element;
        set_status.code = SUCCESS;
    }
    
    else
    {
        set_status.code = FAILURE;
    }

    return set_status;
}

struct Status remove_element(struct MySet *set, int element) {
    struct Status set_status;
    set_status.element = element;

    for (int i = 0; i < set->arr_size; i++) {
        if (set->arr[i] == element) {
            for (int j = i; j < set->arr_size - 1; j++) {
                set->arr[j] = set->arr[j + 1];
            }
            set->arr_size--;
            set_status.code = SUCCESS;
            return set_status;
        }
    }
    set_status.code = FAILURE;
    return set_status;
}

int check_element(struct MySet *set, int element) {
    for (int i = 0; i < set->arr_size; i++) {
        if (set->arr[i] == element) {
            return 1;
        }
    }
    return 0;
}

void print_set(struct MySet *set) {
    printf("Set: { ");
    for (int i = 0; i < set->arr_size; i++) {
        printf("%d ", set->arr[i]);
    }
    printf("}\n");
}

int main() {
    struct MySet mySet;
    initializeSet(&mySet);

    int elements[] = {10, 20, 30, 40, 50, 10, 20, 60};
    int n = sizeof(elements) / sizeof(elements[0]);

    struct Status status;

    for (int i = 0; i < n; i++) {
        status = add_element(&mySet, elements[i]);
        if (status.code == 1)
            printf("Element %d added to the set.\n", status.element);
        else
            printf("Element %d already present in the set.\n", status.element);
    }

    printf("Set after addition:\n");
    print_set(&mySet);

    status = remove_element(&mySet, 20);
    if (status.code == 1)
        printf("Element %d removed from the set.\n", status.element);
    else
        printf("Element %d not found in the set.\n", status.element);

    status = remove_element(&mySet, 90);
    if (status.code == 1)
        printf("Element %d removed from the set.\n", status.element);
    else
        printf("Element %d not found in the set.\n", status.element);

    printf("Set after removal:\n");
    print_set(&mySet);

    free(mySet.arr);

    return 0;
}
