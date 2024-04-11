#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct Node
{
    char key[20];
    char value[100];
    struct Node* next;
} Node;

typedef struct
{
    Node** data;
    int table_size;
    int current_size;
} Hashtable;


Node* hashtable_node_create(char *key, char* value);
Hashtable* hashtable_create(int table_size);
void hashtable_free(Hashtable* hashtable);
void hashtable_print(Hashtable* hashtable);
void hashtable_print_formatted(Hashtable* hashtable);
void hashtable_set(Hashtable* hashtable, char *key, char* value);
char* hashtable_get(Hashtable* hashtable, char *key);
void hashtable_delete(Hashtable* hashtable, char* key);