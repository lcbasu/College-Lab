%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>    
    void yyerror(char *s);
    enum treetype {operator_node, number_node, variable_node};
    typedef struct tree
    {
        enum treetype nodetype;
        union 
        {
            struct 
            {
                  struct tree *left, *right; char operator;
            } an_operator;

            int a_number;
            char a_variable;
        } body;
    } tree;


static tree *make_operator (tree *l, char o, tree *r) 
{
      tree *result= (tree*) malloc (sizeof(tree));
      result->nodetype= operator_node;
      result->body.an_operator.left= l;
      result->body.an_operator.operator= o;
      result->body.an_operator.right= r;
      return result;
}
 static tree *make_number (int n) {
   tree *result= (tree*) malloc (sizeof(tree));
   result->nodetype= number_node;
   result->body.a_number= n;
   return result;
 }
 static tree *make_variable (char v) {
   tree *result= (tree*) malloc (sizeof(tree));
   result->nodetype= variable_node;
   result->body.a_variable= v;
   return result;
 }
 static void printtree (tree *t, int level) {
 #define step 4
   if (t)
     switch (t->nodetype)
     {
       case operator_node:
        printtree (t->body.an_operator.right, level+step);
        printf ("%*c%c\n", level, ' ', t->body.an_operator.operator);
        printtree (t->body.an_operator.left, level+step);
        break;
       case number_node:
        printf ("%*c%d\n", level, ' ', t->body.a_number);
        break;
       case variable_node:
        printf ("%*c%c\n", level, ' ', t->body.a_variable);
     }
 }
 %}


 %union {
   int a_number;
   char a_variable;
   struct tree *a_tree;
 }

 %start input

 %token <a_number> number

 %token <a_variable> variable

 %type <a_tree> exp term factor

 %%
 input  : exp ';'               {printtree ($1, 1);}
        ;
 exp    : '+' term              {$$ = $2;}
        | '-' term              {$$ = make_operator (NULL, '~', $2);}
        | term                  {$$ = $1;}
        | exp '+' term          {$$ = make_operator ($1, '+', $3);}
        | exp '-' term          {$$ = make_operator ($1, '-', $3);}
        ;
 term   : factor                {$$ = $1;}
        | term '*' factor       {$$ = make_operator ($1, '*', $3);}
        | term '/' factor       {$$ = make_operator ($1, '/', $3);}
        ;
 factor : number                {$$ = make_number ($1);}
        | variable              {$$ = make_variable ($1);}
        | '(' exp ')'           {$$ = $2;}
        ;
 %%

int main (void) 
{
    return yyparse();
}

void yyerror(char *s)
{
  printf("%s\n", s);
}