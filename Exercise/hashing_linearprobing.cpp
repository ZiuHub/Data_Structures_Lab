#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max_table 20

struct Node
{
    char name[40];
    int angka;
} *bucket[max_table];

int count = 0;
int pos_search = 0;

Node *createNewNode(char *name, int angka)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->angka = angka;
    return newNode;
}

int hash(char *name)
{ // ini pakai cara division method
    int key = 0;
    int len = strlen(name);
    int i;

    for (i = 0; i < len; i++)
    {
        key = key + name[i];
    }

    return key % max_table; // ini di mod sama max table bucketnya ada berapa
}

void insert(char *name, int angka)
{
    int hashKey = hash(name);
    int pos = hashKey;

    // array kita semuanya ada isi / stack overflow
    if (count == max_table)
    {
        printf("Hash Table sudah penuh!\n");
        return;
    }

    // if there is any collision, in this cases we use linear probing
    while (bucket[pos] != NULL)
    {
        pos = (pos + 1) % max_table;
    }
    // array ke key nya kosong atau tidak colision
    bucket[pos] = createNewNode(name, angka);
    count++;
}

Node *search(char *name)
{
    int hashKey = hash(name);
    int pos = hashKey;

    do
    {
        if (bucket[pos] != NULL && strcmp(bucket[pos]->name, name) == 0)
        {
            pos_search = pos;
            return bucket[pos];
        }

        pos = (pos + 1) % max_table;

    } while (pos != hashKey);

    return NULL;
}

void pop(char *name)
{
    int hashKey = hash(name);
    int pos = hashKey;

    do
    {
        if (bucket[pos] != NULL && strcmp(bucket[pos]->name, name) == 0)
        {
            free(bucket[pos]);
            bucket[pos] = NULL;
            return;
        }

        pos = (pos + 1) % max_table;
    } while (pos != hashKey);

    return;
}

void print()
{
    int i;
    for (i = 0; i < max_table; i++)
    {
        if (bucket[i] != NULL)
        {
            printf("%d: %s, %d[Hash Value: %d]\n", i, bucket[i]->name, bucket[i]->angka, hash(bucket[i]->name));
        }
        else
        {
            printf("%d: -\n", i);
        }
    }
}

int main()
{
    insert("biola", 20);
    insert("ay", 30);
    insert("ik", 40);
    insert("he", 20);

    pop("hehe");
    print();
    char a[50];
    printf("Masukkan nama yang ingin dicari\n");
    scanf("%s", a);
    if (search(a) != NULL)
    {
        printf("Ketemu pada hash value no %d\n", pos_search);
    }
    else
    {
        printf("Tidak ketemu\n");
    }
}