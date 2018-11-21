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
char ** parse_args(char* line){
  char** arr = calloc(6, sizeof(char*));
  int i = 0;
  char * k;
  char * m = "";

  for(i; i < 6; i++){
    
    //strseps for arguments
    if (m != k){
      k = strsep(&line, ";");
      arr[i] = k;
    }
    else if (m == k){
      arr[i] = NULL;
    }
     
    m = line;
    if (strsep(&m, "") == NULL)
      arr[i] = NULL;
   
    //printf("; in array[%d]: %s\n", i, arr[i]);
    //printf("; still need to parse: %s\n", line);
  }
  
  
  return arr;
}


//splits " " to get separate arguments
char ** parse_argsspace(char* line){
  char** arr = calloc(6, sizeof(char*));
  int i = 0;
  char * k;
  char * m = "";

  for(i; i < 6; i++){
    
    //strseps for arguments
    if (m != k){
      k = strsep(&line, " \n ");
      arr[i] = k;
    }
    else if (m == k){
      arr[i] = NULL;
    }
     
    m = line;
    if (strsep(&m, "") == NULL)
      arr[i] = NULL;
   
    // printf("in array[%d]: %s\n", i, arr[i]);
    //printf("still need to parse: %s\n", line);
  }
  
  
  return arr;
}



int main(int argc, char * argv[]){
  int stat;
  while (1){
    printf("type something:"); //maybe pwd or getcwd 
    char * input = malloc(sizeof(char *)); 
    fgets(input, 100, stdin); 

    //child process 
    if (fork() == 0){ 
      char** command;
      char** commandsemi;
      command = parse_argsspace(input);
      execvp(command[0], command);
    }

    //parent process 
    else{ 
      waitpid(-1,&stat,0); 
      if (WIFEXITED(stat)){ 
	printf("\n"); 
      } 
    } 

  }
  //return 0;

}
