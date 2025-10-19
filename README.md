# Tokenizer C++ Source Code Analyzer

## Overview
This repository contains the implementation of a **C++ Tokenizer** that reads source code from an input stream, removes preprocessor directives, and separates it into meaningful tokens such as identifiers, numbers, operators, and character literals.  
It was developed as part of the **Simon Fraser University Course Project – Part 1: Tokenizer**, focusing on lexical analysis, parsing logic, and structured program design in C++.

The tokenizer is implemented using only standard C++ libraries, emphasizing control over character-level parsing, readability, and correctness. It includes a comprehensive suite of automated unit tests using **Boost.Test** to validate functionality and edge-case behavior.

---

## Objectives
- Simulate the first phase of a compiler (lexical analysis) by building a custom tokenizer.  
- Use standard input streams and character classification for fine-grained parsing.  
- Reinforce understanding of **C++ I/O**, **string handling**, and **loop-based iteration**.  
- Verify correctness across valid, malformed, and corner-case code snippets using test-driven development.

---

## Features
- **Preprocessor Filtering** – Skips lines beginning with `#` such as `#define` and `#include`.  
- **Identifier Recognition** – Supports alphanumeric and underscore-based names (`foo_123`, `_temp`).  
- **Numeric Handling** – Parses integers, floating-point numbers, and scientific notation (`1.23e-4`).  
- **Character Literal Support** – Correctly processes `'a'`, `'\\n'`, `'\\001'` while identifying malformed literals.  
- **Operator Detection** – Recognizes single, double, and triple operators (`++`, `>>=`, `+=`, etc.).  
- **Error Recovery** – Unsupported or malformed expressions are replaced by empty tokens (`""`) for consistent output.  
- **Cross-Platform Compatibility** – Tested on Linux (g++), Windows (MSVC), and macOS (clang++).

---

## Repository Structure

| File | Description |
|------|--------------|
| `Part1Tokenizer.hpp` | Declares `tokenizeCodeStrip(std::istream&)`. |
| `Part1Tokenizer.cpp` | Implements the tokenizer logic. |
| `TestPart1.cpp` | Contains unit tests written with **Boost.Test** for automated verification. |

---

## Example Usage

### Input:
```cpp
int main() {
    double a = 3.14e-2;
    char c = '\\n';
}
