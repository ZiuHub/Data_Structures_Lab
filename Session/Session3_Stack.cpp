#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc & free

// struktur node
struct Node{
    int id;
    char nama[50];
    struct Node* prev;
    struct Node* next;
}*head, *tail;

struct Node* createNode(int id, const char nama[]){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    // inisialisasi
    newNode->id = id;
    strcpy(newNode->nama, nama);
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void pushHead(int id, const char nama[]){
    struct Node* newNode = createNode(id, nama);
    // kondisi 1: belum ada node
    if(head == NULL){
        head = tail = newNode;
    }
    // kondisi 2: sudah ada >= 1 node
    else{
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void pushTail(int id, const char nama[]){
    struct Node* newNode = createNode(id, nama);
    // kondisi 1: belum ada node
    if(head == NULL){
        head = tail = newNode;
    }
    // kondisi 2: sudah ada >= 1 node
    else{
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

void pushMid(int id, const char nama[]){
    // kondisi 1: belum ada node
    if(head == NULL){
        struct Node* newNode = createNode(id, nama);
        head = tail = newNode;
    }
    //. kondisi 2: jika id < head->id
    else if(id < head->id){
        pushHead(id, nama);
    }
    //. kondisi 3: jika id >= head->id
    else if(id >= tail->id){
        pushTail(id, nama);
    }
    // kondisi 4: berada di tengah linked list
    else{
        struct Node* newNode = createNode(id, nama);
        struct Node* curr = head;
        while(curr != NULL && curr->id <= newNode->id){
        curr = curr->next;
        }
        newNode->prev = curr->prev;
        newNode->next = curr;
        newNode->prev->next = newNode;
        curr->prev = newNode;
    }
}

struct Node* popHead(){
    // kondisi 1: belum ada node
    if(head == NULL){
        return NULL;
    }
    // kondisi 2: ada 1 node
    else if(head == tail){
        struct Node* temp = head;
        head = tail = NULL;
        return temp;
    }
    // kondisi 3: ketika ada >= 1 node
    else{
        struct Node* temp = head;
        head = head->next;
        head->prev = NULL;
        return temp;
    }
}

struct Node* popTail(){
    // kondisi 1: belum ada node
    if(head == NULL){
        return NULL;
    }
    // kondisi 2: ada 1 node
    else if(head == tail){
        struct Node* temp = head;
        head = tail = NULL;
        return temp;
    }
    // kondisi 3: ketika ada >= 1 node
    else{
        struct Node* temp = tail;
        tail = tail->prev;
        tail->next= NULL;
        return temp;
    }
}

struct Node* popMid(int id){
    // kondisi 1: belum ada node
    if(head == NULL){
        return NULL;
    }
    // kondisi 2: id == head->id
    else if(id == head->id){
        return popHead();
    }
    // kondisi 3: id == tail->id
    else if(id == tail->id){
        return popTail();
    }
    // kondisi 4: berada di tengah linked list
    else{
        struct Node* curr = head;
        while(curr != NULL && curr->id != id){
            curr = curr->next;
        }
        if(curr == NULL){
            return NULL;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        return curr;
    }
}

void forwardPrint(){
    struct Node* curr = head;
    while(curr != NULL){
        printf("%d %s <-> ", curr->id, curr->nama);
        curr = curr->next;
    }
    printf("NULL\n");
}

void backwardPrint(){
    struct Node* curr = tail;
    while(curr != NULL){
        printf("%d %s <-> ", curr->id, curr->nama);
        curr = curr->prev;
    }
    printf("NULL\n");
}

int main(){
    pushMid(1, "Andi");
    pushMid(3, "Budi");
    pushMid(2, "Chica");
    
    forwardPrint();

    struct Node* temp = popTail();
    if(temp != NULL){
        printf("Deleted %d %s\n", temp->id, temp->nama);
        free(temp);
    }
    else{
        printf("No data\n");
    }

    printf("Setelah delete: ");
    forwardPrint();

    return 0;
}