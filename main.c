#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

#include "shell.h"

int main(int argc, char * argv[]){
  int stat;
  int n;
  int i;
  //char test[100] = "ls -l ; echo hello ; ls -a ";
  //char *input = test;
  while (1){
    printf("\n-------------------------------\n");
    printf("type something:"); //maybe pwd or getcwd
    printf("\n");
    char * input = malloc(sizeof(char *)); 
    fgets(input, 100, stdin);


    char** command;
    char** commandsemi;
    commandsemi = parse_argssemi(input);

    i = 0;
    while (i < 5){
      command = parse_argsspace(commandsemi[i]);
      i++;

      //child process
      if (fork() == 0){
	printf("running: %s %s\n", command[0], command[1]);
	if (execvp(command[0], command) == -1){
	  printf("Something went wrong: %s\n", strerror(errno));
	}			
      }

      //parent process   
      else{
        waitpid(-1,&stat,0); 
	if (WIFEXITED(stat)){ 
	  printf("parent done\n"); 
	}
      }     
    }    
  }
  return 0;
}
