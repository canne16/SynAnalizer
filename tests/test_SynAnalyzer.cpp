#include <gtest/gtest.h>
#include <FlexLexer.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Analyzer.h"


class AnalyzerTest : public ::testing::TestWithParam<std::tuple<std::string, bool>> {};


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

TEST(AnalyzerTest, ReadFromFile) {
    std::ifstream inputFile("../tests/test_input.txt");

    SyntaxAnalyzer<LR0> analyzer;
    FlexLexer* lexer = new yyFlexLexer;
    lexer->switch_streams(&inputFile, &std::cout);
    analyzer.parse(lexer);

    std::vector<GrammarElement> stack_out = analyzer.process();

    EXPECT_TRUE(
        stack_out.size() == 1 && stack_out[0].getType() == ElementType::EXPRESSION
    );

    inputFile.close();

    delete lexer;
}

TEST_P(AnalyzerTest, Processer) {
    
    std::string test_input = std::get<0>(GetParam());
    bool expected = std::get<1>(GetParam());

    std::istringstream in_stream(test_input);


    SyntaxAnalyzer<LR0> analyzer;
    FlexLexer* lexer = new yyFlexLexer;
    lexer->switch_streams(&in_stream, &std::cout);
    analyzer.parse(lexer);

    std::vector<GrammarElement> stack_out = analyzer.process();

    EXPECT_EQ((stack_out.size() == 1) && (stack_out[0].getType() == ElementType::EXPRESSION), expected);

    delete lexer;
}

INSTANTIATE_TEST_SUITE_P(
    InputCases,  // Test suite name
    AnalyzerTest,       // Test fixture
    ::testing::Values(
        std::make_tuple("1 + 2 $", true),
        std::make_tuple("1 + 2 +$", false),
        std::make_tuple("x*(y+ 3)/z * (2+x+3/y)$", true),
        std::make_tuple(" 2 - 3/4 + ( x*y*z+ 4 $", false)
    )  // Test cases
);