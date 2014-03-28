%{
#include<stdio.h>
int yylex();
int yyerror(char*);

%}

%token LINE1
%token LINE2
%token LINE3

%%
Address :LINE1 LINE2 LINE3      { printf("correct syntax"); }

%%
int main(){
  yyparse();
  return 0;
}

int yyerror(char* s){
  printf("error: %s\n",s);
  return 1;
}
