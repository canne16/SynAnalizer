#include "Analyzer.h"
#include "Visualize.h"


SyntaxAnalyzer<LR0>::SyntaxAnalyzer() : idCounter(0) {}

std::queue<GrammarElement> SyntaxAnalyzer<LR0>::parse(FlexLexer* lexer) {

    #ifndef TESTING
    std::cout << "Parsing using LR(0) algorithm.\n";
    #endif
    
    int lex_out = lexer->yylex();
    while (lex_out != 0)
    {
        switch (lex_out)
        {
            case PLUS:
            case MINUS:
            case DIV:
            case MUL:
            case LPAR:
            case RPAR:
            buffer.emplace(ElementType::OPERATOR, lexer->YYText());
            break;
        case NUMBER:
        case VAR:
            buffer.emplace(ElementType::ID, lexer->YYText(), idCounter);
            idCounter++;
        default:
            break;
        }
        lex_out = lexer->yylex();
    }

    return buffer;
}

std::vector<GrammarElement> SyntaxAnalyzer<LR0>::process() {
    
    #ifndef TESTING
    table_prompt();
    #endif

    while (!buffer.empty()) {

        ReductionCode code = canReduce();
        while(code != INV) {
            reduce(code);
            code = canReduce();
        }
        
        shift();
    }

    ReductionCode code = canReduce();
    while(code != INV) {
        reduce(code);
        code = canReduce();
    }
    
    if ((stack.size() == 1) && (stack[0].getType() == ElementType::EXPRESSION))
        actions.push_back("Accept");
    else
        actions.push_back("Error");

    #ifndef TESTING
    printRow(stack, buffer, actions.back());
    #endif

    return stack;
}

void SyntaxAnalyzer<LR0>::shift() {
    actions.push_back("Shift");
    #ifndef TESTING
    printRow(stack, buffer, actions.back());
    #endif
    stack.push_back(buffer.front());
    buffer.pop();
}

void SyntaxAnalyzer<LR0>::reduce(ReductionCode code) {
    switch (code)
    {
        case ID_F:
            actions.push_back("Reduce F -> id");
            #ifndef TESTING
            printRow(stack, buffer, actions.back());
            #endif
            stack.pop_back();
            stack.push_back(ElementType::FACTOR);
            break;
        
        case lEl_F:
            actions.push_back("Reduce F -> (E)");
            #ifndef TESTING
            printRow(stack, buffer, actions.back());
            #endif
            stack.pop_back();
            stack.pop_back();
            stack.pop_back();
            stack.push_back(ElementType::FACTOR);
            break;

        case F_T:
            actions.push_back("Reduce T -> F");
            #ifndef TESTING
            printRow(stack, buffer, actions.back());
            #endif
            stack.pop_back();
            stack.push_back(ElementType::TERM);
            break;

        case TF_T:
            if ((stack[stack.size() - 2].getType() == ElementType::OPERATOR) && 
                (stack[stack.size() - 2].getValue() == "*"))
                actions.push_back("Reduce T -> T*F");
            else
                actions.push_back("Reduce T -> T/F");
            #ifndef TESTING
            printRow(stack, buffer, actions.back());
            #endif
            
            stack.pop_back();
            stack.pop_back();
            stack.pop_back();
            stack.push_back(ElementType::TERM);
            break;

        case T_E:
            actions.push_back("Reduce E -> T");
            #ifndef TESTING
            printRow(stack, buffer, actions.back());
            #endif
            stack.pop_back();
            stack.push_back(ElementType::EXPRESSION);
            break;

        case ET_E:
            if ((stack[stack.size() - 2].getType() == ElementType::OPERATOR) && 
                (stack[stack.size() - 2].getValue() == "+"))
                actions.push_back("Reduce E -> E+T");
            else
                actions.push_back("Reduce E -> E-T");
            #ifndef TESTING
            printRow(stack, buffer, actions.back());
            #endif

            stack.pop_back();
            stack.pop_back();
            stack.pop_back();
            stack.push_back(ElementType::EXPRESSION);
            break;

        default:
            break;
    }
}

ReductionCode SyntaxAnalyzer<LR0>::canReduce() {

    if (stack.empty())
        return INV;

    if (stack.back().getType() == ElementType::ID)
        return ID_F;

    if (
        stack.size() >= 3 &&
        stack[stack.size() - 3].getType() == ElementType::OPERATOR &&
        stack[stack.size() - 3].getValue() == "(" &&
        stack[stack.size() - 1].getType() == ElementType::OPERATOR &&
        stack[stack.size() - 1].getValue() == ")" &&
        stack[stack.size() - 2].getType() == ElementType::EXPRESSION
    )   return lEl_F;
    
    if (
        stack.size() >= 3 &&
        stack[stack.size() - 3].getType() == ElementType::TERM &&
        stack[stack.size() - 2].getType() == ElementType::OPERATOR &&
        (stack[stack.size() - 2].getValue() == "*" || stack[stack.size() - 2].getValue() == "/") &&
         stack[stack.size() - 1].getType() == ElementType::FACTOR
    )   return TF_T;
    
    if (
        stack[stack.size() - 1].getType() == ElementType::FACTOR
    )   return F_T;

    if (
        (
            stack[stack.size() - 1].getType() == ElementType::TERM &&
            !buffer.empty() &&
            buffer.front().getType() == ElementType::OPERATOR && 
            (buffer.front().getValue() == "+" || buffer.front().getValue() == "-" || buffer.front().getValue() == ")")
        ) || 
        (
            stack[stack.size() - 1].getType() == ElementType::TERM && buffer.empty()
        )       
    ) {
        if (
            stack.size() >= 3 &&
            stack[stack.size() - 3].getType() == ElementType::EXPRESSION &&
            stack[stack.size() - 2].getType() == ElementType::OPERATOR &&
            (stack[stack.size() - 2].getValue() == "+" || stack[stack.size() - 2].getValue() == "-")
        ) return ET_E;
        
        else
            return T_E;
    }   

    return INV;
}

SyntaxAnalyzer<LR0>::~SyntaxAnalyzer() {
    while (!buffer.empty()) {
        buffer.pop();
    }
    stack.clear(); 
}

