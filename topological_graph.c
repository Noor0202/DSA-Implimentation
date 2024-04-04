#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NODE 1000

typedef struct node
{
    int value;
    struct node *next;
} node;

typedef struct edge
{
    int from, to;
} edge;

void add_exe_ord(int *exe_ord, node *adj_list[], int curr_node, int *in_degree, int *index, int *visited)
{
    visited[curr_node] = 1;
    exe_ord[*index] = curr_node;
    (*index)++;
    node *adj_node = adj_list[curr_node];
    while (adj_node != NULL)
    {
        in_degree[adj_node->value]--;
        if (in_degree[adj_node->value] == 0 && visited[adj_node->value] == 0)
        {
            add_exe_ord(exe_ord, adj_list, adj_node->value, in_degree, index, visited);
        }
        adj_node = adj_node->next;
    }
}

int *getexeorder(struct edge *e, int noOfEdges, int noOfNodes)
{
    node *adj_list[MAX_NODE] = {NULL};
    int in_degree[MAX_NODE] = {0};
    int visited[MAX_NODE] = {0};

    int *exe_ord = (int *)malloc(sizeof(int) * noOfNodes);
    int exe_ord_index = 0;

    int i = 0;
    while (i < noOfEdges)
    {
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        newnode->value = e[i].to;
        newnode->next = adj_list[e[i].from];
        adj_list[e[i].from] = newnode;
        in_degree[e[i].to]++;
        i = i + 1;
    }

    int k = 0;
    while (k < noOfEdges)
    {
        if (in_degree[e[k].from] == 0 && visited[e[k].from] == 0)
        {
            add_exe_ord(exe_ord, adj_list, e[k].from, in_degree, &exe_ord_index, visited);
        }
        k = k + 1;
    }
    return exe_ord;
}

int main()
{

    int no_of_nodes, no_of_edges;
    scanf("%d %d", &no_of_edges, &no_of_nodes);

    struct edge e[no_of_edges];
    int i = 0;
    while (i < no_of_edges)
    {
        scanf("%d %d", &e[i].from, &e[i].to);
        i = i + 1;
    }

    clock_t start_time = clock();
    int *result = getexeorder(e, no_of_edges, no_of_nodes);
    clock_t end_time = clock();
    int j = 0;
    printf("Topological Order: ");
    while (j < no_of_nodes)
    {
        printf(" %d ", result[j]);
        j = j + 1;
    }

    free(result);

    double et = (end_time - start_time) / (double)CLOCKS_PER_SEC;
    printf("\n Execution Time - %3.5lf\n", et);
    return 0;
}
