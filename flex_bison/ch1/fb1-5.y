/* simplest version of calculator */ 
%{
#include <stdio.h>
%}

/* declare tokens */ 
%token NUMBER
%token ADD SUB MUL DIV ABS 
%token EOL

%%
calclist: /* nothing */
 | calclist exp EOL { printf("=%d\n", $2);}
 ;  
exp: factor /* default $$ = $1 */
 | exp ADD factor { $$ = $1 + $3; } 
 | exp SUB factor { $$ = $1 - $3; } 
 ;
factor: term /* default $$ = $1 */
 | factor MUL term { $$ = $1 * $3; } 
 | factor DIV term { $$ = $1 / $3; } 
 ;
term: NUMBER /*default $$ = $1*/
| ABS term { $$ = $2 >= 0? $2 : - $2; } 
;
%%

yyerror(char *s)
{
    fprintf(stderr, "error: %s\n", s);
}

main(int argc, char **argv)
{
    yyparse();
}



// bison -d fb1-5.y  ==> fb1-5.tab.c fb1-5.tab.h
// flex fb1-5.l      ==> lex.yy.c
// cc fb1-5.tab.c lex.yy.c   ==> a.cout