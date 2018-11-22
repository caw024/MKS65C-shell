#ifndef SHELL_H
#define SHELL_H

//return type: char ** (pointer to a char pointer)
//arguments: char * (a string)
//fxn: parses the semicolons in a given line to get commands
char ** parse_argssemi(char *line);

//return type: char ** (pointer to a char pointer)
//arguments: char * (a string)
//fxn: parses spaces in a given line to get arguments
char ** parse_argsspace(char *line);

#endif
