#pragma once

#include <string>
#include <iostream>
#include "Codes.h"


class GrammarElement {
public:

    ElementType type;
    std::string value;
    int index;

    GrammarElement(ElementType t, const std::string& val = "", int id = -1) : type(t), value(val), index(id) {}
    
    void display() const {
        if (type == ElementType::OPERATOR) {
            std::cout << value;
        } else if (type == ElementType::ID) {
            std::cout << "id" << index; 
        } else if (type == ElementType::EXPRESSION) {
            std::cout << "E";
        } else if (type == ElementType::TERM) {
            std::cout << "T";
        } else if (type == ElementType::FACTOR) {
            std::cout << "F";
        }
    }

    virtual ~GrammarElement() = default;
};