#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct Node
{
    int value;
    struct Node* next;
} Node;

typedef struct
{
    Node** data;
    int table_size;
    int current_length;
} Hash_table;


unsigned int hash(Hash_table* hash_table, int value)
{
    unsigned int hash_value;
    hash_value = (unsigned int)( value % hash_table->table_size );

    return hash_value;
}

Hash_table* hash_table_create(int table_size)
{
    Hash_table* hash_table = malloc(sizeof(Hash_table));
    hash_table->table_size = table_size;

    hash_table->data = malloc(sizeof(Node*) * hash_table->table_size);
    for (int i=0; i < hash_table->table_size; i++)
    {
        hash_table->data[i] = NULL;
    }

    return hash_table;
}

void hash_table_free(Hash_table* hash_table)
{
    for (int i=0; i < hash_table->table_size; i++)
    {
        if (hash_table->data[i] == NULL)
            continue;

        Node* tmp = hash_table->data[i];
        while (tmp != NULL)
        {
            Node* node_for_deletion = tmp;
            tmp = tmp -> next;
            free(node_for_deletion);
        }
    }

    free(hash_table->data);
    free(hash_table);
}

void hash_table_print_formatted(Hash_table* hash_table)
{
    printf("Start\n");
    for (int i=0; i < hash_table->table_size; i++)
    {
        if (hash_table->data[i] == NULL)
        {
            printf("\t%i\t---\n",i);
        }
        else
        {
            printf("\t%i\t ",i);
            Node* tmp = hash_table->data[i];
            while (tmp != NULL)
            {
                printf("%d - ", tmp->value);
                tmp = tmp -> next;
            }
            printf("\n");
        }
    }
    printf("End\n");
}

void hash_table_print_all(Hash_table* hash_table)
{
    for (int i=0; i < hash_table->table_size; i++)
    {
        if (hash_table->data[i] == NULL)
            continue;

        Node* tmp = hash_table->data[i];
        while (tmp != NULL)
        {
            printf("%d, ", tmp->value);
            tmp = tmp -> next;
        }
    }
    printf("\n");
}

//find a Node in the table by their index
bool hash_table_value_check(Hash_table* hash_table, int value)
{
    int index = hash(hash_table, value);
    Node* tmp = hash_table->data[index];
    
    while (tmp != NULL)
    {
        if (tmp->value == value)
            return true;

        tmp = tmp->next;
    }

    return false;
}

bool hash_table_insert(Hash_table* hash_table, int value)
{
    Node* tmp = malloc(sizeof(Node));
    tmp->value = value;

    int index = hash(hash_table, value);
    tmp->next = hash_table->data[index];
    hash_table->data[index] = tmp;
    
    return true;
}

bool hash_table_insert_unique(Hash_table* hash_table, int value)
{
    bool exists = hash_table_value_check(hash_table, value);

    if (exists)
    {
        printf("already exists.\n");
        return false;
    }

    hash_table_insert(hash_table, value);
    
    return true;
}

bool hash_table_delete(Hash_table* hash_table, int value)
{
    int index = hash(hash_table, value);
    Node* tmp = hash_table->data[index];
    Node* prev = NULL;

    while (tmp != NULL && tmp->value != value)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return false;

    if (prev == NULL)
    {
        //deleting the head
        hash_table->data[index] = tmp->next;
    }
    else
        prev->next = tmp->next;

    free(tmp);

    return true;
}

int main()
{
    Hash_table* hash_table1 = hash_table_create(15);

    hash_table_print_formatted(hash_table1);
    hash_table_print_all(hash_table1);

    hash_table_insert_unique(hash_table1, 0);
    hash_table_insert_unique(hash_table1, 1);
    hash_table_insert_unique(hash_table1, 2);
    hash_table_insert_unique(hash_table1, 3);
    hash_table_insert_unique(hash_table1, 3);
    hash_table_insert_unique(hash_table1, 4);
    hash_table_insert_unique(hash_table1, 5);
    hash_table_insert_unique(hash_table1, 6);
    hash_table_insert_unique(hash_table1, 13);
    hash_table_insert_unique(hash_table1, 14);
    hash_table_insert_unique(hash_table1, 44);
    hash_table_insert_unique(hash_table1, 865);
    hash_table_print_formatted(hash_table1);
    hash_table_print_all(hash_table1);

    bool exists;
    exists = hash_table_value_check(hash_table1, 3);
    if (exists)
        printf("Found it.\n");
    else
        printf("Not found!\n");
    
    exists = hash_table_value_check(hash_table1, 5);
    if (exists)
        printf("Found it.\n");
    else
        printf("Not found!\n");

    hash_table_delete(hash_table1, 3);
    exists = hash_table_value_check(hash_table1, 3);
    if (exists)
        printf("Found it.\n");
    else
        printf("Not found!\n");

    hash_table_print_formatted(hash_table1);
    hash_table_print_all(hash_table1);

    hash_table_delete(hash_table1, 14);
    hash_table_delete(hash_table1, 2);

    hash_table_print_formatted(hash_table1);
    hash_table_print_all(hash_table1);


    hash_table_free(hash_table1);

    return 0;
}