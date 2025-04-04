#pragma once

#include <string>
#include <iostream>
#include "Codes.h"


class GrammarElement {
public:
    virtual void display() const {
        std::cout << "This is a generic GrammarElement.\n";
    }

    virtual ~GrammarElement() = default;
};

class Operator : public GrammarElement {
private:
public:

    std::string value;
    ElementType type;
    Operator(const std::string& val) : value(val) {type=OPERATOR;}

    void display() const override {
        
        std::cout << value; // << " ";
    }
};

class Id : public GrammarElement {
private:
    int index;
    std::string value;

public:
    ElementType type;
    Id(int id, const std::string& val) : index(id), value(val) {type=ID;}

    void display() const override {
        std::cout << "id" << index; // << " "; // << "[" << value << "]";
    }
};

class Expression : public GrammarElement {
private:
public:
    ElementType type;
    Expression() {type=EXPRESSION;}
    void display() const override {
        std::cout << "E";
    }
};

class Term : public GrammarElement {
private:
public:
    ElementType type;
    Term() {type=TERM;}
    void display() const override {
        std::cout << "T";
    }
};

class Factor : public GrammarElement {
private:
public:
    std::string type;
    Factor() {type=FACTOR;}
    void display() const override {
        std::cout << "F";
    }
};