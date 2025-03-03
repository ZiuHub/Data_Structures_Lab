/*
SINGLE LINKED LIST
1. INSERT: Push Head, Push Tail, Push Mid
2. VIEW
3. SEARCH
4. DELETE: Pop Head, Pop Tail, Pop Mid
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {
    int key;
    char name[50];
    struct Data* next;
} *head = NULL, *tail = NULL;

struct Data* createData(int key, const char* name) {
    struct Data* newData = (struct Data*)malloc(sizeof(struct Data));
    newData->key = key;
    strcpy(newData->name, name);
    newData->next = NULL;
    return newData;
}

void pushHead(struct Data* newData) {
    if (head == NULL) {
        head = tail = newData;
    } else {
        newData->next = head;
        head = newData;
    }
}

void pushTail(struct Data* newData) {
    if (head == NULL) {
        head = tail = newData;
    } else {
        tail->next = newData;
        tail = newData;
    }
}

void pushMid(struct Data* newData) {
    if (head == NULL) {
        pushHead(newData);
    } else if (head->key > newData->key) {
        pushHead(newData);
    } else if (tail->key < newData->key) {
        pushTail(newData);
    } else {
        struct Data* curr = head;
        while (curr->next != NULL && curr->next->key < newData->key) {
            curr = curr->next;
        }
        newData->next = curr->next;
        curr->next = newData;
    }
}

void view() {
    struct Data* curr = head;
    while (curr != NULL) {
        printf("|%d - %s| -> ", curr->key, curr->name);
        curr = curr->next;
    }
    printf("NULL\n");
}

struct Data* search(const char* name) {
    struct Data* curr = head;
    while (curr != NULL) {
        if (strcasecmp(curr->name, name) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void popHead() {
    if (head == NULL) {
        return;
    } else if (head == tail) {
        free(head);
        head = tail = NULL;
    } else {
        struct Data* curr = head;
        head = head->next;
        free(curr);
    }
}

void popTail() {
    if (head == NULL) {
        return;
    } else if (head == tail) {
        free(head);
        head = tail = NULL;
    } else {
        struct Data* curr = head;
        while (curr->next != tail) {
            curr = curr->next;
        }
        free(tail);
        tail = curr;
        tail->next = NULL;
    }
}

void popMid(int key){
    if (head == NULL) {
        return;
    } else if (head->key == key) {
        popHead();
    } else if (tail->key == key) {
        popTail();
    } else {
        struct Data* curr = head;
        while (curr->next != NULL && curr->next->key != key) {
            curr = curr->next;
        }
        if (curr->next->key == key) {
            struct Data* temp = curr->next;
            curr->next = temp->next;
            free(temp);
        }
    }
}

int main() {
    pushMid(createData(4, "Budi"));
    pushTail(createData(7, "Agung"));
    pushHead(createData(2, "Leslie"));
    pushMid(createData(5, "Charlie"));

    view();

    // popHead();
    // popTail();
    popMid(5);
    view();

    // struct Data* result = search("Budi");
    // if (result == NULL) {
    //     puts("Not Found");
    // } else {
    //     printf("%s has key %d\n", result->name, result->key);
    // }

    return 0;
}