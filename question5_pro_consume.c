#include <stdio.h>
#include <stdlib.h>

struct Node {
    int product;
    struct Node* next;
};

int sem_empty = 1;
int sem_full = 0;
int mutex = 1;

void wait(int* x) {
    if (*x > 0) {
        (*x)--;
    }
}

void signal(int* x) {
    (*x)++;
}

struct Node* create_node(int product) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->product = product;
    new_node->next = NULL;
    return new_node;
}

void produce(struct Node** buffer) {
    int product;
    printf("Enter the product value: ");
    scanf("%d", &product);

    wait(&sem_empty);
    wait(&mutex);

    struct Node* new_node = create_node(product);
    new_node->next = *buffer;
    *buffer = new_node;

    signal(&mutex);
    signal(&sem_full);
    printf("Produced: %d\n", product);
}

void consume(struct Node** buffer) {
    if (*buffer == NULL) {
        printf("Buffer is empty!\n");
        return;
    }

    wait(&sem_full);
    wait(&mutex);

    struct Node* temp = *buffer;
    *buffer = (*buffer)->next;
    printf("Consumed: %d\n", temp->product);

    free(temp);
    signal(&mutex);
    signal(&sem_empty);
}

int main() {
    struct Node* buffer = NULL;
    int choice;

    while (1) {
        printf("\nEnter 1 to produce a product, 2 to consume a product, or any other key to exit: ");
        scanf("%d", &choice);

        if (choice == 1) {
            produce(&buffer);
        } else if (choice == 2) {
            consume(&buffer);
        } else {
            break;
        }
    }

    while (buffer != NULL) {
        struct Node* temp = buffer;
        buffer = buffer->next;
        free(temp);
    }

    return 0;
}
