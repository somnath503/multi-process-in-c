#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
	int parent_to_child[2], child_to_parent[2];
	if(pipe(parent_to_child) < 0 || pipe(child_to_parent) < 0) {
		perror("Pipe Creation Failed!");
		return 1;
	}

	pid_t id = fork();
	if(id < 0) {
		perror("Fork Failed");
		return 2;
	} else if(id == 0) {
		// Child Process
		close(parent_to_child[1]);
		close(child_to_parent[0]);

		int num;
		while(1) {
			read(parent_to_child[0], &num, sizeof(int));
			if(num > 100)
				break;

			printf("Child  Printed: %d\t\t", num);
			num++;

			write(child_to_parent[1], &num, sizeof(int));
		}

		close(parent_to_child[0]);
		close(child_to_parent[1]);
	} else {
		// Parent Process
		close(parent_to_child[0]);
		close(child_to_parent[1]);

		int num = 1;
		while(1) {
			write(parent_to_child[1], &num, sizeof(int));
			read(child_to_parent[0], &num, sizeof(int));
			if(num > 100)
				break;

			printf("Parent Printed: %d\t\t", num);
			num++;
		}

		close(parent_to_child[1]);
		close(child_to_parent[0]);
		wait(NULL);
		printf("\n");
	}

	return 0;
}
