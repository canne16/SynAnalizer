#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <FlexLexer.h>

#include "Codes.h"
#include "Grammar.h"

template <Grammar G>
class SyntaxAnalyzer {};  

template <>
class SyntaxAnalyzer<LR0> {
private:
    int idCounter;
    std::queue<GrammarElement*> buffer;
    std::vector<GrammarElement*> stack;
    std::vector<std::string> actions;

public:
    SyntaxAnalyzer(); 

    std::queue<GrammarElement*> parse(FlexLexer* lexer, std::istream* in_stream);
    std::vector<GrammarElement*> process();
    void shift();
    void reduce(ReductionCode code);
    ReductionCode canReduce();

    ~SyntaxAnalyzer();
};