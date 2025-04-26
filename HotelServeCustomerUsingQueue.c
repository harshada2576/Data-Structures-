#include <stdio.h>
#include <string.h>
#define N 20

typedef struct queue {
    char a[N][100];
    int front, rear;
} queue;

void add(queue *q, char *x) {
    if (q->rear == N - 1) {
        printf("\nQueue Overflow");
    } else {
        q->rear++;
        strcpy(q->a[q->rear], x);
    }
}

int isempty(queue *q) {
    return q->front > q->rear;
}

char *serve(queue *q) {
    if (isempty(q)) {
        return NULL;
    } else {
        return q->a[q->front++];
    }
}

void display(queue *q) {
    int i;
    if (isempty(q)) {
        printf("Queue is empty!");
    } else {
        for (i = q->front; i <= q->rear; i++) {
            printf("\t%s", q->a[i]);
        }
    }
}

int main() {
    int ch;
    char cust[100];
    queue q;
    q.front = 0;
    q.rear = -1;

    while (1) {
        printf("\n1) Add\n2) Serve\n3) Display\n4) Exit\nEnter choice: ");
        scanf("%d", &ch);
        if (ch == 4)
            break;
        switch (ch) {
            case 1: {
                printf("Enter name of customer: ");
                scanf("%s", cust);
                add(&q, cust);
            } break;

            case 2: {
                char *served_cust = serve(&q);
                if (served_cust == NULL) {
                    printf("Queue is empty");
                } else {
                    printf("\nDequeued Element = %s", served_cust);
                }
            } break;

            case 3: {
                display(&q);
            } break;

            default:
                printf("Invalid choice! Try again.");
        }
    }
    return 0;
}
