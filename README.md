
# SynAnalyzer

**SynAnalyzer** is a simple **shift-reduce** syntax analysis tool built using C++ and Flex. It includes features for parsing and analyzing input data using a lexer, and supports testing via Google Test. It is designed for primitive language, which grammar is following:

## LR Grammar

$$ E \Rightarrow E+T | E-T | T $$
$$ T \Rightarrow T\cdot F | T/F | F $$
$$ F \Rightarrow (E) | id $$

The language consists of addition, subtraction, multiplication, division, and parentheses. Operations can be performed on variables or numbers. **Only x, y, and z can be used as variables.**

## Requirements

- **CMake** (Version 3.14 or higher)
- **C++11 or higher**
- **Flex** (for lexer generation)

## Build Instructions

0. **Install Flex (if not installed)**:

   ```bash
   sudo apt install flex
   ```

1. **Clone the repository**:

   ```bash
   git clone https://github.com/canne16/SynAnalyzer.git
   cd SynAnalyzer
   ```

2. **Create a build directory**:

   ```bash
   mkdir build
   cd build
   ```

3. **Run CMake to configure the project**:

   ```bash
   cmake ..
   ```

4. **Build the project**:

   ```bash
   cmake --build .
   ```

5. **Run the executable**:

   ```bash
   ./SynAnalyzer
   ```

## Project Structure

```bash
SynAnalyzer/
├── CMakeLists.txt            # CMake configuration file
├── include/                  # Header files
│   ├── Analyzer.h            # Syntax analyzer class
│   ├── Codes.h               # Return code definitions
│   ├── Grammar.h             # Grammar structure classes
│   └── Visualize.h           # Visualization utilities
├── src/                      # Source files
│   ├── main.cpp              # Main application entry point
│   ├── lexer.l               # Flex lexer specification
│   ├── Analyzer.cpp          # Implementation of the analyzer
│   └── Visualize.cpp         # Visualization functions
├── tests/                    # Unit tests
│   ├── test_main.cpp         # Test entry point
│   └── test_SynAnalyzer.cpp  # SynAnalyzer test cases
├── Config.h.in               # Template for configuration header file
│
└── README.md                 # This file
```

## Google Test Integration

The project includes tests using the Google Test framework. To run the tests:

1. **Build the tests**:

   ```bash
   cmake --build . --target runTests
   ```

2. **Run the tests**:

   ```bash
   ./runTests
   ```

## Example Usage

### Running the Syntax Analyzer

**Important**: only x, y, and z can be used as variables. Parsing is ended with symbol **$**. Each input therefore should end with **$**.

To analyze an input string using the `SynAnalyzer` executable:

```bash
echo "(x + y) / 2 - z $" | ./SynAnalyzer
```

### Analyzing input from file

- **to be done in future**
