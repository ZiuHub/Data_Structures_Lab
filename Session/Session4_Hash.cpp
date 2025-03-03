// import libraries

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_table 10

struct Node{
    char name[40];
    Node *next;
}*head[max_table];

Node *createNewNode(const char *name){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

int hash(const char *name){
    int key = 0;
    for(int i = 0; i < strlen(name); i++){
        key += name[i];
        // key = key + name[i]
    }
    return key % max_table;
}

void push(const char *name){
    Node *newNode = createNewNode(name);
    // calculate hash key
    int pos = hash(name);
    // push
    // kondisi 1: head kosong
    if(head[pos] == NULL){
        head[pos] = newNode;
        return;
    }
    // kondisi 2: head ada (push tail)
    Node *temp = head[pos];
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
}

void pop(const char *name){
    int pos = hash(name);
    // kondisi 1: head[pos] kosong
    if(head[pos] == NULL){
        puts("Tidak ada data!");
        return;
    }
    // kondisi 2: head[pos] ada
    else{
        if(strcmp(head[pos]->name, name) == 0){
            Node *temp = head[pos];
            head[pos] = temp->next;
            free(temp);
        }
        else{
            Node *temp = head[pos];
            while(temp->next != NULL && strcmp(temp->next->name, name) != 0){
                temp = temp->next;
            }
            if(temp->next == NULL){
                puts("Tidak ada data!");
            }
            Node *toPop = temp->next;
            temp->next = toPop->next;
            free(toPop);
        }
    }
}

void print(){
    for(int i = 0; i < max_table; i++){
        Node *temp = head[i];
        printf("%d: ", i);
        while(temp){
            printf("%s -> ", temp->name);
            temp = temp->next;
        }
        puts("NULL");
    }
}

int main(){
    push("budi");
    push("lala");
    push("andi");
    push("agus");
    push("neo");
    push("ziva");
    push("jaden");
    push("nana");
    push("webe");
    puts("before pop:");
    print();
    puts("");
    pop("jaden");
    puts("after pop jaden:");
    print();
    puts("");
    pop("amba");
    puts("after pop amba:");
    print();

    return 0;
}