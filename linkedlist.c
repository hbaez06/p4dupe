#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

struct linkedlist
{
    struct linkedlist_node *first;
    // TODO1: define linked list metadata
    // metadata is size
    int size;
};

struct linkedlist_node
{
    // TODO2 started: define the linked list node

    int key;                      //key
    int value;                    //value
    struct linkedlist_node *next; //pointer to next node
};
typedef struct linkedlist_node linkedlist_node_t;

linkedlist_t *ll_init()
{
    // TODO3: create a new linked list

    // We have done this TODO for you as an example of how to use malloc().
    // You might want to read more about malloc() from Linux Manual page.
    // Usually free() should be used together with malloc(). For example,
    // the linkedlist you are currently implementing usually have free() in the
    // ll_delete() function. Since we are not asking you to implement
    // the ll_delete() function, you will not be using free() in this case.

    // First, you use C's sizeof function to determine
    // the size of the linkedlist_t data type in bytes.
    // Then, you use malloc to set aside that amount of space in memory.
    // malloc returns a void pointer to the memory you just allocated, but
    // we can assign this pointer to the specific type we know we created
    linkedlist_t *list = malloc(sizeof(linkedlist_t));

    // TODO4: set metadata for your new list and return the new list
    list->size = 0;
    return list;
}
void ll_free_helper(linkedlist_node_t *node)
{
    if (node->next != NULL)
    {
        ll_free_helper(node->next);
    }
    free(node->next);
}
void ll_free(linkedlist_t *list)
{
    // TODO5: free a linked list from memory
    // ll_free_helper(list->first); DOESNT WORK
    free(list);
}

void ll_add(linkedlist_t *list, int key, int value)
{
    // TODO6: create a new node and add to the front of the linked list if a
    // node with the key does not already exist.
    // Otherwise, replace the existing value with the new value.
    linkedlist_node_t *new_node = malloc(sizeof(linkedlist_node_t));
    new_node->key = key;
    new_node->value = value;

    if (list->size == 0)
    {
        new_node->key = key;
        new_node->value = value;
        new_node->next = NULL;
        list->first = new_node;
        list->size = list->size + 1;
    }
    else
    {
        int counter = 0;
        linkedlist_node_t *curr = list->first;
        while (counter == 0)
        {
            if ((list->first->key) == (key))
            {
                curr->value = value;
                counter = 1;
            }
            else
            {
                if (curr->next == NULL)
                {
                    new_node->key = key;
                    new_node->value = value;
                    new_node->next = list->first;
                    list->first = new_node;
                    list->size = list->size + 1;
                }
                else
                {
                    curr = curr->next;
                }
            }
        }
    }
}

int ll_get(linkedlist_t *list, int key)
{
    // TODO7: go through each node in the linked list and return the value of
    // the node with a matching key.
    // If it does not exist, return 0.
    int counter = 0;
    linkedlist_node_t *curr = list->first;
    if (list->size == 0)
    {
        return 0;
    }
    while (counter == 0)
    {
        if ((curr->key) == key)
        {
            counter = 1;
            return curr->value;
        }
        else
        {
            if (curr->next == NULL)
            {
                return 0;
            }
            else
            {
                curr = curr->next;
            }
        }
    }
    return 0;
}

int ll_size(linkedlist_t *list)
{
    // TODO8: return the number of nodes in this linked list
    return list->size;
}
