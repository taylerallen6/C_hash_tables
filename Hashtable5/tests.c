#include "hashtable5.h"


int main()
{
    Hashtable* table = hashtable_create(3);

    hashtable_print(table);
    printf("\n");

    hashtable_set(table, "name", "tayler");
    hashtable_set(table, "age", "26");
    hashtable_set(table, "notes", "random data");

    hashtable_print(table);
    printf("\n");

    char* data = hashtable_get(table, "name");
    printf("name: %s\n", data);
    char* data2 = hashtable_get(table, "age");
    printf("age: %s\n", data2);
    char* data3 = hashtable_get(table, "notes");
    printf("notes: %s\n", data3);

    printf("\n");

    hashtable_delete(table, "notes");
    hashtable_print(table);
    hashtable_delete(table, "notes");
    hashtable_print(table);

    hashtable_delete(table, "name");
    hashtable_print(table);

    hashtable_delete(table, "age");
    hashtable_print(table);
    

    return 0;
}