
# SynAnalyzer

**SynAnalyzer** is a simple syntax analysis tool built using C++ and Flex. It includes features for parsing and analyzing input data using a lexer and an LR(0) parser, and supports testing via Google Test.

## Features
- **Syntax Analyzer**: The core functionality that parses input data.
- **Lexer**: Automatically generated using Flex, to tokenize input.
- **Visualizer**: To visualize the analysis output.
- **Testing**: Unit tests are written using Google Test framework.

## Requirements

- **CMake** (Version 3.14 or higher)
- **C++11 or hi1+gher**
- **Flex** (for lexer generation)
- **Google Test** (for testing)

## Build Instructions

1. **Clone the repository**:
   ```
   git clone https://github.com/your_username/SynAnalyzer.git
   cd SynAnalyzer
   ```

2. **Create a build directory**:
   ```
   mkdir build
   cd build
   ```

3. **Run CMake to configure the project**:
   ```
   cmake ..
   ```

4. **Build the project**:
   ```
   make
   ```

5. **Run the executable**:
   ```
   ./SynAnalyzer
   ```

## Project Structure

```
SynAnalyzer/
├── CMakeLists.txt        # CMake configuration file
├── include/              # Header files
│   ├── Analyzer.h        # Main analyzer class
│   └── ...
├── src/                  # Source files
│   ├── main.cpp          # Main application entry
│   ├── Analyzer.cpp      # Implementation of the analyzer
│   └── Visualize.cpp     # Visualization logic
├── tests/                # Unit tests
│   ├── test_main.cpp     # Test entry point
│   ├── test_SynAnalyzer.cpp  # SynAnalyzer test cases
│   └── ...
├── lexer.l               # Flex lexer specification
└── README.md             # This file
```

## Google Test Integration

The project includes tests using the Google Test framework. To run the tests:

1. **Build the tests**:
   ```
   cmake --build . --target runTests
   ```

2. **Run the tests**:
   ```
   ./runTests
   ```

3. **Testing with CMake**: After running `make`, you can also run tests with CMake directly:
   ```
   ctest
   ```

## CMake Configuration

This project uses CMake to handle the build process. Here's a breakdown of the key components in the `CMakeLists.txt` file:

- **Project Configuration**:
   - The project is configured with CMake minimum version 3.14 and set to use the C++11 standard.
   - `Config.h` is generated via `configure_file`, allowing for configuration settings in header files.

- **Lexer Generation**:
   - The lexer is automatically generated using Flex. The `FLEX_TARGET` command compiles the `lexer.l` file into `lexer.cpp`.

- **Google Test Fetching**:
   - Google Test is fetched from the official GitHub repository using the `FetchContent` module.
   - The version `v1.16.0` is specifically used.

- **Building the Executables**:
   - **SynAnalyzer**: The main executable for the syntax analysis.
   - **runTests**: The executable for running unit tests, which is linked with Google Test and compiled with the necessary source files.

- **Target Definitions**:
   - The `runTests` executable is compiled with the definition `TESTING` to indicate that it's for running tests.
   - Google Test is linked to the test executable along with the `pthread` library.

- **Testing**:
   - The `enable_testing()` command is used to enable the `ctest` testing functionality, and a basic test is added using `add_test()`.

## Example Usage

### Running the Syntax Analyzer

To analyze an input string using the `SynAnalyzer` executable:

```bash
echo "(x + y) / 2 - z $" | ./SynAnalyzer
```

### Running Tests

To run the tests, after building the project:

```bash
./runTests
```