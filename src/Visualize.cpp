#include <iostream>
#include <vector>
#include <queue>

#include "Grammar.h"


void printStack(std::vector<GrammarElement*> stack) {
    std::cout << "Stack:" << std::endl << "$";

    for (auto it = stack.rend() - 1; it != stack.rbegin() - 1; --it) {
        (*it)->display();
    }

    std::cout << std::endl;
}


void printBuffer(std::queue<GrammarElement*> q) {
    std::cout << "Buffer:" << std::endl;

    while (!q.empty()) {
        q.front()->display(); 
        q.pop();
        // std::cout << " ";
    }

    std::cout << "$" << std::endl;
}
