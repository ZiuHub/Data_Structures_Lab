#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct tnode{
    char value;
    struct tnode* left, *right;
}tnode;

tnode* createNode(char value){
    tnode* newNode = (tnode*)malloc(sizeof(tnode));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int isOperator(char c){
    return(c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void buildPrefix(tnode** root, char prefix[], int* pos){
    if(*root == NULL){
        if(isOperator(prefix[*pos])){
            *root = createNode(prefix[*pos]);
            (*pos)++;
            buildPrefix(&(*root)->left, prefix, pos);
            buildPrefix(&(*root)->right, prefix, pos);
        }
        else{
            *root = createNode(prefix[*pos]);
            (*pos)++;
        }
    }
}

tnode* buildPostfix(char postfix[]){
    tnode* stack[100];
    int i, top = -1;
    for(i = 0; postfix[i] != '\0'; i++){
        tnode* newNode = createNode(postfix[i]);
        if(isdigit(postfix[i])){
            stack[++top] = newNode;
        }
        else if(isOperator(postfix[i])){
            newNode->right = stack[top--];
            newNode->left = stack[top--];
            stack[++top] = newNode;
        }
    }
    return stack[top];
}

int evaluate(tnode* root){
    if(root->value == '+') return evaluate(root->left) + evaluate(root->right);
    else if(root->value == '-') return evaluate(root->left) - evaluate(root->right);
    else if(root->value == '*')return evaluate(root->left) * evaluate(root->right);
    else if(root->value == '/') return evaluate(root->left) / evaluate(root->right);
    else if(root->value == '^') return (int) pow(evaluate(root->left), evaluate(root->right));
    else return root->value - '0'; // convert char to int
}

void inorder(tnode* root){
    if(root != NULL){
        inorder(root->left);
        printf("%c ", root->value);
        inorder(root->right);
    }
}

void preorder(tnode* root){
    if(root != NULL){
        printf("%c ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(tnode* root){
    if(root != NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->value);
    }
}

int main(){
    tnode* root = NULL;
    char prefix[] = "+*234";
    char postfix[] = "351^+";
    int pos = 0;

    printf("Prefix: %s\n", prefix);
    buildPrefix(&root, prefix, &pos);
    printf("Inorder: ");
    inorder(root);
    puts("");
    printf("Preorder: ");
    preorder(root);
    puts("");
    printf("Postorder: ");
    postorder(root);
    puts("");
    printf("Result: %d\n", evaluate(root));
    puts("");

    printf("Postfix: %s\n", postfix);
    tnode* post = buildPostfix(postfix);
    printf("Preorder: ");
    preorder(post);
    puts("");
    printf("Result: %d\n", evaluate(post));

    return 0;
}