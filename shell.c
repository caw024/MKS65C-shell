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

char ** parse_args(char* line){
  char** arr = calloc(6, sizeof(char*));
  int i = 0;
  char * k;
  char * m = "";
  int ctr = 0;
  for(i; i < 6; i++){
    
    //strseps
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
   
    //printf("in array[%d]: %s\n", i, arr[i]);
    //printf("still need to parse: %s\n", line);
  }
  
  return arr;
}



int main(int argc, char * argv[]){
  while (1){
    printf("type something:"); //maybe pwd or getcwd 
    char * input = malloc(sizeof(char *)); 
    fgets(input, 100, stdin); 

    //figure out how to parse
    //char ex[100] = "ls -a -l";
    //char * input = ex; 
    char** command; 
    command = parse_args(input);
    execvp(command[0], command);
  }
  //return 0;

}




// forking process

/* int randfd; */
/* int arr[0]; */
/* int stat; */
/* int l; */
/* int m; */
/* int i = 0; */

 
/* printf("beginning of parent\n"); */

/* for  (i; i < 2; i++){ */
/*   //child process */
/*   if (fork() == 0){ */
/*     randfd = open("/dev/random", O_RDONLY); */
/*     l = read(randfd, arr, sizeof(int)); */
/*     m = close(randfd); */
  
/*     l = (l % 15) + 5; */
/*     sleep(l); */
/*     printf("child finished sleeping\n"); */

/*     printf("The child slept for %d seconds\n", l); */
/*     return 0; */
/*   } */

/*   //parent process */
/*   else{ */
/*     printf("parent is waiting for child to finish:\n"); */
/*     waitpid(-1,&stat,0); */
/*     if (WIFEXITED(stat)){ */
/* 	printf("parent is done waiting\n"); */
/*     } */
/*   } */
