# MKS65C-shell
Calvin Aw

A description of what features your shell implements:<br />

The shell can fork + execute commands in a line (separated by semicolons) and redirect via stdin. cd and exit work properly.


A description of what features you attempted to implement but were unsuccessful: <br />

I couldn't get redirecting stdout (returns "input file is not output file") and piping (returns something, but not what we want) to work out properly (progress on them can be found in comments section of code).


Any bugs or things you want me to know about your program: <br />

* Extraneous spaces in the command line might make a command invalid. <br />
* Redirecting via stdin can cause the program to end (although it does run).


A copy of every function header:

//return type: char ** (pointer to a char pointer)<br />
//arguments: char * (a string)<br />
//fxn: parses the pipes in a given line to get arguments<br />
char ** parse_pipe(char *line);

//return type: char ** (pointer to a char pointer)<br />
//arguments: char * (a string)<br />
//fxn: parses the > sign in a given line to get arguments<br />
char ** parse_greater(char *line);

//return type: char ** (pointer to a char pointer)<br />
//arguments: char * (a string)<br />
//fxn: parses the < in a given line to get arguments<br />
char ** parse_less(char *line);

//return type: char ** (pointer to a char pointer)<br />
//arguments: char * (a string)<br />
//fxn: parses the semicolons in a given line to get commands<br />
char ** parse_semi(char *line);

//return type: char ** (pointer to a char pointer)<br />
//arguments: char * (a string)<br />
//fxn: parses spaces in a given line to get arguments<br />
char ** parse_space(char *line);

* I consulted stack overflow and other websites for some help on pieces of code as listed inside it.
