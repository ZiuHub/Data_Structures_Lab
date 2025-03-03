#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student{
    int id;
    char name[101];
    struct Student *left, *right;
};

struct Student *createStudent(int id, char *name){
    struct Student *newStudent = (struct Student*) malloc(sizeof(struct Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->left = newStudent->right = NULL;
    return newStudent;
}

struct Student *insert(struct Student *root, int id, char *name){
    // case 1: tree belum ada, NULL
    if(root == NULL){
        return createStudent(id, name);
    }

    // case 2: ID yang baru insert > ID current node
    else if(id > root->id){
        root->right = insert(root->right, id, name);
    }

    // case 3: ID yang baru insert < ID current node
    else{
        root->left = insert(root->left, id, name);
    }

    // case 4: ID yang baru insert == ID current node
    return root;
}

void inorder(struct Student *root){
    if(root == NULL) return;
    inorder(root->left);
    printf("Student ID: %d, Name: %s\n", root->id, root->name);
    inorder(root->right);
}

void preorder(struct Student *root){
    if(root == NULL) return;
    printf("Student ID: %d, Name: %s\n", root->id, root->name);
    inorder(root->left);
    inorder(root->right);
}

void postorder(struct Student *root){
    if(root == NULL) return;
    inorder(root->left);
    inorder(root->right);
    printf("Student ID: %d, Name: %s\n", root->id, root->name);
}

struct Student *search(struct Student *root, int id){
    // case 1: ID yang disearch tidak ada
    if(root == NULL){
        puts("Not found!");
        return NULL;
    }

    // case 2: ID yang disearch == ID current node
    if(root->id == id){
        puts("Found!");
        return root;
    }

    // case 3: ID yang disearch > ID current node
    else if(id > root->id){
        return search(root->right, id);
    }

    // case 4: ID yang disearch < ID current node
    else{
        return search(root->left, id);
    }
}

struct Student *update(struct Student *root, int id, char *name){
    // case 1: ID yang disearch tidak ada
    if(root == NULL){
        puts("Not found!");
        return NULL;
    }

    // case 2: ID yang disearch == ID current node
    if(root->id == id){
        puts("Found!");
        strcpy(root->name, name);
        return root;
    }

    // case 3: ID yang disearch > ID current node
    else if(id > root->id){
        return update(root->right, id, name);
    }

    // case 4: ID yang disearch < ID current node
    else{
        return update(root->left, id, name);
    }
}

int main(){
    struct Student *root = NULL;

    puts("Inserting...");
    root = insert(root, 3, "bill");
    root = insert(root, 1, "tom");
    root = insert(root, 16, "jake");
    root = insert(root, 78, "diana");
    root = insert(root, 33, "eve");
    puts("Insert successful!");

    // traversal
    puts("\nInorder traversal:");
    inorder(root);

    // searching
    puts("\nSearching:");
    struct Student *searchedStudent = search(root, 16);
    if(searchedStudent != NULL){
        printf("Student ID %d found with Name %s\n", searchedStudent->id, searchedStudent->name);
    }

    // updating
    puts("\nUpdating:");
    struct Student *updatedStudent = update(root, 16, "jacob");
    if(updatedStudent != NULL){
        printf("Student ID %d updated with Name %s\n", updatedStudent->id, updatedStudent->name);
    }

    // traversal after updating
    puts("\nInorder traversal:");
    inorder(root);

    puts("\nPreorder traversal:");
    preorder(root);

    puts("\nPostorder traversal:");
    postorder(root);

    return 0;
}