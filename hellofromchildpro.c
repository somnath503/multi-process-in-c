#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int id;
int i;

int main() {
    for (i = 1; i <= 5; i++) { 
        id = fork();  
        
        if (id == 0) {
            // Child process
            printf("Hi from child process (pid = %d) and (iteration = %d)\n", getpid(), i);
            printf("Goodbye from child process (pid = %d)\n", getpid());
            exit(0);  // Ensure the child process terminates
        } 
		else if (id > 0) {
        
            wait(NULL);  // Wait for the child process to finish
            printf("Hello from parent process (pid = %d) and (iteration = %d)\n", getpid(), i);
            printf("Goodbye from parent process (pid = %d)\n", getpid());
        } 
		else {
    
            perror("Fork failed");
            exit(1);
        }
    }

    return 0;
}
