#pragma once

enum Grammar {
    LR0 , // implement only LR0 for syntax ana lyzer
    LR1 ,
    LALR,
    NONE
} ;

enum LexerOutput {
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

enum ReductionCode {
    END = 0,
    ID_F,
    lEl_F,
    ET_E,
    T_E,
    TF_T,
    F_T,
    ERROR,
};

enum ElementType {
    ID = 0,
    OPERATOR,
    EXPRESSION,
    TERM,
    FACTOR,
    INV_EXPR,
};  