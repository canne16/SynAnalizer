#include <gtest/gtest.h>
#include <FlexLexer.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Analyzer.h"


TEST(AnalyzerTest, Parser) {

    std::ifstream inputFile("../tests/test_input.txt");

    SyntaxAnalyzer<LR0> analyzer;
    FlexLexer* lexer = new yyFlexLexer;

    EXPECT_TRUE(
        ! analyzer.parse(lexer, &inputFile).empty()
    );

    inputFile.close();

    delete lexer;
}

TEST(AnalyzerTest, AnalyzeInvalidInput) {
    SyntaxAnalyzer<LR0> analyzer;
    std::string input = "invalid syntax";
    // EXPECT_FALSE(analyzer.analyze(input));
}