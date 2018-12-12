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


//MAIN METHOD

int main(int argc, char * argv[]){
  int stat;
  int n;
  int i;
  int fin, fout;
  int fd0, fd1;
  char readbuf[1024];
  char current[1024];
  int pid;


  //char test[100] = "ls -l ; echo hello ; ls -a ";
  //char *input = test;
  while (1){
    
    //printf("\n-------------------------------\n");
    char cwd[1024];
  

    //specific help from stack overflow to get random characters as outputs
    //printf("\n");
    char * input = malloc(10 * sizeof(char *)); 
    fgets(input, 1024, stdin);
    
    char **command;
    char **commandsemi;
    char **commandpipe;
    char **commandgreater;
    char **commandless;

    commandsemi = parse_semi(input);

    i = 0;

    //repeats based on parsed semis
    while (i < 5){

      //piping only
      fin = dup(STDIN_FILENO);
      fout = dup(STDOUT_FILENO);
  
      
      commandpipe = parse_pipe(commandsemi[i]);
      commandgreater = parse_greater(commandsemi[i]);
      commandless = parse_less(commandsemi[i]);
      command = parse_space(commandsemi[i]);
      i++;


      //if (isatty(STDIN_FILENO)){
      //}
      
      if (command[0] == NULL)
	break;

      if (strcmp(command[0], "exit") == 0){

	printf("Exiting\n");
	return 0;
      }

      //found how popen works online and tried to implement it
      //open pipes to work with
      if (commandpipe[1] != NULL){
	//open command pipe
	FILE *filein = popen(commandpipe[0],"r");

	//takes available parts and concatenates them into final string
	while (fgets(readbuf, 1024, filein)){
	  strcat(current, readbuf);
	}
	pclose(filein);

	
	FILE *fileout = popen(commandpipe[1],"w");	
	fputs(current,fileout);
	pclose(fileout);

	//reset readbuf and current
	strcpy(readbuf, "");
        strcpy(current, "");
	
	break;
      }

      //stack exchange provided me a summary of how redirection works
      //changes stdin so that execvp works on them as inputs
      else if (commandless[1] != NULL){
	fd0 = open(commandless[1],  O_RDONLY);
	if (fd0 == -1)
	  printf("Something went wrong: %s\n", strerror(errno));
	dup2(fd0, 0);
	close(fd0);
	
	
	/* //child process */
	/* if (fork() == 0){	 */
	/*   if (execvp(commandless[0], commandless) == -1){ */
	/*     printf("Something went wrong: %s\n", strerror(errno)); */
	/*   } */
	/* } */

      }

      //changes stdout so that execvp works on them as outputs
      else if (commandgreater[1] != NULL){	
	fd0 = open(commandgreater[1],  O_CREAT | O_WRONLY);
	if (fd0 == -1)
	  printf("Something went wrong: %s\n", strerror(errno));
	fd1 = open(commandgreater[0], O_RDONLY);
	if (fd1 == -1)
	  printf("Something went wrong: %s\n", strerror(errno));
	dup2(fd0, 1); //swap stdout
	dup2(fd1, 0); //swap stdin
	close(fd0);
	close(fd1);

	/* if (command[0] != NULL && execvp("grep", commandgreater) == -1){ */
	/*   printf("Something went wrong: %s\n", strerror(errno)); */
	/* } */

      }

      //printf("\nrunning: %s,%s,%s\n", command[0], command[1], command[2]);
      //sleep(1);

      if (strcmp(command[0], "cd") == 0){ 
	if (chdir(command[1]) == -1) 
	  printf("Something went wrong: %s\n", strerror(errno));
	  
	if (getcwd(cwd, sizeof(cwd)) != NULL){ 
	  printf("cwd: %s \n",cwd); 
	}
      }

      else{
	//child process
	pid = fork();
	if (pid < 0){
	  printf("Something went wrong: %s\n", strerror(errno));
	  exit(1);
	}
	else if (pid == 0){      		
	  if (execvp(command[0], command) == -1){ 
	    printf("Something went wrong: %s\n", strerror(errno)); 
	  }
	}
      
	else{
	  waitpid(-1,&stat,0);
	}
      }

      //printf("\n");


      //replaces with original tools
      dup2(fout, 1);
      dup2(fin, 0);
      close(fin);
      close(fout);
      free(input);


    } //end of while 1-5 loop	

  } //end of while(1) loop
  return 0;
}//end of main



