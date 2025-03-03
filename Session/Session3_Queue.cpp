#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// enqueue -> push tail
// dequeue -> pop head
// front -> data depan/head
// rear -> data belakang/tail

void pushMid(int priority, const char nama[]);

// struktur node
struct Node{
    int priority;
    char nama[50];
    struct Node* prev;
    struct Node* next;
}*head, *tail;

struct Node* createNode(int priority, const char nama[]){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    // inisialisasi
    newNode->priority = priority;
    strcpy(newNode->nama, nama);
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void enqueue(int priority, const char nama[]){
    struct Node* newNode = createNode(priority, nama);
    // kondisi 1: belum ada node
    if(head == NULL){
        head = tail = newNode;
    }
    // kondisi 2: sudah ada >= 1 node
    else if (head == tail){
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    else{
        pushMid(priority, nama);
    }
}

struct Node* dequeue(){
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

void pushHead(int priority, const char nama[]){
    struct Node* newNode = createNode(priority, nama);
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

void pushMid(int priority, const char nama[]){
    // kondisi 1: belum ada node
    if(head == NULL){
        struct Node* newNode = createNode(priority, nama);
        head = tail = newNode;
    }
    //. kondisi 2: jika priority < head->priority
    else if(priority < head->priority){
        pushHead(priority, nama);
    }
    //. kondisi 3: jika priority >= head->priority
    else if(priority >= tail->priority){
        enqueue(priority, nama);
    }
    // kondisi 4: berada di tengah linked list
    else{
        struct Node* newNode = createNode(priority, nama);
        struct Node* curr = head;
        while(curr != NULL && curr->priority <= newNode->priority){
        curr = curr->next;
        }
        newNode->prev = curr->prev;
        newNode->next = curr;
        newNode->prev->next = newNode;
        curr->prev = newNode;
    }
}

void getFront(){
    printf("%d %s\n", head->priority, head->nama);
}

void getRear(){
    printf("%d %s\n", tail->priority, tail->nama);
}

int main(){
    enqueue(1, "Andi");
    enqueue(2, "Budi");
    dequeue();

    getFront();
    getRear();

    return 0;
}