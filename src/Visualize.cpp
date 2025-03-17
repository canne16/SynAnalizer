#include "Visualize.h"

void printStack(std::vector<GrammarElement*> stack) {
    // std::cout << "Stack:" << std::endl << "$";

    std::cout << "$ ";

    for (auto it = stack.rend() - 1; it != stack.rbegin() - 1; --it) {
        (*it)->display();
    }

    std::cout << "\t|";// std::endl;
}


void printBuffer(std::queue<GrammarElement*> q) {
    // std::cout << "Buffer:" << std::endl;

    while (!q.empty()) {
        q.front()->display(); 
        q.pop();
        // std::cout << " ";
    }

    std::cout << "$\t|"; // << std::endl;
}

std::string captureDisplayOutput(GrammarElement* element) {
    std::ostringstream buffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf()); // Redirect std::cout
    element->display(); // Call display() which prints to std::cout
    std::cout.rdbuf(oldCoutBuffer); // Restore original std::cout buffer
    return buffer.str(); // Get captured output
}

void printRow(std::vector<GrammarElement*> stack, std::queue<GrammarElement*> buffer, std::string action) {
    
    std::ostringstream stackStream, bufferStream;

    stackStream << "$ ";
    for (auto it = stack.rend() - 1; it != stack.rbegin() - 1; --it) {
        stackStream << captureDisplayOutput(*it); // << " ";
    }
   
    while (!buffer.empty()) {
        bufferStream << captureDisplayOutput(buffer.front()); //<< " ";
        buffer.pop();
    }

    std::cout << std::left
              << std::setw(STACK_WIDTH) << stackStream.str()
              << std::right
              << std::setw(BUFFER_WIDTH) << (bufferStream.str() + " $")
              << std::setw(ACTION_WIDTH) << action
              << std::endl;

}

void table_prompt() {
    std::cout << std::endl;
    std::cout << std::left
              << std::setw(STACK_WIDTH) << "STACK"
              << std::right
              << std::setw(BUFFER_WIDTH) << "BUFFER"
              << std::setw(ACTION_WIDTH) << "ACTION"
              << std::endl;
}