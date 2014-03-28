%{
#include<stdio.h>
#include"y.tab.h"
%}

%option noyywrap

aa             [a-z]
AA             [A-Z]
letter         [a-zA-Z0-9]
digit          [0-9]
word           {AA}{aa}*
line1          {word}" "{word}
line2          ({letter}|"-"|" ")+
line3          {word}" "{AA}({AA}|{aa})*", PIN-"{digit}{6}

%%

{line1}$        { printf("%s\n",yytext); return (LINE1);}
{line2}$        { printf("%s\n",yytext); return (LINE2); }
{line3}$        { printf("%s\n",yytext); return (LINE3); }
.|\n              ;
%%
