# MKS65C-shell

A description of what features your shell implements:
The shell can fork + execute commands in a line (separated by semicolons).


A description of what features you attempted to implement but were unsuccessful:
I couldn't get redirecting and piping to work out.


Any bugs or things you want me to know about your program:
Extraneous spaces in the command line will give an invalid type.


A copy of every function header:

//return type: char ** (pointer to a char pointer) broken up by semicolons
//arguments: char * (a string)
//fxn: parses the semicolons in a given line to get commands
char ** parse_argssemi(char *line);

//return type: char ** (pointer to a char pointer) broken up by spaces
//arguments: char * (a string)
//fxn: parses spaces in a given line to get arguments
char ** parse_argsspace(char *line);
