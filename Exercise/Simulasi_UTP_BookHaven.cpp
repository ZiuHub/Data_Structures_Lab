#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define SIZE 100
#define gc getchar();

struct Node{
    char borrowId[100];
    char name[100];
    char libraryId[100];
    char title[100];
    int duration;
    Node* next;
}*node[SIZE];

Node* createNode(char* borrowId, char* name, char* libraryId, char* title, int duration){
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    strcpy(newNode->borrowId, borrowId);
    strcpy(newNode->name, name);
    strcpy(newNode->libraryId, libraryId);
    strcpy(newNode->title, title);
    newNode->duration = duration;

    newNode->next = NULL;
    return newNode;
}

int getHash(char* borrowId){
    long long key = atoi(&borrowId[2]);
    key *= key;
    char keyString[100];
    sprintf(keyString, "%lld", key);
    int len = strlen(keyString);
    if(len % 2 == 0){
        key = (keyString[len/2-1] - '0')*10 + keyString[len/2] - '0';
    }
    else{
        key = keyString[len/2] - '0';
    }

    return key % SIZE;
}

void pushHash(Node* newNode){
    int key = getHash(newNode->borrowId);

    if(node[key] == NULL) node[key] = newNode;
    else{
        Node* temp = node[key];
        while(temp->next) temp->next;
        temp->next = newNode;
    }
}

bool validName(char* name){
    return strlen(name) >= 3 && strlen(name) <= 30;
}

bool validLibraryId(char* libraryId){
    return !strncmp(libraryId, "LIB-", 4) && isdigit(libraryId[4]) && isdigit(libraryId[5]) && isdigit(libraryId[6]) && isdigit(libraryId[7]) && isdigit(libraryId[8]) && strlen(libraryId) == 9;
}

bool validTitle(char* title){
    return strlen(title) >= 3 && strlen(title) <= 50;
}

bool validDuration(int duration){
    return duration >= 1 && duration <= 30;
}

void enter(){
    printf("Press ENTER to Continue...");
    gc
}

void borrow(){
    char borrowId[100], name[100], libraryId[100], title[100];
    int duration;

    do{
        printf("Enter your full name: ");
        scanf("%[^\n]", name); gc
        if(!validName(name)) puts("Full name must be 3-30 characters");
    }while(!validName(name));

    do{
        printf("Enter your library ID (format: LIB-xxxxx): ");
        scanf("%s", libraryId); gc
        if(!validLibraryId(libraryId)) puts("Library ID must start with 'LIB-' followed by exactly 5 digits)");
    }while(!validLibraryId(libraryId));

    do{
        printf("Enter book title: ");
        scanf("%[^\n]", title); gc
        if(!validTitle(title)) puts("Book Title must be 3-50 characters");
    }while(!validTitle(title));

    do{
        printf("Enter borrowing duration (1-30 days): ");
        scanf("%d", &duration); gc
        if(!validDuration(duration)) puts("Borrowing duration must between 1-30 days");
    }while(!validDuration(duration));

    sprintf(borrowId, "%c%c%d%d%d", toupper(title[0]), toupper(title[1]), rand()%10, rand()%10, rand()%10);

    pushHash(createNode(borrowId, name, libraryId, title, duration));
    puts("Book Borrowed Successfully!");
    printf("Borrowing ID: %s\n", borrowId);
    printf("Borrower Name: %s\n", name);
    printf("Library ID: %s\n", libraryId);
    printf("Book Title: %s\n", title);
    printf("Duration: %d\n", duration);
    enter();
}

bool view(){
    bool found = false;
    for(int i = 0; i < SIZE; i++){
        if(node[i] == NULL) continue;
        else{
            puts("Borrowed Books List:");
            found = true;
            Node* temp = node[i];
            while(temp){
                printf("Borrowing ID: %s\n", temp->borrowId);
                printf("Borrower Name: %s\n", temp->name);
                printf("Library ID: %s\n", temp->libraryId);
                printf("Book Title: %s\n", temp->title);
                printf("Duration: %d\n", temp->duration);
                puts("");
                temp = temp->next;
            }
        }
    }
    if(!found) puts("No books borrowed yet.");

    enter();
    return found;
}

void retur(){
    if(!view()) return;

    char borrowId[100];
    puts("");
    printf("Enter Borrowing ID to return: ");
    scanf("%s", borrowId); gc

    int key = getHash(borrowId);
    Node* temp = node[key];

    if(temp == NULL){
        puts("No books found!");
    }
    else if(strcmp(node[key]->borrowId, borrowId) == 0){
        node[key] = temp->next;
        free(temp);
        puts("Book Returned Successfully!");
        printf("Borrowing ID %s has been removed\n", borrowId);
        enter();
    }
    else{
        while(temp->next && strcmp(temp->next->borrowId, borrowId)){
            temp->next;
        }
        Node* toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
        puts("Book Returned Successfully!");
        printf("Borrowing ID %s has been removed\n", borrowId);
    }
    enter();
}

void printMenu(){
    puts("BookHaven Library Management");
    puts("1. Borrow a Book");
    puts("2. View Borrowed Books");
    puts("3. Return a Book");
    puts("4. Exit");
}

int main(){
    do{
        system("cls");
        printMenu();
        int choice;
        do{
            printf(">> ");
            scanf("%d", &choice); gc
            if(choice < 1 || choice > 4) puts("Choice must between 1-4");
        }while(choice < 1 || choice > 4);

        switch(choice){
            case 1:
                borrow();
                break;
            case 2:
                view();
                break;
            case 3:
                retur();
                break;
            case 4:
                return 0;
        }
    }while(1);
}