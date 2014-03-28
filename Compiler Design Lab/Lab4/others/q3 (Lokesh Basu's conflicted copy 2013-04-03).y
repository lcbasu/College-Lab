%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// stuff from flex that bison needs to know about:
extern int yylex();
extern int yyparse();
extern FILE *yyin;
 
void yyerror(const char *s);
int nWords = 0;
%}

%union {
	char *sval;
}
%start line
%token <sval> STRING
%%

line	:	STRING line { nWords++; }
		|	STRING         { nWords++; }
		;
%%

main() {
	// open a file handle to a particular file:
	FILE *myfile = fopen("in.cpp", "r");
	// make sure it is valid:
	if (!myfile) {
		printf("Can't Open File!!!");
		return -1;
	}
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;
	
	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));

	printf("\nNumber of words is : %d", nWords);
	printf("\n");
	
}

void yyerror(const char *s) 
{
	printf("EEK, parse error!  Message: %s", s);
}
