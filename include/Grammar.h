#pragma once

#include <string>
#include <iostream>
#include "Codes.h"


class GrammarElement {

private:
    ElementType type;
    std::string value;
    int index;
public:

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
        } else if (type == ElementType::INV_EXPR) {
            std::cout << " (?) ";
        }
    }

    ElementType getType()  const { return type; }
    std::string getValue() const { return value; }
    int         getIndex() const { return index; }


    virtual ~GrammarElement() = default;
};