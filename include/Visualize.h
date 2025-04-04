#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <sstream>

#include "Grammar.h"

const int STACK_WIDTH = 20;  
const int BUFFER_WIDTH = 40; 
const int ACTION_WIDTH = 17; 

void printStack(std::vector<GrammarElement> stack);

void printBuffer(std::queue<GrammarElement> q);

std::string captureDisplayOutput(GrammarElement element);

void printRow(std::vector<GrammarElement> stack, std::queue<GrammarElement> buffer, std::string action);

void table_prompt();