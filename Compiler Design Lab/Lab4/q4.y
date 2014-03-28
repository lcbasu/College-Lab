%{

    #include<stdio.h>
    int yyerror (char *s);

%}

%token NUM

%start line

%left '+' '-'
%left '*' '/'

%right NEGATIVE

%%

line    :   exp  ';'                {  ;   }
        ;
exp     :   exp '+' exp             {   printf("+");    }
        |   exp '*' exp             {   printf("*");    }
        |   exp '-' exp             {   printf("-");    }
        |   exp '/' exp             {   printf("/");    }
        |   '(' exp ')'
        |   '-' exp %prec NEGATIVE  {    printf("-");    }
        |   NUM                     {   printf("%d", yylval);   }
        ;
%%

int main()
{
    yyparse();
    printf ("\n");
}

int yyerror (char *s)
{
    printf ("ERROR : %s\n", s);
}