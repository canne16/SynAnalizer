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


void printTable(std::vector<int>& stack1, const std::queue<int>& queue, const std::vector<int>& stack2) {
    // Print the table header
    std::cout << "Stack 1\tQueue\tStack 2" << std::endl;
    std::cout << "-------\t-----\t-------" << std::endl;

    // Determine the maximum size among stack1, queue, and stack2
    size_t maxSize = std::max(stack1.size(), std::max(queue.size(), stack2.size()));

    // Print the contents of the stack and queue in a tabular format
    for (size_t i = 0; i < maxSize; ++i) {
        // Print stack1 element if available
        if (i < stack1.size()) {
            std::cout << stack1[stack1.size() - 1 - i] << "\t";
        } else {
            std::cout << "\t";
        }

        // Print queue element if available
        if (i < queue.size()) {
            std::queue<int> tempQueue = queue; // Copy the queue to avoid modifying the original
            for (size_t j = 0; j < i; ++j) {
                tempQueue.pop();
            }
            std::cout << tempQueue.front() << "\t";
        } else {
            std::cout << "\t";
        }

        // Print stack2 element if available
        if (i < stack2.size()) {
            std::cout << stack2[stack2.size() - 1 - i];
        }

        std::cout << std::endl;
    }
}