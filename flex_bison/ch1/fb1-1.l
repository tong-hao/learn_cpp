/* just like Unix wc */ 
%option noyywrap
%{
int chars = 0;
int words = 0;
int lines = 0; 
%}

%%

[a-zA-Z]+ { words++; chars += strlen(yytext); } 
\n        { chars++; lines++; }
.         { chars++; }

%%

int main(int argc, char **argv)
{
    yylex();
    printf("---------\nlines:%8d, words:%8d, chars:%8d\n", lines, words, chars); 
    return 0;
}


// build:
// flex fb1-1.l
// cc lex.yy.c
// a.out