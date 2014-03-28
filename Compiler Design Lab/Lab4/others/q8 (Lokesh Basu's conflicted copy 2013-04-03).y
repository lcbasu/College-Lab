%{
	void yyerror(char *s);
	#include <stdio.h>
	#include <stdlib.h>
%}
%token A B
%%
start:sa sb
|sa
|sb
;
sa: A sa
| A
;
sb: B sb
|B
;
%%
int main()
{
printf(“\n enter a string of A’s followed by B\n”);
printf(“for the following grammer a^nb^n,n,m>=0\n”);
yyparse();
printf(“valid input\n”);
return 0;
}

void yyerror(char *s)
{
	printf("%s\n", s);
}