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
                
                if (canReduce()) {
                    reduce();
                }
                else {
                    shift();
                }
            }

            printBuffer(buffer);            
            printStack(stack);

            std::cout << "FINISHED" << std::endl;
        }

        void shift() {
            stack.push_back(buffer.front());
            buffer.pop();
        }

        void reduce() {}

        int canReduce() {
            return 0;
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