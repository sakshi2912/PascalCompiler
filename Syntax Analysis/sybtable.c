#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTOKENLEN 31
//
typedef struct Node
{
    int length;
    char *par_type; // int , char
    char *var_name;
    // to store value
    int ival;
    double fval;
    char *st_sval;
    int line_no_d;
    int line_no_u;
    char *scope;
    struct Node *next;
} Node;

void print_tab(Node *node)
{
    if (node != NULL)
    {
        printf("\nIdentifier  Type  Line_Number  Scope\n");
        for (Node *temp = node; temp != NULL; temp = temp->next)
        {
            printf("%s\t  %s\t  %d\t%s\n", temp->var_name, temp->par_type, temp->line_no_d, temp->scope);
        }
    }
    return;
}
int search(Node *first, char *name, char *scope, int line_no_u)
{
    Node *temp = first;
    while (temp != NULL)
    {
        if ((strcmp(temp->var_name, name) == 0) && (strcmp(temp->scope, scope) == 0))
        {
            return 1;
        }
        temp = temp->next;
    }
    printf("\n%s is not defined at line no:%d\n", name, line_no_u);
    return -1; //false
}

Node *insert(Node *node, char *name, int lineno, char *scope)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (search(node, name, scope, lineno) == 1)
    {
        printf("Already found\n");
        return node;
    }
    temp->var_name = name;
    temp->scope = scope;
    temp->line_no_d = lineno;
    temp->next = NULL;
    if (node == NULL)
    {
        return temp;
    }
    Node *tem = node;
    while (tem->next != NULL)
    {
        tem = tem->next;
    }
    tem->next = temp;
    printf("Inserted successfully\n");
    return node;
}
Node *delete (Node *first, char *name, int lineno, char *scope)
{
    Node *x, *temp;
    if (first == NULL)
    {
        return first;
    }
    x = first;
    // assuming that the search function returns a true or false!
    int res = search(first, name, scope, lineno);
    if (res == -1)
    {
        printf("The identifier is not found\n");
        return first;
    }
    else
    {
        if (strcmp(first->var_name, name) == 0)
        {
            temp = first;
            first = first->next;
            free(temp);
        }
        else
        {
            temp = x->next;
            while (strcmp(temp->var_name, name) != 0 || temp->next != NULL)
            {
                x = x->next;
                temp = temp->next;
            }
            x->next = temp->next;
        }
        return first;
    }
}

int main()
{
    Node *node = NULL;
    node = insert(node, "First", 89, "global");
    node = insert(node, "First", 89, "global");
    node = insert(node, "sew", 84, "local");
    node = insert(node, "hello", 98, "local");
    print_tab(node);
    node = delete (node, "First", 84, "local");
    print_tab(node);
    printf("\nEnding gracefully\n");
    return 0;
}