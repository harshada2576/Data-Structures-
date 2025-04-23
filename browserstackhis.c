#include <stdio.h>
#include <string.h>
#define N 20
											/*Harshada Avhad
											CMPN-B
											24102B0023
											*/
typedef struct stack {
    char a[N][100]; // Array to store page URLs (each URL is a string)
    int top;
} stack;

void push(stack *s, char *x) {
    if (s->top == N - 1)
        printf("\nStack Overflow...");
    else {
        s->top = s->top + 1;
        strcpy(s->a[s->top], x);
    }
}

int isempty(stack *s) {
    return (s->top == -1);
}

char* pop(stack *s) {
    if (isempty(s))
        return NULL;
    else {
        return s->a[s->top--];
    }
}

char* peek(stack *s) {
    if (isempty(s))
        return NULL;
    else
        return s->a[s->top];
}

void display(stack *s) {
    if (isempty(s)) {
        printf("\nStack is empty...");
    } else {
        for (int i = s->top; i >= 0; i--) {
            printf("\t%s", s->a[i]);
        }
    }
}

int main() {
    int ch;
    char url[100];
    stack backStack, forwardStack;
    char currentPage[100] = "Home"; // Starting page
    backStack.top = -1;
    forwardStack.top = -1;

    while (1) {
        printf("\n\nCurrent Page: %s", currentPage);
        printf("\n1: Visit New Page\n2: Back\n3: Forward\n4: Display History\n5: Exit\nEnter choice: ");
        scanf("%d", &ch);

        if (ch == 5)
            break;

        switch (ch) {
            case 1: // Visit new page
                printf("\nEnter URL of new page: ");
                scanf("%s", url);
                push(&backStack, currentPage); // Push the current page to the back stack
                strcpy(currentPage, url);     // Set the new page as the current page
                while (!isempty(&forwardStack)) { // Clear the forward stack
                    pop(&forwardStack);
                }
                break;

            case 2: // Back
                if (isempty(&backStack)) {
                    printf("\nNo pages in the back history.");
                } else {
                    push(&forwardStack, currentPage); // Push the current page to the forward stack
                    strcpy(currentPage, pop(&backStack)); // Set the top of backStack as the current page
                }
                break;

            case 3: // Forward
                if (isempty(&forwardStack)) {
                    printf("\nNo pages in the forward history.");
                } else {
                    push(&backStack, currentPage); // Push the current page to the back stack
                    strcpy(currentPage, pop(&forwardStack)); // Set the top of forwardStack as the current page
                }
                break;

            case 4: // Display history
                printf("\nBack History: ");
                display(&backStack);
                printf("\nForward History: ");
                display(&forwardStack);
                break;

            default:
                printf("\nInvalid Choice...");
        }
    }
    return 0;
}

