#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define SIZE 100
#define gc getchar();

struct Node{
    char name[100];
    char studentID[100];
    char subject[100];
    char time[100];
    char attendanceID[100];
    Node* next;
}*node[SIZE];

void enter(){
    printf("Press ENTER to Continue...");
    gc
    return;
}

Node* createNode(char* name, char* studentID, char* subject, char* time, char* attendanceID){
    Node* newNode = (Node*)malloc(sizeof(Node));

    strcpy(newNode->name, name);
    strcpy(newNode->studentID, studentID);
    strcpy(newNode->subject, subject);
    strcpy(newNode->time, time);
    strcpy(newNode->attendanceID, attendanceID);

    newNode->next = NULL;
    return newNode;
}

int getHash(char* attendanceID){
    int key;
    sscanf(attendanceID + 2, "%d", &key);
    key *= key;
    char stringKey[100];
    sprintf(stringKey, "%d", key);
    int len = strlen(stringKey);
    if(len % 2 == 0){
        key = (stringKey[len/2-1] - '0') * 10 + stringKey[len/2] - '0';
    }
    else{
        key = stringKey[len/2] - '0';
    }

    return key % SIZE;
}

void pushHash(Node* newNode){
    int key = getHash(newNode->attendanceID);
    Node* temp = node[key];
    
    if(temp == NULL){
        node[key] = newNode;
    }
    else{
        while(temp->next) temp = temp->next;
        temp->next = newNode;
    }
    return;
}

bool validName(char* name){
    return strlen(name) >= 3 && strlen(name) <= 30;
}

bool validStudentID(char* studentID){
    return !strncmp(studentID, "ST-", 3) && isdigit(studentID[3]) && isdigit(studentID[4]) && isdigit(studentID[5]) && isdigit(studentID[6]) && isdigit(studentID[7]) && strlen(studentID) == 8;
}

bool validSubject(char* subject){
    return strlen(subject) >= 3 && strlen(subject) <= 50;
}

bool validTime(char* time){
    return strlen(time) == 5 && isdigit(time[0]) && isdigit(time[1]) && time[2] == ':' && isdigit(time[3]) && isdigit(time[4]);
}

void add(){
    char name[100], studentID[100], subject[100], time[100], attendanceID[100];

    do{
        printf("Enter your name [3-30 characters]: ");
        scanf("%[^\n]", name); gc
        if(!validName(name)) puts("Name must be 3-30 characters");
    }while(!validName(name));

    do{
        printf("Enter your student ID [ST-*****]: ");
        scanf("%s", studentID); gc
        if(!validStudentID(studentID)) puts("Student ID must starts with 'ST-' and followed by 5 digits");
    }while(!validStudentID(studentID));

    do{
        printf("Enter subject [3-50 characters]: ");
        scanf("%[^\n]", subject); gc
        if(!validSubject(subject)) puts("Subject must be 3-50 characters");
    }while(!validSubject(subject));

    do{
        printf("Enter attendance time [HH:MM]: ");
        scanf("%s", time); gc
        if(!validTime(time)) puts("Attendance time must follows the format [HH:MM]");
    }while(!validTime(time));

    sprintf(attendanceID, "%c%c%d%d%d", toupper(subject[0]), toupper(subject[1]), rand() % 10, rand() % 10, rand() % 10);

    pushHash(createNode(name, studentID, subject, time, attendanceID));
    puts("Attendance log has been added!");
    enter();
    return;
}

bool view(){
    bool found = false;
    for(int i = 0; i < SIZE; i++){
        if(node[i] == NULL) continue;
        else{
            found = true;
            Node* temp = node[i];
            while(temp){
                printf("Attendance ID: %s\n", temp->attendanceID);
                printf("Name: %s\n", temp->name);
                printf("Student ID: %s\n", temp->studentID);
                printf("Subject: %s\n", temp->subject);
                printf("Time: %s\n", temp->time);
                puts("");
                temp = temp->next;
            }
        }
    }
    if(!found) puts("There is no students attendance yet");
    enter();
    return found;
}

void remove(){
    if(!view()) return;

    char attendanceID[100];
    puts("");
    printf("Enter attendance ID to remove: ");
    scanf("%s", attendanceID); gc

    int key = getHash(attendanceID);
    Node* temp = node[key];

    if(temp == NULL){
        puts("Not found");
    }
    else if(!strcmp(temp->attendanceID, attendanceID)){
        node[key] = temp->next;
        free(temp);
        puts("Attendance log removed successfully");
    }
    else{
        while(temp->next && strcmp(temp->next->attendanceID, attendanceID)) temp = temp->next;
        Node* toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
        puts("Attendance log removed successfully");
    }
    enter();
    return;
}
void printMenu(){
    puts("Attendance Logs System");
    puts("1. Add attendance log");
    puts("2. View attendance logs");
    puts("3. Remove attendance log");
    puts("4. Exit");
    return;
}

int main(){
    srand(time(NULL));
    do{
        system("cls");
        printMenu();
        printf(">> ");
        int choice;
        scanf("%d", &choice); gc
        switch(choice){
            case 1:
                add();
                break;
            case 2:
                view();
                break;
            case 3:
                remove();
                break;
            case 4:
                return 0;
        }
    }while(1);

    return 0;
}