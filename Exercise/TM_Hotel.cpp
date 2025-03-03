#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HASH_SIZE 100
#define getch while(getchar()!='\n');

struct Booking{
    char fullname[35];
    char phonenumber[20];
    int age;
    char roomtype[10];
    int stayduration;
    char bookingid[10];
    struct Booking *next;
}*booking[HASH_SIZE];

int getHashKey(char* id){
    int x = 0;
    for(int i = 2; i < 5; i++){
        x += id[i]- '0';
    }
    return (x-1) % HASH_SIZE;
}

char toUpper(char x){
    // ternary
    // condition ? if true : if false
    return 'a' <= x && x <= 'z' ? x - ('a' - 'A') : x;
}

char* generateID(char* roomtype){
    // rand() % (max-min+1) + min
    char* id = (char*)malloc(sizeof(char)*7);
    for(int i = 0; i < 5; i++){
        id[i] = i < 2 ? toUpper(roomtype[i]) : rand() % 10 + '0';
    }
    id[5] = '\0';
    return id;
}

struct Booking* newBooking(char* fullname, char* phonenumber, int age, char* roomtype, int stayduration){
    char* bookingid = generateID(roomtype);

    struct Booking* curr = (struct Booking*)malloc(sizeof(struct Booking));
    strcpy(curr->fullname, fullname);
    strcpy(curr->phonenumber, phonenumber);
    curr->age = age;
    strcpy(curr->roomtype, roomtype);
    curr->stayduration = stayduration;
    strcpy(curr->bookingid, bookingid);

    curr->next = NULL;

    return curr;
}

void pushTail(struct Booking* newData){
    int hash = getHashKey(newData->bookingid);

    if(booking[hash] == NULL){
        booking[hash] = newData;
    }
    else{
        struct Booking* curr = booking[hash];
        while(curr->next) curr = curr->next;
        curr->next = newData;
    }
}

bool validFullName(char* fullname){
    int len = strlen(fullname);
    return len >= 3 && len <= 30;
}

bool validPhoneNumber(char* phonenumber){
    if(phonenumber[0] != '+' || phonenumber[1] != '6' || phonenumber[2] != '2'){
        return false;
    }

    int space = 0;
    int len = strlen(phonenumber);
    for(int i = 3; i < len; i++){
        if(phonenumber[i] == ' ') space++;
    }
    return space >= 1 && len - (space + 3) == 11;
}

bool validAge(int age){
    return age >= 18;
}

bool validRoomType(char* roomtype){
    return strcmp(roomtype, "Regular") == 0 || strcmp(roomtype, "Deluxe") == 0 || strcmp(roomtype, "Suite") == 0;
}

bool validStayDuration(int stayduration){
    return stayduration >= 1 && stayduration <= 30;
}

void createBooking(){
    char fullname[35];
    char phonenumber[20];
    int age;
    char roomtype[10];
    int stayduration;

    do{
        printf("Input Full Name: ");
        scanf("%[^\n]", fullname); getch
    }while(!validFullName(fullname));

    do{
        printf("Input Phone Number: ");
        scanf("%[^\n]", phonenumber); getch
    }while(!validPhoneNumber(phonenumber));

    do{
        printf("Input Age: ");
        scanf("%[^\n]", age); getch
    }while(!validAge(age));

    do{
        printf("Input Room Type: ");
        scanf("%[^\n]", roomtype); getch
    }while(!validRoomType(roomtype));

    do{
        printf("Input Stay Duration: ");
        scanf("%[^\n]", stayduration); getch
    }while(!validStayDuration(stayduration));

    pushTail(newBooking(fullname, phonenumber, age, roomtype, stayduration));
}

bool viewBooking(){
    bool found = false;
    for(int i = 0; i < HASH_SIZE; i++){
        struct Booking* curr = booking[i];
        while(curr){
            printf("Booking ID: %s\n", curr->bookingid);
            curr = curr->next;
            found = true;
        }
    }
    if(!found) printf("No booking found!\n");
    return found;
}

bool pop(char* bookingid){
    int hash = getHashKey(bookingid);

    struct Booking* curr = booking[hash];
    if(strcmp(curr->bookingid, bookingid) == 0){
        booking[hash] = curr->next;
        free(curr);
    }
    else{
        while(curr){
            if(strcmp(curr->next->bookingid, bookingid) == 0){
                struct Booking* temp = curr->next;
                curr->next = temp->next;
                free(temp);
                return true;
            }
            curr = curr->next;
        }
    }
}

void deleteBooking(){
    if(!viewBooking()) return;

    char bookingid[10];
    printf("Input Booking ID: ");
    scanf("%[^\n]", bookingid); getch

    if(pop(bookingid)){
        printf("Deleted ID %s!\n", bookingid);
    }
    else{
        printf("ID %s not found!\n", bookingid);
    }
}

int main(){
    srand(time(NULL));
    int menu = 0;
    do{
        system("cls");
        puts("1. Insert Booking");
        puts("2. View Booking");
        puts("3. Delete Booking");
        puts("4. Exit");
        printf(">> ");
        scanf("%d", &menu); getch

        switch(menu){
            case 1:
                createBooking();
                break;
            case 2:
                viewBooking();
                break;
            case 3:
                deleteBooking();
                break;
            case 4:
                return 0;
                break;
            default:
                puts("Invalid menu!");
        }
    }while(menu < 1 || menu > 4);

    return 0;
}