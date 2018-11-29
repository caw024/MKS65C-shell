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
   
    //printf("in array(space)[%d]:%s\n", i, arr[i]);
    //printf("still need to parse:%s\n", line);
  }  
  
  return arr;
}


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
    //do piping and >, >>, <, <<
    while (i < 5){
      command = parse_argsspace(commandsemi[i]);
      i++;

      char * first = command[0];
      printf("running: %s,%s\n", first, command[1]);
     
      //child process
      if (fork() == 0){

	//cd
	if (strcmp(first, "cd") == 0){
	  printf("You cd now\n");
	}

	//exit
	else if (strcmp(first, "exit") == 0){
	  printf("You exit now\n");
	}
	
	else if (execvp(command[0], command) == -1){
	  printf("Something went wrong: %s\n", strerror(errno));
	}

      }

      //parent process   
      else{
        waitpid(-1,&stat,0);
	if (WIFSIGNALED(stat)){
	  printf("exiting\n");
	  return 0;
	}
	else if (WIFEXITED(stat)){ 
	  printf("parent done\n");
	}
      }
      
    }    
  }
  return 0;
}

