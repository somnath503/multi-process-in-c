#include<stdio.h>
#include<unistd.h>
int main(){
	pid_t pid  = fork();
	if(pid == 0){
		//child processs
		printf("hello from child process(pid : %d) \n",getpid());
	}
	else
	{
		printf("hello from parent process (pid : %d)\n",getpid());
	}
	return 0;
}
