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

#define READ 0
#define WRITE 1

//splits ; to get separate lines
char ** parse_argssemi(char *line){
  char** arr = calloc(5, sizeof(char*));
  int i = 0;
  char * k;
  char * m = "";

  for(i; i < 5; i++){
    
    //strseps for arguments
    if (m != k){
      k = strsep(&line, ";");
      strsep(&line, " ");
      arr[i] = k;
    }
    else if (m == k){
      arr[i] = NULL;
    }
     
    m = line;
    // if (strsep(&m, "") == NULL)
    //arr[i] = NULL;
   
    //printf("; in array[%d]:%s\n", i, arr[i]);
    //printf("; still need to parse:%s\n", line);
  }  
  return arr;
}



//splits " " to get separate arguments
char ** parse_argsspace(char *line){
  char** arr = calloc(5, sizeof(char*));
  int i = 0;
  char * k;
  char * m = "  ";
  char * test;
  
  for(i; i < 5; i++){
    
    //strseps for arguments
    if (m != k){
      k = strsep(&line, " \n ");
      arr[i] = k;
    }
    else if (m == k){
      arr[i] = NULL;
    }
     
    m = line;
    if (m == " " || strsep(&m, "") == NULL)
      arr[i] = NULL;

  }  
  return arr;
}


int main(int argc, char * argv[]){
  int stat;
  int n;
  int i;
  int fin, fout;
  int fdin,fdout;
  //char test[100] = "ls -l ; echo hello ; ls -a ";
  //char *input = test;
  while (1){
    
    printf("\n-------------------------------\n");
    char cwd[100];

    //specific help from stack overflow to get random characters as outputs
    if (getcwd(cwd, sizeof(cwd)) != NULL){
      printf("cwd: %s: ",cwd);
    }
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

      char * first = command[0];
      printf("running: %s,%s\n", first, command[1]);

      //exits
      if (first != NULL && strcmp(first, "exit") == 0){
	printf("You exit now\n");
	return 0;
      }	
     
      //child process
      if (fork() == 0){

	//piping only
	if (command[1] != NULL && command[2] != NULL && strcmp(command[1], "|") == 0){
	  printf("Starting\n");
	  int fd = open(command[0], O_READ);
	  FILE *filein = popen(command[0],"r");
	  FILE *fileout = popen(command[2],"w");


	}

	
	//cd
	if (strcmp(first, "cd") == 0){
	  if (chdir(command[1]) == -1)
	    printf("Something went wrong: %s\n", strerror(errno));
	}	

		 
	//do piping (with popen) and >, >>, <, <<
	
	else if (execvp(command[0], command) == -1){
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

  
