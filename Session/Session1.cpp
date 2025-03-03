#include <stdio.h>
#include <stdlib.h>


struct Student{
    int age;
    int height;
}arrStudent[5];

int main(){
    Student student;

    // Akses anggota struct
    student.age = 20;
    student.height = 170;

    // int a = 10;
    // int* ptr = &a;

    // printf("memory dari ptr: %d\n", &ptr);
    // printf("value dari ptr: %d\n", ptr);
    // printf("value dari memory yang disimpan: %d\n", *ptr);
    
    // *ptr = 20;

    // print("Nilai a sekarang: %d\n", a);
    
    // Memory allocation example
    int* ptr = (int *)malloc(sizeof(int));

    *ptr = 20;

    // print("Alamat baru: %d, value dari alamat:", ptr, *ptr);

    // Alokasi memori untuk struct
    Student* ptr2 = (Student*)malloc(sizeof(Student));

    // Akses anggota dari struct pointer
    ptr->age = 21;
    ptr->height = 175;

    printf("Age: %d, height: %d", ptr2->age, ptr2->height);

    // Melepaskan alokasi memori
    free(ptr2);

    // Akses anggota dari array of struct
    arrStudent[0].age = 12;
    arrStudent[1].age = 13;
}