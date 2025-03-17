%{
#include <iostream>
#include <fstream>

using namespace std;

enum Level {
    PLUS = 5,
    MINUS,
    DIV,
    MUL,
    LPAR,
    RPAR,
    NUMBER,
    VAR
}; 

%}

%option noyywrap c++

ws      [ \ta-wA-Z\n=_,.?]+

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

{ws}    

{number}    {return NUMBER;}

{var}       {return VAR;}

%%