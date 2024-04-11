#include "hashtable5.h"


unsigned int hash(Hashtable* hashtable, char* key)
{
    unsigned int hash_value = 0;
    unsigned int key_length = strlen(key);
    for (int i = 0; i < key_length; i++)
    {
        hash_value = hash_value * key_length + key[i];
    }
    
    hash_value = hash_value % hashtable->table_size;

    return hash_value;
}

Node* hashtable_node_create(char *key, char* value)
{
    Node* new_node = malloc(sizeof(Node));

    strcpy(new_node->key, key);
    strcpy(new_node->value, value);

    new_node->next = NULL;

    return new_node;
}

void hashtable_node_free(Node* node)
{
    free(node);
}

Hashtable* hashtable_create(int table_size)
{
    Hashtable* hashtable = malloc(sizeof(Hashtable));
    hashtable->table_size = table_size;
    hashtable->current_size = 0;

    hashtable->data = malloc(sizeof(Node*) * hashtable->table_size);
    for (int i=0; i < hashtable->table_size; i++)
    {
        hashtable->data[i] = NULL;
    }

    return hashtable;
}

void hashtable_free(Hashtable* hashtable)
{
    for (int i=0; i < hashtable->table_size; i++)
    {
        if (hashtable->data[i] == NULL)
            continue;

        Node* tmp = hashtable->data[i];
        while (tmp != NULL)
        {
            Node* node_for_deletion = tmp;
            tmp = tmp -> next;
            hashtable_node_free(node_for_deletion);
        }
    }

    free(hashtable->data);
    free(hashtable);
}

void hashtable_print(Hashtable* hashtable)
{
    printf("{");
    
    if (hashtable->current_size != 0)
        printf("\n");
    
    for (int i=0; i < hashtable->table_size; i++)
    {
        if (hashtable->data[i] == NULL)
            continue;

        Node* tmp = hashtable->data[i];
        while (tmp != NULL)
        {
            printf("\t%s: %s,\n", tmp->key, tmp->value);
            tmp = tmp -> next;
        }
    }
    printf("}\n");
    printf("current_size: %d\n", hashtable->current_size);
}

void hashtable_print_formatted(Hashtable* hashtable)
{
    printf("{\n");
    for (int i=0; i < hashtable->table_size; i++)
    {
        if (hashtable->data[i] == NULL)
        {
            printf("\t%i\t---\n",i);
        }
        else
        {
            printf("\t%i\t",i);
            Node* tmp = hashtable->data[i];
            while (tmp != NULL)
            {
                printf("%s - ", tmp->key);
                tmp = tmp -> next;
            }
            printf("\n");
        }
    }
    printf("}\n");
    printf("current_size: %d\n", hashtable->current_size);
}

void hashtable_set(Hashtable* hashtable, char *key, char* value)
{
    unsigned int slot = hash(hashtable, key);
    Node* entry = hashtable->data[slot];

    if (entry == NULL)
    {
        hashtable->data[slot] = hashtable_node_create(key, value);
        hashtable->current_size++;
        return;
    }

    Node* prev_node;

    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
        {
            strcpy(entry->value, value);
            return;
        }

        prev_node = entry;
        entry = prev_node->next;
    }

    prev_node->next = hashtable_node_create(key, value);
    hashtable->current_size++;
}

char* hashtable_get(Hashtable* hashtable, char *key)
{
    unsigned int slot = hash(hashtable, key);
    Node* entry = hashtable->data[slot];

    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
            return entry->value;
        
        entry = entry->next;
    }

    return NULL;
}

void hashtable_delete(Hashtable* hashtable, char* key)
{
    int index = hash(hashtable, key);
    Node* tmp = hashtable->data[index];
    Node* prev = NULL;

    while (tmp != NULL && strcmp(tmp->key, key) != 0)
    {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL)
        return;

    if (prev == NULL)
        hashtable->data[index] = tmp->next;
    else
        prev->next = tmp->next;

    hashtable_node_free(tmp);
    hashtable->current_size--;
}