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
    std::ostringstream null_stream;
    lexer->switch_streams(&in_stream, &null_stream);

    EXPECT_TRUE(
        analyzer.parse(lexer).size() == 3
    );

    delete lexer;
}

TEST(AnalyzerTest, ReadFromFile) {
    std::ifstream inputFile("../tests/test_input.txt");

    SyntaxAnalyzer<LR0> analyzer;
    FlexLexer* lexer = new yyFlexLexer;
    std::ostringstream null_stream;

    lexer->switch_streams(&inputFile, &null_stream);
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

    std::ostringstream null_stream;
    lexer->switch_streams(&in_stream, &null_stream);
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
        std::make_tuple(" 2 - 3/4 + ( x*y*z+ 4 $", false),
        
        std::make_tuple("x + (y - z) * (3 + 4) / (2 * (x + y))$", true),  // Nested parentheses with valid operations
        std::make_tuple("((x + y) * z - 3) / (4 + 5 * (6 - 7))$", true),  // Deeply nested valid expression
        std::make_tuple("x * (y + z) - (3 / (4 + 5)) + (6 * (7 - 8))$", true),  // Multiple levels of nesting

        std::make_tuple("x + (y - z) * (3 + 4) / (2 * (x + y)$", false),  // Missing closing parenthesis
        std::make_tuple("x + (y - z) * (3 + 4) / (2 * (x + y)) + @$", false),  // Invalid symbol '@'
        std::make_tuple("x + (y - z) * (3 + 4) / (2 * (x + y)) + _$", false),  // Invalid symbol '_'
        std::make_tuple("x + (y - z) * (3 + 4) / (2 * (x + y)) + 4.5$", false),  // Invalid floating-point number
        std::make_tuple("x + (y - z) * (3 + 4) / (2 * (x + y)) + a$", false),  // Invalid variable 'a'

        std::make_tuple("x + 12345 * (6789 - 234) / (567 + 890)$", true),  // Large numbers
        std::make_tuple("(123 + 456) * (789 - 1011) / (1213 + 1415)$", true),  // Large numbers with valid operations

        std::make_tuple("x + (y - z) * (3 + 4)) / (2 * (x + y))$", false),  // Extra closing parenthesis
        std::make_tuple("x + ((y - z) * (3 + 4) / (2 * (x + y))$", false),  // Missing closing parenthesis

        std::make_tuple("x + y - z * 3 / (2 + x * (y - z))$", true),  // All operators with valid nesting
        std::make_tuple("(x + y) * (z - 3) / (4 + 5) + (6 - 7) * (8 / 9)$", true),  // Complex valid expression

        std::make_tuple("x + y - z * 3 / 2 + #$", false),  // Invalid symbol '#'
        std::make_tuple("x + y - z * 3 / 2 + !$", false),  // Invalid symbol '!'
        std::make_tuple("x + y - z * 3 / 2 + 4.5$", false),  // Invalid floating-point number
        std::make_tuple("x + y - z * 3 / 2 + 123abc$", false),  // Invalid mixed variable and number
        std::make_tuple("x + y - z * 3 / 2 + 123 + )$", false)  // Extra closing parenthesis
    )  
);