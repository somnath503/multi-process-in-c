#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	int id = fork();
	int n;
	if(id==0){
		n=1; 
	}
	else{
		n=6;
	}
	if(id!=0){
		wait(NULL);
	}
	int i;
	for(i=n;i<n+5;i++){
		printf("%d ",i);
		fflush(stdout);
	}
	printf("\n");
	
	return 0;
}
