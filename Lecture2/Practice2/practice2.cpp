#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* top = NULL;

void push(int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = top;
    top = temp;
}

void pop() {
    struct node* temp;
    if (top == NULL)
        return;
    temp = top;
    top = top->next;
    free(temp);
}

void display() {
    struct node* temp;
    if (top == NULL)
        return;
    temp = top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main() {
    push(1);
    push(2);
    push(3);
    push(4);
    push(5);
    printf("Stack: ");
    display();
    pop();
    printf("\nStack after pop operation: ");
    display();
    return 0;
}
