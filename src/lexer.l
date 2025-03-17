%{
#include <iostream>
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

"+"         {cout << "operation " << YYText() << endl; return PLUS;}
"-"         {cout << "operation " << YYText() << endl; return MINUS;}
"*"         {cout << "operation " << YYText() << endl; return MUL;}
"/"         {cout << "operation " << YYText() << endl; return DIV;}
"("         {cout << "operation " << YYText() << endl; return LPAR;}
")"         {cout << "operation " << YYText() << endl; return RPAR;}
"$"         {cout << "quitting..." << endl; return 0;}

{ws}    

{number}    {cout << "number " << YYText() << '\n'; return NUMBER;}

{var}       {cout << "variable " << YYText() << '\n'; return VAR;}

%%