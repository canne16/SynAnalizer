enum Grammar {
    LR0 , // implement only LR0 for syntax ana lyzer
    LR1 ,
    LALR,
    NONE
} ;

enum LexerOutputs {
    PLUS = 5,
    MINUS,
    DIV,
    MUL,
    LPAR,
    RPAR,
    NUMBER,
    VAR
}; 

