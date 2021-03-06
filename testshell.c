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



//splits | to get separate lines
char ** parse_pipe(char *line){
  char** arr = calloc(4, sizeof(char*));
  int i = 0;
  char * k;
  char * m = "";

  for(i; i < 4; i++){
    
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
    //printf("string to array: %s", k);

  }  
  return arr;
}




//splits > to get separate lines
char ** parse_greater(char *line){
  char** arr = calloc(4, sizeof(char*));
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
  char** arr = calloc(4, sizeof(char*));
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
char ** parse_space(char *line){
  char** arr = calloc(5, sizeof(char*));
  int i = 0;
  char * k;
  char * m = " ";
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
    //printf("; in array[%d]:%s\n", i, arr[i]);
    //printf("; still need to parse:%s\n", line);
    
  }  
  return arr;
}





//MAIN METHOD

int main(int argc, char * argv[]){
  int stat;
  int n;
  int i;
  int fin, fout;
  int fd0, fd1;
  int ret;
  //char test[1024] = "ls -l ; echo hello ; ls -a ";
  //char *input = test;
  while (1){
    
    printf("\n-------------------------------\n");
    char cwd[1024];

    //specific help from stack overflow to get random characters as outputs
    // if (getcwd(cwd, sizeof(cwd)) != NULL){
    // printf("cwd: %s: ",cwd);
    //}
    char * input = malloc(sizeof(char *)); 
    fgets(input, 1024, stdin);
    
    char **command;
    char **commandsemi;
    char **commandpipe;
    char **commandgreater;
    char **commandless;
    char **commandsub;


    commandsemi = parse_semi(input);

    i = 0;

    while (i < 5){
      //piping only
      char readbuf[1024];
      char current[1024];
      fin = dup(STDIN_FILENO);
      fout = dup(STDOUT_FILENO);
      printf("\ncommandsemi[0] %s", commandsemi[0]);

      
      commandpipe = parse_pipe(commandsemi[i]);
      commandgreater = parse_greater(commandsemi[i]);
      commandless = parse_less(commandsemi[i]);
      command = parse_space(commandsemi[i]);
      i++;

            
      if (command[0] == NULL)
	break;

      //found how popen works online and tried to implement it
      //open pipes to work with
      if (commandpipe[1] != NULL){
	//open command pipe
	FILE *filein = popen(commandpipe[0],"r");
	printf("\ncommandpipe[0]: %s", commandpipe[0]);

	//takes available parts and concatenates them into final string
	while (fgets(readbuf, 1024, filein)){
	  strcat(current, readbuf);
	  //printf("readbuf: %s", readbuf);
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
	fd1 = open(commandgreater[0], O_RDONLY);
	dup2(fd0, 1); //swap stdout
	dup2(fd1, 0);
	close(fd0);
	close(fd1);

	/* if (command[0] != NULL && execvp("grep", commandgreater) == -1){ */
	/*   printf("Something went wrong: %s\n", strerror(errno)); */
	/* } */

      }

      //printf("running: %s,%s\n", command[0], command[1]);

      //exits
      if (strcmp(command[0], "exit") == 0){
	printf("You exit now\n");
	return 0;
      }
      
      //child process
      if (fork() == 0){

	//cd
	if (strcmp(command[0], "cd") == 0){
	  if (chdir(command[1]) == -1)
	    printf("Something went wrong: %s\n", strerror(errno));
	}	
		
	else if (execvp(command[0], command) == -1){
	  printf("Something went wrong: %s\n", strerror(errno));
	}

      }
      //parent process   
      else{
	waitpid(-1,&stat,0);	
      }
	
      //replaces with original tools
      dup2(fout, 1);
      dup2(fin, 0);
      close(fin);
      close(fout);

    } //end of while 1-5 loop	

  } //end of while(1) loop
}//end of main
