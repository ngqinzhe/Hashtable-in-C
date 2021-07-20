#include <stdlib.h>
#include <stdio.h>
#include <string.h>


const int SIZE = 10;

typedef struct node {
    int value;
    char* key;
    struct node* next; 
} node;

typedef struct LinkedList{
    node* root;
} LinkedList;

typedef struct Hashtable {
    LinkedList array[SIZE];
} Hashtable;

node* createNode(char* name, int data) {
    node* n = malloc(sizeof(node));
    n->key = name;
    n->value = data;
    n->next = NULL;
    return n;
}

int hashcode(node* n) {
    char* key = n->key;
    int code = 0;
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        code += key[i];
    }
    return code % SIZE;
}

void getValue(char* string, Hashtable* hashtable) {
    int len = strlen(string);
    int code = 0;
    for (int i = 0; i < len; i++) {
        code += string[i];
    }
    code = code % SIZE;
    // search in the hashtable
    if (hashtable->array[code].root == NULL) {
        printf("%s doesn't exist in the Hash Table\n", string);
        return;
    }
    node* tmp = hashtable->array[code].root;
    while (tmp != NULL) {
        if (tmp->key == string) {
            printf("Key found! Value is: %d\n", tmp->value);
            return;
        }
        tmp = tmp->next;
    }
    printf("%s doesn't exist in the Hash Table\n", string);
}

Hashtable* insert(node* n, Hashtable* hashtable) {
    int code = hashcode(n);
    if (hashtable->array[code].root == NULL) {
        hashtable->array[code].root = n;
        return hashtable;
    }
    node* tmp = hashtable->array[code].root;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = n;
    return hashtable;
}

Hashtable* delete(node* n, Hashtable* hashtable) {
    int code = hashcode(n);
    if (hashtable->array[code].root == NULL) {
        printf("Node doesn't exist, nothing to remove.\n");
        return hashtable;
    }
    node* tmp = hashtable->array[code].root;
    while (tmp != NULL) {
        // if it is the first key and there are no keys thereafter
        if (tmp->key == n->key && tmp->value == n->value) {
            if (tmp->next == NULL) {
                free(tmp);
                hashtable->array[code].root = NULL;
                printf("Node removed from table.\n");
                return hashtable;
            } else {
                node* tmpnext = tmp->next;
                hashtable->array[code].root = tmpnext;
                free(tmp);
                printf("Node removed from table.\n");
                return hashtable;
            }
        }
        if (tmp->next->key == n->key && tmp->next->value == n->value) {
            if (tmp->next->next == NULL) {
                free(tmp->next);
                tmp->next = NULL;
                printf("Node removed from table.\n");
                return hashtable;
            } else {
                node* tmpnext = tmp->next;
                tmp->next = tmpnext->next;
                free(tmpnext);
                printf("Node removed from table.\n");
                return hashtable;
            }
        }
        tmp = tmp->next;
    }
    printf("Node doesn't exist, nothing to remove.\n");
    return hashtable;
}

void printTable(Hashtable* hashtable) {
    for (int i = 0; i < SIZE; i++) {
        if (hashtable->array[i].root == NULL) {
            printf("%d. EMPTY\n", i);
            continue;
        }
        node* tmp = hashtable->array[i].root;
        printf("%d. ", i);
        while (tmp != NULL) {
            printf("%s ->", tmp->key);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

void freeMem(Hashtable* hashtable) {
    for (int i = 0; i < SIZE; i++) {
        if (hashtable->array[i].root == NULL) {
            continue;
        }
        node* tmp = hashtable->array[i].root;
        while (tmp != NULL) {
            node* tmpnext = tmp->next;
            free(tmp);
            tmp = tmpnext;
        }
        hashtable->array[i].root = NULL;
    }
    free(hashtable);
    hashtable = NULL;
    printf("Memory freed.\n");
    return;
} 

int main() {
    Hashtable* hash = malloc(sizeof(Hashtable));
    node* n = createNode("hello", 3);
    node* n2 = createNode("H", 2);
    hash = insert(n, hash);
    hash = insert(n2, hash);
    getValue("hello", hash);
    printTable(hash);
    hash = delete(n, hash);
    printTable(hash);
    getValue("hello", hash);
    freeMem(hash);
    printTable(hash);
}