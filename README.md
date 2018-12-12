# MKS65C-shell
Calvin Aw

A description of what features your shell implements:<br />

The shell can fork + execute commands in a line (separated by semicolons) and redirect as well as some piping.


A description of what features you attempted to implement but were unsuccessful: <br />

Extraneous spaces in the command line might make a command invalid. <br />

Any bugs or things you want me to know about your program: <br />

I couldn't figure out why ls -l | wc doesn't work exactly the way you want it (it givse an incorrect response). 

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

Important Note: <br />
I consulted stack overflow and other websites for some help on pieces of code I had trouble with (and worked several hours on). The specific parts are listed inside the code.
