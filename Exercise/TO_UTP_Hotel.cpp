#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define HASH_SIZE 100
#define gc getchar();

struct Booking{
    char name[35];
    char phoneNum[20];
    int age;
    char roomType[10];
    int stayDuration;
    char bookingId[10];
    struct Booking *next;
}*booking[HASH_SIZE];

void enterToContinue(){
    printf("Press ENTER to Continue..."); gc
}

char* generateID(char* roomType){
    char* id = (char*)malloc(sizeof(7));
    sprintf(id, "%c%c%d%d%d", toupper(roomType[0]), toupper(roomType[1]), rand() % 10, rand() % 10, rand() % 10);
    return id;
}

Booking* createBooking(char* name, char* phoneNum, int age, char* roomType, int stayDurartion){
    Booking* newBooking = (Booking*)malloc(sizeof(Booking));
    char* bookingId = generateID(roomType);
    
    strcpy(newBooking->name, name);
    strcpy(newBooking->phoneNum, phoneNum);
    newBooking->age = age;
    strcpy(newBooking->roomType, roomType);
    newBooking->stayDuration = stayDurartion;
    strcpy(newBooking->bookingId, bookingId);
    
    newBooking->next = NULL;
    return newBooking;
}

int getHashKey(char* id){
    int key = 0;
    for(int i = 2; i < 5; i++){
        key += id[i] - '0';
    }
    key -= 1;
    
    return key % HASH_SIZE;
}

void pushHash(Booking* c){
    int key = getHashKey(c->bookingId);
    if(booking[key] == NULL) booking[key] = c;
    else{
        Booking* temp = booking[key];
        while(temp->next) temp = temp->next;
        temp->next = c;
    }
}

bool validName(char* name){
    return strlen(name) >= 3 && strlen(name) <= 30;
}

bool validPhoneNum(char* phoneNum){
    bool found = false;
    int len = strlen(phoneNum);
    for(int i = 0; i < len; i++){
        if(phoneNum[i] == ' ') found = true;
    }

    return phoneNum[0] == '+' && phoneNum[1] == '6' && phoneNum[2] == '2' && found == true && len >= 7 && len <= 34;
}

bool validAge(int age){
    return age >= 18;
}

bool validRoomType(char* roomType){
    return strcmp(roomType, "Regular") == 0 || strcmp(roomType, "Deluxe") == 0 || strcmp(roomType, "Suite") == 0;
}

bool validStayDuration(int stayDuration){
    return stayDuration >= 1 && stayDuration <= 30;
}

void book(){
    char name[100], phoneNum[100], roomType[100];
    int age, stayDurartion;

    do{
        printf("Input Full Name [3-30]: ");
        scanf("%[^\n]", name); gc
        if(!validName(name)) puts("Full name length must between 3 and 30");
    }while(!validName(name));

    do{
        printf("Input Phone Number: ");
        scanf("%[^\n]", phoneNum); gc
        if(!validPhoneNum(phoneNum)) puts("Phone number must begin with '+62', contains with at least 1 space and the length must be 11 (Exclude +62 and space)");
    }while(!validPhoneNum(phoneNum));

    do{
        printf("Input Age [Minimum 18]: ");
        scanf("%d", &age); gc
        if(!validAge(age)) puts("Age must be minimum 18");
    }while(!validAge(age));
    
    do{
        printf("Input Room Type [Regular|Deluxe|Suite] (Case Sensitive): ");
        scanf("%s", roomType); gc
        if(!validRoomType(roomType)) puts("Room type must be either Regular or Deluxe or Suite (Case sensitive)");
    }while(!validRoomType(roomType));

    do{
        printf("Input How Many Night You Will Stay [1-30]: ");
        scanf("%d", &stayDurartion); gc
        if(!validStayDuration(stayDurartion)) puts("You can't stay less than 1 night or more than 30 nights");
    }while(!validStayDuration(stayDurartion));

    pushHash(createBooking(name, phoneNum, age, roomType, stayDurartion));
    enterToContinue();
}

bool view(){
    bool found = false;
    for(int i = 0; i < HASH_SIZE; i++){
        if(booking[i] == NULL) continue;

        found = true;
        Booking* temp = booking[i];
        while(temp){
            puts("");
            printf("Booking ID: %s\n", temp->bookingId);
            printf("Full Name: %s\n", temp->name);
            printf("Phone Number: %s\n", temp->phoneNum);
            printf("Room Type: %s\n", temp->roomType);
            printf("Night Stay: %d night(s)\n", temp->stayDuration);
            temp = temp->next;
        }
    }
    if(found == false) puts("There is no booking!");
    enterToContinue();
    return found;
}

void pop(){
    if(!view()){
        return;
    }

    bool found = false;
    char id[10];
    puts("");
    printf("Input Booking ID: ");
    scanf("%s", id); gc

    int key = getHashKey(id);
    
    if(booking[key] == NULL){
        puts("Not found!");
        enterToContinue();
        return;
    }
    else if(strcmp(booking[key]->bookingId, id) == 0){
        found = true;
        booking[key] = NULL;
        printf("BookingID %s is Successfully Deleted!\n", id);
        enterToContinue();
    }
    else{
        found = true;
        Booking* temp = booking[key];
        while(temp->next && strcmp(temp->next->bookingId, id)){
            temp = temp->next;
        }
        Booking* toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
        printf("BookingID %s is Successfully Deleted!\n", id);
        enterToContinue();
    }
    if(!found){
        puts("Failed to Delete, There is No Data!");
    }
}

void printMenu(){
    system("cls");
    puts("Hotel GrAnsylvania");
    puts("1. Booking Hotel");
    puts("2. View Bookings");
    puts("3. Delete Bookings");
    puts("4. Exit");
}

int main(){
    srand(time(NULL));

    do{
        printMenu();
        int choice;
        printf(">> ");
        scanf("%d", &choice); gc

        switch(choice){
            case 1:
                book();
                break;
            case 2:
                view();
                break;
            case 3:
                pop();
                break;
            case 4:
                return 0;
        }
    }while(1);
}