// test_Analyzer.cpp
#include <gtest/gtest.h>
#include "Analyzer.h"

TEST(AnalyzerTest, Parser) {
    SyntaxAnalyzer<LR0> analyzer;
    FlexLexer* lexer = new yyFlexLexer;

    std::string input = "valid syntax";
    EXPECT_TRUE(
        ! analyzer.parse(lexer).empty()
    );

    delete lexer;
}

// TEST(AnalyzerTest, AnalyzeInvalidInput) {
//     SyntaxAnalyzer<LR0> analyzer;
//     std::string input = "invalid syntax";
//     // EXPECT_FALSE(analyzer.analyze(input));
// }