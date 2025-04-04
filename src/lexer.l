%{
enum Level {
    PLUS = 5,
    MINUS,
    DIV,
    MUL,
    LPAR,
    RPAR,
    NUMBER,
    VAR,
    INV_SYM,
}; 

%}

%option noyywrap c++

ws      [a-wA-Z=_,.?#@%^&~`!:;'"\[\]\{\}]+

var     [x-z]
dig     [0-9]
dig1    [1-9]
num     {dig1}{dig}*
number  {dig}|{num}

%%

"+"         {return PLUS;}
"-"         {return MINUS;}
"*"         {return MUL;}
"/"         {return DIV;}
"("         {return LPAR;}
")"         {return RPAR;}
"$"         {return 0;}

{ws}        {return INV_SYM;}

{number}    {return NUMBER;}

{var}       {return VAR;}


%%