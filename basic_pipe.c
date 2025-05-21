#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    // Creating a pipe
    if (pipe(fd) == -1) {
        printf("Error creating pipe!\n");
        return 1;
    }

    int id = fork(); 

    if (id == -1) {
        printf("Error creating process!\n");
        return 2;
    }

    if (id == 0) {

        close(fd[1]); // Close unused write end

        int num;
        while (1) {
            read(fd[0], &num, sizeof(int)); // Read from pipe
            if (num > 100) break; // 

            printf("Child: %d\t", num);
            num++; 

            write(fd[1], &num, sizeof(int)); // Write back to pipe
        }
        close(fd[0]); // Close read end
    } else {
    
        close(fd[0]); // Close unused read end

        int num = 1;
        write(fd[1], &num, sizeof(int)); 

        while (1) {
            read(fd[0], &num, sizeof(int)); // Read from pipe
            if (num > 100) break; // 

            printf("Parent: %d\t", num);
            num++; 

            write(fd[1], &num, sizeof(int)); // Write back to pipe
        }
        close(fd[1]); 
        wait(NULL);   
        printf("\n");
    }

    return 0;
}
