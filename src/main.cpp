#include <FlexLexer.h>

#include "Analyzer.h"
#include "Config.h"


int main(int argc, char* argv[])
{
    
    std::cout << argv[0] << " Version " << SynAnalyzer_VERSION_MAJOR << "." << SynAnalyzer_VERSION_MINOR << std::endl;
    
    FlexLexer* lexer = new yyFlexLexer;

    SyntaxAnalyzer<LR0> lr0Analyzer;

    lr0Analyzer.parse(lexer);
    lr0Analyzer.process();  

    delete lexer;

    return 0;
}

