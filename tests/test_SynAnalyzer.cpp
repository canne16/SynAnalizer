#include <gtest/gtest.h>
#include <FlexLexer.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Analyzer.h"


TEST(AnalyzerTest, Parser) {
    
    std::string test_input = "1 + 2 $";
    std::istringstream in_stream(test_input);

    SyntaxAnalyzer<LR0> analyzer;
    FlexLexer* lexer = new yyFlexLexer;
    lexer->switch_streams(&in_stream, &std::cout);

    EXPECT_TRUE(
        analyzer.parse(lexer).size() == 3
    );

    delete lexer;
}

TEST(AnalyzerTest, Processer) {
    std::ifstream inputFile("../tests/test_input.txt");

    SyntaxAnalyzer<LR0> analyzer;
    FlexLexer* lexer = new yyFlexLexer;
    lexer->switch_streams(&inputFile, &std::cout);
    analyzer.parse(lexer);

    std::vector<GrammarElement*> stack_out = analyzer.process();

    EXPECT_TRUE(
        stack_out.size() == 1 && dynamic_cast<Expression*>(stack_out[0]) != nullptr
    );

    inputFile.close();

    delete lexer;
}