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
    std::string symbol;

public:
    Operator(const std::string& sym) : symbol(sym) {}

    void display() const override {
        
        std::cout << symbol;
    }
};

class Id : public GrammarElement {
private:
    int index;
    std::string value;

public:
    Id(int id, const std::string& val) : index(id), value(val) {}

    void display() const override {
        std::cout << "ID" << index << "[" << value << "]";
    }
};

class Expression : public GrammarElement {
public:
    void display() const override {
        std::cout << "E";
    }
};

class Term : public GrammarElement {
public:
    void display() const override {
        std::cout << "T";
    }
};

class Factor : public GrammarElement {
public:
    void display() const override {
        std::cout << "F";
    }
};