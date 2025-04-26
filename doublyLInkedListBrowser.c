#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URLS 10  
#define MAX_LENGTH 100  

// Structure for a node in the doubly linked list
typedef struct Node {
    char url[MAX_URLS][MAX_LENGTH]; // 2D array for URLs
    int count[MAX_URLS]; // Array to count visits for each URL
    struct Node* prev;
    struct Node* next;
} Node;

// Structure for the linked list (only using `start` pointer)
typedef struct {
    Node* start;  // Points to the first node
} BrowserHistory;

// Function to create a new node
Node* createNode(const char* url) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->url[0], url);
    newNode->count[0] = 1;
    for (int i = 1; i < MAX_URLS; i++) {
        newNode->url[i][0] = '\0'; // Initialize empty URLs
        newNode->count[i] = 0;
    }
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end
void insertAtEnd(BrowserHistory* history, const char* url) {
    Node* newNode = createNode(url);
    if (history->start == NULL) {
        history->start = newNode;
        return;
    }
    Node* temp = history->start;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to delete a node from the beginning
void deleteFromBeginning(BrowserHistory* history) {
    if (history->start == NULL) {
        printf("History is empty.\n");
        return;
    }
    Node* temp = history->start;
    history->start = history->start->next;
    if (history->start != NULL) {
        history->start->prev = NULL;
    }
    free(temp);
}

// Function to display the first node
void displayFirstNode(BrowserHistory* history) {
    if (history->start == NULL) {
        printf("History is empty.\n");
    } else {
        printf("First Page: %s\n", history->start->url[0]);
    }
}

// Function to display the last node
void displayLastNode(BrowserHistory* history) {
    if (history->start == NULL) {
        printf("History is empty.\n");
        return;
    }
    Node* temp = history->start;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    printf("Last Page: %s\n", temp->url[0]);
}

// Function to display browsing history in forward direction
void displayForward(BrowserHistory* history) {
    if (history->start == NULL) {
        printf("History is empty.\n");
        return;
    }
    Node* temp = history->start;
    printf("Browsing History (Forward):\n");
    while (temp != NULL) {
        printf("[");
        for (int i = 0; i < MAX_URLS && temp->url[i][0] != '\0'; i++) {
            printf(" %s(%d) ", temp->url[i], temp->count[i]);
        }
        printf("] -> ");
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to display browsing history in backward direction
void displayBackward(BrowserHistory* history) {
    if (history->start == NULL) {
        printf("History is empty.\n");
        return;
    }
    Node* temp = history->start;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    printf("Browsing History (Backward):\n");
    while (temp != NULL) {
        printf("[");
        for (int i = 0; i < MAX_URLS && temp->url[i][0] != '\0'; i++) {
            printf(" %s(%d) ", temp->url[i], temp->count[i]);
        }
        printf("] -> ");
        temp = temp->prev;
    }
    printf("NULL\n");
}

// Main function
int main() {
    BrowserHistory history;
    history.start = NULL;
    int choice;
    char url[MAX_LENGTH];

    while (1) {
        printf("\nMenu:\n");
        printf("1) Insert at end\n");
        printf("2) Delete from beginning\n");
        printf("3) Display first node\n");
        printf("4) Display last node\n");
        printf("5) Display forward\n");
        printf("6) Display backward\n");
        printf("7) Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                insertAtEnd(&history, url);
                break;
            case 2:
                deleteFromBeginning(&history);
                break;
            case 3:
                displayFirstNode(&history);
                break;
            case 4:
                displayLastNode(&history);
                break;
            case 5:
                displayForward(&history);
                break;
            case 6:
                displayBackward(&history);
                break;
            case 7:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

