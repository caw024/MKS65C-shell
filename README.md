# MKS65C-shell

A description of what features your shell implements:
The shell can fork + execute commands in a line (separated by semicolons) and redirect via stdin. cd and exit work properly.


A description of what features you attempted to implement but were unsuccessful:
I couldn't get redirecting stdout (returns "input file is not output file") and piping to work out properly. (progress on them can be found in comments section of code).


Any bugs or things you want me to know about your program:
Extraneous spaces in the command line might make a command invalid.
Redirecting via stdin can cause the program to end (although it does run).


A copy of every function header:

//return type: char ** (pointer to a char pointer) broken up by semicolons
//arguments: char * (a string)
//fxn: parses the semicolons in a given line to get commands
char ** parse_argssemi(char *line);

//return type: char ** (pointer to a char pointer) broken up by spaces
//arguments: char * (a string)
//fxn: parses spaces in a given line to get arguments
char ** parse_argsspace(char *line);
