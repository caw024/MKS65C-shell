#ifndef SHELL_H
#define SHELL_H

//return type: char ** (pointer to a char pointer)
//arguments: char * (a string)
//fxn: parses the pipes in a given line to get arguments
char ** parse_pipe(char *line);

//return type: char ** (pointer to a char pointer)
//arguments: char * (a string)
//fxn: parses the > sign in a given line to get arguments
char ** parse_greater(char *line);

//return type: char ** (pointer to a char pointer)
//arguments: char * (a string)
//fxn: parses the < in a given line to get arguments
char ** parse_less(char *line);


//return type: char ** (pointer to a char pointer)
//arguments: char * (a string)
//fxn: parses the semicolons in a given line to get commands
char ** parse_semi(char *line);

//return type: char ** (pointer to a char pointer)
//arguments: char * (a string)
//fxn: parses spaces in a given line to get arguments
char ** parse_space(char *line);

#endif
