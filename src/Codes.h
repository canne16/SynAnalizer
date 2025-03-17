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
    VAR
}; 

enum ReductionCode {
    INV = 0,
    ID_F,
    lEl_F,
    ET_E,
    T_E,
    TF_T,
    F_T
};
