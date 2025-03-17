#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <FlexLexer.h>

#include "Codes.h"
#include "Grammar.h"
#include "Visualize.cpp"


template <Grammar G>
class SyntaxAnalyzer {};

template<>
class SyntaxAnalyzer<LR0> {
    private:
        int idCounter;
        std::queue<GrammarElement*> buffer;
        std::vector<GrammarElement*> stack;
        std::vector<std::string> actions;

    public:
        SyntaxAnalyzer() : idCounter(0) {} 

        void parse(FlexLexer* lexer) {
            std::cout << "Parsing using LR(0) algorithm.\n";
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
                    buffer.push(new Operator(lexer->YYText()));
                    break;
                case NUMBER:
                case VAR:
                    buffer.push(new Id(idCounter, lexer->YYText()));
                    idCounter++;
                default:
                    break;
                }
                lex_out = lexer->yylex();
            }

            printBuffer(buffer);
            
        }

        void process() {
            
            while (!buffer.empty()) {
                
                ReductionCode code = canReduce();
                while(code != INV) {
                    reduce(code);
                    std::cout << actions.back() << "\n";
                    printStack(stack);
                    code = canReduce();
                }
                
                shift();
                std::cout << actions.back() << "\n";
            }

            ReductionCode code = canReduce();
            while(code != INV) {
                reduce(code);
                std::cout << actions.back() << "\n";
                printStack(stack);
                code = canReduce();
            }
            
            printStack(stack);

            std::cout << "ACCEPT" << std::endl;
        }

        void shift() {
            stack.push_back(buffer.front());
            buffer.pop();
            actions.push_back("Shift");
            printBuffer(buffer);            
            printStack(stack);
        }

        void reduce(ReductionCode code) {
            switch (code)
            {
                case ID_F:
                    actions.push_back("Reduce F -> id");
                    delete stack.back();
                    stack.pop_back();
                    stack.push_back(new Factor());
                    break;
                
                case lEl_F:
                    actions.push_back("Reduce F -> (E)");
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
                    delete stack.back();
                    stack.pop_back();
                    stack.push_back(new Term());
                    break;

                case TF_T:
                    if (dynamic_cast<Operator*>(stack[stack.size() - 2])->value == "*")
                        actions.push_back("Reduce T -> T*F");
                    else
                        actions.push_back("Reduce T -> T/F");
                    
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
                    delete stack.back();
                    stack.pop_back();
                    stack.push_back(new Expression());
                    break;

                case ET_E:
                    if (dynamic_cast<Operator*>(stack[stack.size() - 2])->value == "+")
                        actions.push_back("Reduce E -> E+T");
                    else
                        actions.push_back("Reduce E -> E-T");

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

        ReductionCode canReduce() {

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


        ~SyntaxAnalyzer() {
            while (!buffer.empty()) {
                delete buffer.front();
                buffer.pop();
            }
            for (auto ptr : stack) {
                delete ptr;
            }
            stack.clear(); 

        }
};