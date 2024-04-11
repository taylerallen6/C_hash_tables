#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct Node
{
    int value;
    struct Node* next;
} Node;

Node* hash_table[TABLE_SIZE];

// unsigned int hash(char* name)
// {
//     int length = strnlen(name, MAX_NAME);
//     unsigned int hash_value = 0;
//     for (int i=0; i < length; i++)
// {
//         hash_value += name[i];
//         hash_value = (hash_value * name[i]) % TABLE_SIZE;
//     }
//     return hash_value;
// }

unsigned int hash(int value)
{
    unsigned int hash_value;
    hash_value = (unsigned int)( value % TABLE_SIZE );

    return hash_value;
}

void init_hash_table()
{
    for (int i=0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
    //table is empty
}

void table_print_formatted()
{
    printf("Start\n");
    for (int i=0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n",i);
        }
        else
        {
            printf("\t%i\t ",i);
            Node* tmp = hash_table[i];
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

void table_print_all()
{
    for (int i=0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
            continue;

        Node* tmp = hash_table[i];
        while (tmp != NULL)
        {
            printf("%d, ", tmp->value);
            tmp = tmp -> next;
        }
    }
    printf("\n");
}

//find a Node in the table by their index
bool hash_table_value_check (int value)
{
    int index = hash(value);
    Node* tmp = hash_table[index];
    
    while (tmp != NULL)
    {
        if (tmp->value == value)
            return true;

        tmp = tmp->next;
    }

    return false;
}

bool hash_table_insert(int value)
{
    Node* tmp = malloc(sizeof(Node));
    tmp->value = value;

    int index = hash(value);
    tmp->next = hash_table[index];
    hash_table[index] = tmp;
    
    return true;
}

bool hash_table_insert_unique(int value)
{
    bool exists = hash_table_value_check(value);

    if (exists)
    {
        printf("already exists.\n");
        return false;
    }

    hash_table_insert(value);
    
    return true;
}

bool hash_table_delete(int value)
{
    int index = hash(value);
    Node* tmp = hash_table[index];
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
        hash_table[index] = tmp->next;
    }
    else
        prev->next = tmp->next;

    free(tmp);

    return true;
}

int main()
{
    init_hash_table();
    table_print_formatted();
    table_print_all();

    hash_table_insert_unique(0);
    hash_table_insert_unique(1);
    hash_table_insert_unique(2);
    hash_table_insert_unique(3);
    hash_table_insert_unique(3);
    hash_table_insert_unique(4);
    hash_table_insert_unique(5);
    hash_table_insert_unique(6);
    hash_table_insert_unique(13);
    hash_table_insert_unique(14);
    hash_table_insert_unique(44);
    hash_table_insert_unique(865);
    table_print_formatted();
    table_print_all();

    bool exists;
    exists = hash_table_value_check(3);
    if (exists)
        printf("Found it.\n");
    else
        printf("Not found!\n");
    
    exists = hash_table_value_check(5);
    if (exists)
        printf("Found it.\n");
    else
        printf("Not found!\n");

    hash_table_delete(3);
    exists = hash_table_value_check(3);
    if (exists)
        printf("Found it.\n");
    else
        printf("Not found!\n");

    table_print_formatted();
    table_print_all();

    hash_table_delete(14);
    hash_table_delete(2);

    table_print_formatted();
    table_print_all();


    return 0;
}