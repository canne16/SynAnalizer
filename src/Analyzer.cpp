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
    
    if ((stack.size() == 1) && (stack[0].type != ElementType::EXPRESSION))
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
            if ((stack[stack.size() - 2].type == ElementType::OPERATOR) && 
                (stack[stack.size() - 2].value == "*"))
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
            if ((stack[stack.size() - 2].type == ElementType::OPERATOR) && 
                (stack[stack.size() - 2].value == "+"))
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

    if (stack.back().type == ElementType::ID)
        return ID_F;

    if (
        stack.size() >= 3 &&
        stack[stack.size() - 3].type == ElementType::OPERATOR &&
        stack[stack.size() - 3].value == "(" &&
        stack[stack.size() - 1].type == ElementType::OPERATOR &&
        stack[stack.size() - 1].value == ")" &&
        stack[stack.size() - 2].type == ElementType::EXPRESSION
    )   return lEl_F;
    
    if (
        stack.size() >= 3 &&
        stack[stack.size() - 3].type == ElementType::TERM &&
        stack[stack.size() - 2].type == ElementType::OPERATOR &&
        (stack[stack.size() - 2].value == "*" || stack[stack.size() - 2].value == "/") &&
         stack[stack.size() - 1].type == ElementType::FACTOR
    )   return TF_T;
    
    if (
        dynamic_cast<Factor*>(stack[stack.size() - 1]) != nullptr
    )   return F_T;

    if (
        (
            dynamic_cast<Term*>(stack[stack.size() - 1]) != nullptr &&
            !buffer.empty() &&
            dynamic_cast<Operator*>(buffer.front()) != nullptr && 
            (dynamic_cast<Operator*>(buffer.front())->value == "+" || 
                dynamic_cast<Operator*>(buffer.front())->value == "-" || 
                dynamic_cast<Operator*>(buffer.front())->value == ")")
        ) || 
        (
            dynamic_cast<Term*>(stack[stack.size() - 1]) != nullptr &&
            buffer.empty()
        )       
    ) {
        if (
            stack.size() >= 3 &&
            dynamic_cast<Expression*>(stack[stack.size() - 3]) != nullptr &&
            dynamic_cast<Operator*>(stack[stack.size() - 2]) != nullptr &&
            (dynamic_cast<Operator*>(stack[stack.size() - 2])->value == "+" || 
            dynamic_cast<Operator*>(stack[stack.size() - 2])->value == "-")
        ) return ET_E;
        
        else
            return T_E;
    }   

    return INV;
}

SyntaxAnalyzer<LR0>::~SyntaxAnalyzer() {
    while (!buffer.empty()) {
        delete buffer.front();
        buffer.pop();
    }
    for (auto ptr : stack) {
        delete ptr;
    }
    stack.clear(); 
}

