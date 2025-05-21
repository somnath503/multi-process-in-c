    #include <stdio.h>
    #include <stdlib.h>

    // Function to decrement a semaphore
    void wait(int* x) {
        if (*x > 0) {
            (*x)--; // Dereference the pointer to modify the value
        }
    }

    // Function to increment a semaphore
    void signal(int* x) {
        (*x)++; // Dereference the pointer to modify the value
    }

    int main() {
        int buffer[3];        // Buffer of size 3
        int sem_empty = 3;    // Number of empty slots in the buffer
        int sem_full = 0;     // Number of filled slots in the buffer
        int mutex = 1;        // Mutex for critical section
        int in = 0;           // Index for producer
        int out = 0;          // Index for consumer
        int choice;

        while (1) {
            printf("\n");
            printf("Empty: %d, Full: %d, Semaphore (mutex): %d\n", sem_empty, sem_full, mutex);
            printf("Enter 1 to produce a product, 2 to consume a product, or any other key to exit: ");
            scanf("%d", &choice);

            // Produce product
            if (choice == 1) {
                if (sem_empty > 0 && mutex == 1) {
                    printf("Enter the product value: ");
                    wait(&sem_empty);  // Decrement empty slots
                    wait(&mutex);      // Enter critical section
                    scanf("%d", &buffer[in]); // Store the product in the buffer
                    in = (in + 1) % 3; // Move to the next slot (circular buffer)
                    signal(&mutex);    // Exit critical section
                    signal(&sem_full); // Increment filled slots
                } else {
                    printf("Buffer is full!\n");
                }
            }
            // Consume product
            else if (choice == 2) {
                if (sem_full > 0 && mutex == 1) {
                    wait(&sem_full);   // Decrement filled slots
                    wait(&mutex);      // Enter critical section
                    printf("Consumed product value is: %d\n", buffer[out]); // Consume the product
                    out = (out + 1) % 3; // Move to the next slot (circular buffer)
                    signal(&mutex);    // Exit critical section
                    signal(&sem_empty); // Increment empty slots
                } else {
                    printf("Buffer is empty!\n");
                }
            } else {
                printf("Exiting...\n");
                break;
            }
        }

        return 0;
    }
