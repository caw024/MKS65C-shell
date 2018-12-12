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



//splits | to get separate lines
char ** parse_pipe(char *line){
  char** arr = calloc(4, 10 * sizeof(char *));
  int i = 0;
  char * k;
  char * m = "";

  for(i; i < 3; i++){
    
    //strseps for arguments
    if (m != k){
      k = strsep(&line, "|");
      strsep(&line, " ");
      arr[i] = k;
    }
    else if (m == k){
      arr[i] = NULL;
    }
     
    m = line;
  }  
  return arr;
}




//splits > to get separate lines
char ** parse_greater(char *line){
  char** arr = calloc(4, sizeof(char *));
  char * k;
  char * m = "";

    
  //strseps for arguments
  if (m != k){
    k = strsep(&line, ">");
    strsep(&line, " ");
    arr[0] = k;
  }
  arr[1] = strsep(&line, " \n");
 
  return arr;
}


//splits < to get separate lines
char ** parse_less(char *line){
  char** arr = calloc(4, 10 * sizeof(char *));
  char * k;
  char * m = "";

    
  //strseps for arguments
  if (m != k){
    k = strsep(&line, "<");
    strsep(&line, " ");
    arr[0] = k;
  }
  arr[1] = strsep(&line, " \n");
 
  return arr;
}


//splits ; to get separate lines
char ** parse_semi(char *line){
  char** arr = calloc(5, 10 * sizeof(char *));
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
char ** parse_space(char *line){
  char** arr = calloc(5, 10 * sizeof(char*));
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

