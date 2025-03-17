#pragma once

#include <string>
#include <iostream>


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
    std::string type;
    Operator(const std::string& val) : value(val) {type="operator";}

    void display() const override {
        
        std::cout << value << " ";
    }
};

class Id : public GrammarElement {
private:
    int index;
    std::string value;

public:
    std::string type;
    Id(int id, const std::string& val) : index(id), value(val) {type="id";}

    void display() const override {
        std::cout << "ID" << index << " "; // << "[" << value << "]";
    }
};

class Expression : public GrammarElement {
private:
public:
    std::string type;
    Expression() {type="expression";}
    void display() const override {
        std::cout << "E ";
    }
};

class Term : public GrammarElement {
private:
public:
    std::string type;
    Term() {type="term";}
    void display() const override {
        std::cout << "T ";
    }
};

class Factor : public GrammarElement {
private:
public:
    std::string type;
    Factor() {type="factor";}
    void display() const override {
        std::cout << "F ";
    }
};