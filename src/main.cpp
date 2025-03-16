#include <FlexLexer.h>

#include "Analizer.cpp"
#include "Config.h"


int main(int argc, char* argv[])
{
    
    std::cout << argv[0] << " Version " << SynAnalizer_VERSION_MAJOR << "." << SynAnalizer_VERSION_MINOR << std::endl;
    
    FlexLexer* lexer = new yyFlexLexer;

    SyntaxAnalyzer<LR0> lr0Analyzer;

    lr0Analyzer.parse(lexer);
    


    return 0;
}

