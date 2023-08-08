#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

int getListSize(struct node *node){
    int size = 0;
    while(node != NULL){
        node = node->next;
        size++;
    }
    return size;
}

void printList(){
    struct node *pointer = head;
    printf("\n[ ");

    while(pointer != NULL){
        printf("%d ", pointer->data);
        pointer = pointer->next;
    }
    printf("]\n\n");
}

void addToEnd(int value){
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;

    if(head == NULL){
        head = newNode;
    }
    else{
        struct node *lastNode = head;
        while(lastNode->next != NULL){
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
}

void insertAtPosition(int position, int value){
    int size = getListSize(head);

    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;

    if(position < 0 || position > size){
        printf("List is not long enough to insert at that position.");
    }
    else if(position == 0){
        newNode->next = head;
        head = newNode;
    }
    else{
        struct node *temp = head;
        
        while(--position){
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

struct node* removeAtPosition(int position){
    
    struct node* current = head;
    struct node* previous = NULL;
    int size = getListSize(head);
    if(current == NULL){
        return NULL;
    }
    else if(position < 0 || position > size){
        printf("\nList is not long enough to delete at that position.\n");
        return NULL;
    }
    else if(position == 0){
        struct node *temp = head;
        head = head->next;
        free(temp);
        return temp;
    }
    else{
        struct node *temp = head;
        struct node *previous = NULL;
        position++;
        while(--position){
            previous = temp;
            temp = temp->next;
        }
        previous->next = temp->next;
        free(temp);
        return temp;
    }
    
}

struct node* removeByValue(int value){
    struct node* current = head;
    struct node* previous = NULL;

    if(head == NULL){
        return NULL;
    }
    while(current->data != value){
        if(current->next == NULL){
            return NULL;
        }
        else{
            previous = current;
            current = current->next;
        }
    }
    if(current == head){
        head = head->next;
    }
    else{
        previous->next = current->next;
    }

    free(current);
    return(current);
}

void viewByIndex(int index){
    struct node* current = head;
    int size = getListSize(head);
    int count = index;
    count++;
    if(current == NULL){
        printf("The current list is NULL\n\n");
    }
    else if(index < 0 || index > size){
        printf("There is no node at the given index.");
    }
    else if(index == 0){
        printf("\nThe value at index: %d is: %d\n\n", index, head->data);
    }
    else{

        while(--count){
            current = current->next;
        }
        printf("\nThe value at index: %d is: %d\n\n", index, current->data);
    }
}

int main(){
    
    int isRunning = 5;
    printf("Welcome to the linked list interface.\n");
    int choice;
    while(isRunning == 5){
        printf("Below are your current options.\n");
        printf("1 - Add a node to the end of the list.\n");
        printf("2 - Add a node to a specified location in the list.\n");
        printf("3 - Remove a node at a specified location.\n");
        printf("4 - Remove a node by value.\n");
        printf("5 - View the value of a node at a certain position.\n");
        printf("6 - Exit the linked list interface.\n");

        
        printf("Enter the number of the action you wish to perform: \n");
        scanf("%d", &choice);
        //printf("%d",choice);
        if(choice == 6){
            isRunning = 0;
        }
        else if(choice == 1){
            int number;
            printf("Enter the value you would like to add to the end of the list: \n\n");
            scanf("%d", &number);
            addToEnd(number);
            printf("The new list is: ");
            printList();
        }
        else if(choice == 2){
            int number;
            int index;
            printf("Enter the value you would like to add: \n");
            scanf("%d", &number);
            printf("Enter the index, where you would like to add the node: \n");
            scanf("%d", &index);
            insertAtPosition(index, number);
            printf("The new list is: ");
            printList();
        }
        else if(choice == 3){
            int index;
            printf("Enter the index, where you would like to remove the node: \n");
            scanf("%d", &index);
            removeAtPosition(index);
            printf("The new list is: ");
            printList();
        }
        else if(choice == 4){
            int value;
            printf("Enter the value you would like to remove: \n");
            scanf("%d", &value);
            removeByValue(value);
            printf("The new list is: ");
            printList();
        }
        else if(choice == 5){
            int index;
            printf("Enter the index that you would like to look at: ");
            scanf("%d", &index);
            viewByIndex(index);
        }
        else{
            printf("unknown input\n");
        }
    }
    printf("Goodbye!\n");
    return 0;
}

