#define MAX_SIZE 100

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct
{
    Node **arr;
    int capacity;
    int size;
} MyHashSet;

MyHashSet *set = NULL;

int MyHashFunction(int key, int length)
{
    return key % length;
}

bool myHashSetContains(MyHashSet *obj, int key)
{
    int k = MyHashFunction(key, obj->capacity);
    Node *head = obj->arr[k];
    while (head != NULL)
    {
        if (head->data == key)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

MyHashSet *myHashSetCreate()
{
    set = (MyHashSet *)malloc(sizeof(MyHashSet));
    set->size = 0;
    set->capacity = MAX_SIZE;
    set->arr = (Node **)malloc(sizeof(Node *) * set->capacity);
    for (int i = 0; i < set->capacity; i++)
    {
        set->arr[i] = NULL;
    }
    return set;
}

void myHashSetAdd(MyHashSet *obj, int key)
{
    if (obj->size == obj->capacity)
    {
        int temp = obj->capacity;
        obj->capacity = obj->capacity + MAX_SIZE;
        obj->arr = (Node **)realloc(obj->arr, sizeof(Node *) * obj->capacity);
        for (int i = temp; i < obj->capacity; i++)
        {
            obj->arr[i] = NULL;
        }
    }

    int k = MyHashFunction(key, obj->capacity);
    if (!(myHashSetContains(obj, key)))
    {
        Node *newnode = (Node *)malloc(sizeof(Node));
        newnode->data = key;
        newnode->next = obj->arr[k];
        obj->arr[k] = newnode;
        obj->size = obj->size + 1;
    }
}

void myHashSetRemove(MyHashSet *obj, int key)
{
    int k = MyHashFunction(key, obj->capacity);
    if (myHashSetContains(obj, key))
    {
        Node *curr_node = obj->arr[k];
        Node *prev_node = NULL;
        while (curr_node != NULL && curr_node->data != key)
        {
            prev_node = curr_node;
            curr_node = curr_node->next;
        }
        if (prev_node != NULL)
        {
            prev_node->next = curr_node->next;
            free(curr_node);
        }
        else
        {
            obj->arr[k] = curr_node->next;
            free(curr_node);
        }
        obj->size = obj->size - 1;
    }
}

void myHashSetFree(MyHashSet *obj)
{
    for (int i = 0; i < obj->capacity; i++)
    {
        Node *temp = obj->arr[i];
        while (temp != NULL)
        {
            Node *prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(obj->arr);
    free(obj);
}
