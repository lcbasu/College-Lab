%{
  #include "y.tab.h"
%}

%%

"exit"	{	return exit_command;	}
[0-9]+  { yylval.number = atoi(yytext); return num;  }
[a-zA-Z][0-9a-zA-Z] { yylval.variable = yytext[0]; return var; }
[ \t\n] ;
[-+/*=><!;{}()] { return yytext[0]; }
.   { ECHO;
      yyerror("unexpected character");  }

%%


int yywrap(void)
{
  return 1;
}