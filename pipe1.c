#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

int main(int argc, char* argv[]){
    int fd[2];
    // fd[0] <--- for read
    // fd[1] <--- for write
    if(pipe(fd)==-1){
        printf("error occured with opening a pipe !");
        return 1;
    }
    int id = fork();
    if(id == -1){
        printf("error occured with fork ()");
        return 2;
    }
    if(id==0){
        close(fd[0]);
        int x;
        printf("input a number in a child process ");
        scanf("%d",&x);
        write(fd[1],&x,sizeof(int));
        close(fd[1]);
    }
    else{
        close(fd[1]);
        int y;
        read(fd[0], &y , sizeof(int));
        close(fd[0]);
        printf("got from child process %d \n",y);

 
    }

    return 0;
}
