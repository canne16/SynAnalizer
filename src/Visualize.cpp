#include <iostream>
#include <vector>
#include <queue>

#include "Grammar.h"


void printStack(const std::vector<GrammarElement>& stack) {
    std::cout << "Stack:" << std::endl;
    std::cout << std::endl;
    for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
        it->display();
        std::cout << std::endl;
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

    std::cout << std::endl;
}
