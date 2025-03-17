#include "Analyzer.h"
#include "Visualize.h"


SyntaxAnalyzer<LR0>::SyntaxAnalyzer() : idCounter(0) {}

std::queue<GrammarElement*> SyntaxAnalyzer<LR0>::parse(FlexLexer* lexer, std::istream* in_stream) {
    std::cout << "Parsing using LR(0) algorithm.\n";
    int lex_out = lexer->yylex(in_stream);
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
            buffer.push(new Operator(lexer->YYText()));
            break;
        case NUMBER:
        case VAR:
            buffer.push(new Id(idCounter, lexer->YYText()));
            idCounter++;
        default:
            break;
        }
        lex_out = lexer->yylex(in_stream);
    }

    return buffer;
}

std::vector<GrammarElement*> SyntaxAnalyzer<LR0>::process() {
    table_prompt();

    while (!buffer.empty()) {

        ReductionCode code = canReduce();
        while(code != INV) {
            reduce(code);
            // std::cout << actions.back() << "\n";
            // printStack(stack);
            code = canReduce();
            // printRow(stack, buffer, actions.back());
        }
        
        shift();
        // printRow(stack, buffer, actions.back());
        // std::cout << actions.back() << "\n";
    }

    ReductionCode code = canReduce();
    while(code != INV) {
        reduce(code);
        // std::cout << actions.back() << "\n";
        // printStack(stack);
        code = canReduce();
    }
    
    actions.push_back("Accept");
    printRow(stack, buffer, actions.back());

    return stack;
}

void SyntaxAnalyzer<LR0>::shift() {
    actions.push_back("Shift");
    printRow(stack, buffer, actions.back());
    stack.push_back(buffer.front());
    buffer.pop();
    // printBuffer(buffer);            
    // printStack(stack);
}

void SyntaxAnalyzer<LR0>::reduce(ReductionCode code) {
    switch (code)
    {
        case ID_F:
            actions.push_back("Reduce F -> id");
            printRow(stack, buffer, actions.back());
            delete stack.back();
            stack.pop_back();
            stack.push_back(new Factor());
            break;
        
        case lEl_F:
            actions.push_back("Reduce F -> (E)");
            printRow(stack, buffer, actions.back());
            delete stack.back();
            stack.pop_back();
            delete stack.back();
            stack.pop_back();
            delete stack.back();
            stack.pop_back();
            stack.push_back(new Factor());
            break;

        case F_T:
            actions.push_back("Reduce T -> F");
            printRow(stack, buffer, actions.back());
            delete stack.back();
            stack.pop_back();
            stack.push_back(new Term());
            break;

        case TF_T:
            if (dynamic_cast<Operator*>(stack[stack.size() - 2])->value == "*")
                actions.push_back("Reduce T -> T*F");
            else
                actions.push_back("Reduce T -> T/F");
            printRow(stack, buffer, actions.back());
            
            delete stack.back();
            stack.pop_back();
            delete stack.back();
            stack.pop_back();
            delete stack.back();
            stack.pop_back();
            stack.push_back(new Term());
            break;

        case T_E:
            actions.push_back("Reduce E -> T");
            printRow(stack, buffer, actions.back());
            delete stack.back();
            stack.pop_back();
            stack.push_back(new Expression());
            break;

        case ET_E:
            if (dynamic_cast<Operator*>(stack[stack.size() - 2])->value == "+")
                actions.push_back("Reduce E -> E+T");
            else
                actions.push_back("Reduce E -> E-T");
            printRow(stack, buffer, actions.back());

            delete stack.back();
            stack.pop_back();
            delete stack.back();
            stack.pop_back();
            delete stack.back();
            stack.pop_back();
            stack.push_back(new Expression());
            break;

        default:
            break;
    }
}

ReductionCode SyntaxAnalyzer<LR0>::canReduce() {

    if (stack.empty())
        return INV;

    if (dynamic_cast<Id*>(stack.back()) != nullptr)
        return ID_F;

    if (
        stack.size() >= 3 &&
        dynamic_cast<Operator*>(stack[stack.size() - 3]) != nullptr &&
        dynamic_cast<Operator*>(stack[stack.size() - 3])->value == "(" &&
        dynamic_cast<Operator*>(stack[stack.size() - 1]) != nullptr &&
        dynamic_cast<Operator*>(stack[stack.size() - 1])->value == ")" &&
        dynamic_cast<Expression*>(stack[stack.size() - 2]) != nullptr
    )   return lEl_F;
    
    if (
        stack.size() >= 3 &&
        dynamic_cast<Term*>(stack[stack.size() - 3]) != nullptr &&
        dynamic_cast<Operator*>(stack[stack.size() - 2]) != nullptr &&
        (dynamic_cast<Operator*>(stack[stack.size() - 2])->value == "*" || 
            dynamic_cast<Operator*>(stack[stack.size() - 2])->value == "/") &&
        dynamic_cast<Factor*>(stack[stack.size() - 1]) != nullptr
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

