%{
#include <stdio.h>
#include <stdlib.h>

// stuff from flex that bison needs to know about:
extern int yylex();
extern int yyparse();
extern FILE *yyin;
 
void yyerror(const char *s);
%}

%union {
	int ival;
	float fval;
}
%start snazzle
%token <ival> INT
%token <fval> FLOAT

%%

snazzle:
	INT snazzle      { printf("bison found an int: %d",$1 ); }
	| FLOAT snazzle  { printf("bison found an float: %f",$1 ); }
	| INT            { printf("bison found an int: %d",$1 ); }
	| FLOAT          { printf("bison found an float: %f",$1 ); }
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
	
}

void yyerror(const char *s) 
{
	printf("EEK, parse error!  Message: %s", s);
}
