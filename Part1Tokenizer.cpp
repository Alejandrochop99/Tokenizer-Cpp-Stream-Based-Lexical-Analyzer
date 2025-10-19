/*
//============================================================================
//
//% Student Name 1: Alejandro Choapa
//% Student 1 #:
//% Student 1 userid (email):
//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put 'none' if nobody helped (the two of) you.
//
// Helpers: _none.
//
// Also, list any resources beyond the course textbook and the course pages on Piazza
// that you used in making your submission.
//
// Resources:
Sources used for research
->cppreference.com
->isocpp.org
->cplusplus.com
->LearnCpp.com
->GeeksforGeeks
->Stack Overflow
//
//%% Instructions:
//% * Put your name(s), student number(s), userid(s) in the above section.
//% * Enter the above information in Test.cpp if you are submitting that file too.
//% * Edit the "Helpers" line and "Resources" line.
//% * Your group name should be "P1_<userid1>_<userid2>" (eg. P1_stu1_stu2)
//% * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
//% * Submit one or two files to courses.cs.sfu.ca
//
// Name        : Part1Tokenizer.cpp
// Description : Tokenizer
// Original Portions Copyright (c) 2025 Simon Fraser University
//============================================================================

#include <string>
#include "Part1Tokenizer.hpp"


using namespace std;

// Accepts a stream and returns a vector of tokens with any remaining preprocessing lines stripped out
// Input: a stream
// Output: a vector of tokens
vector<string> tokenizeCodeStrip(istream& code) {

   string whitespace{" \t"};
   string string_variable;
   vector<string> incorrect;
   getline(code, string_variable);

   string::size_type index{0};
   while (index < string_variable.length()) {
      auto indexNW{string_variable.find_first_not_of(whitespace, index)};
      index = string_variable.find_first_of(whitespace, indexNW);
      incorrect.push_back(string_variable.substr(indexNW, index - indexNW));
   }

   // code.ignore(100, '\n');
   // *** Fill in implementation and likely delete the below lines ***
   //  ******* vector<string> incorrect{"An", "incorrect", "vector"};
   return incorrect;
}
*/

#include "Part1Tokenizer.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
using namespace std;

/*
we'll use vector<string which is a function that returns a dynamic array of strings.
tokenizeCodeStrip is the name of a chosen function, where (istream& code) are the input
*/
vector<string> tokenizeCodeStrip(istream& code)
{
    // We now declare an empty vector of strings.
    vector<string> tokenize;
    string line;
    /*
    We now add a loop that reads from code to the end of the file
    getline(code, line) returns a true value when it reads a line.
    The contents of the input get stored in line
    */
    while (getline(code, line))
    {
        /*
        !line.empty() checks if a line does not have a length of 0.
        line[0] == '#' checks that every first character in line is "#".
        */
        if (!line.empty() && line[0] == '#')
            continue;
        /*
        we now examine each line from 0 to line.length() we'll use a for loop
        It was recommended by Stack Overflow to use size_t instead of .length as this avoids unwanted warnings.
        */
        for (size_t i = 0; i < line.length();)
        {
            char character = line[i];
            if (isspace(character)) { i++; continue;
            }
            // isalpha(character) || character == '_' Identifies letters from a-z
            if (isalpha(character) || character == '_')
            {
                size_t start = i++; // we use i++ to advance to keep the loop touching every char
                // The while loop makes sure the next char is a letter or digit or an underscore.
                while (i < line.length() && (isalnum(line[i]) || line[i] == '_'))
                    i++;
                /*
                we use push_back to store the elements at the end of the vector
                */
                tokenize.push_back(line.substr(start, i - start));
                continue;
            }

            /*
            We'll now check if any current character is a digit between 0 and 9 by using if-else statements.
            We use the function isdigit from the cctype library to check for given 0-9 digits
            character == '.' checks whether we have a decimal present or not.
            */
            if (isdigit(character) || (character == '.' && i + 1 < line.length() && isdigit(line[i + 1])))
            {
                size_t start = i++;
                bool decimal = (character == '.'); // decimal is initialized to true if character was '.'
                while (i < line.length())
                {
                    if (isdigit(line[i])) // this filters whether the next digit is a digit or not
                    {
                        i++;
                    }
                    else if (line[i] == '.' && !decimal) // this only allows one decimal point. Eg: 122.3 and not 123.44.6
                    {
                        decimal = true;
                        i++;
                    }
                    else
                    {
                        break;
                    }
                }
                /*
                Check for scientific notation. The code looks for possible exponents
                */
                if (i < line.length() && (line[i] == 'e' || line[i] == 'E')) // checks for exponential symbol within digits.
                {
                    size_t exponent = i; // checks where e is located
                    i++;
                    if (i < line.length() && (line[i] == '+' || line[i] == '-')) // this line checks for either positive or negative exponents
                        i++;
                    size_t digitsStart = i;
                    while (i < line.length() && isdigit(line[i]))
                        i++;
                    if (digitsStart == i)
                    {
                        // no digits after 'e' → backtrack
                        i = exponent;
                    }
                }
                // push_back add stores the element at the end of the vector
                tokenize.push_back(line.substr(start, i - start));
                continue;
            }

            // The following lines of code check whether the character is a single quote.
            if (character == '\'')
            {
                size_t start = i++;
                bool valid = false;
                /*
                this while loop scans for the first and last quote '' to then tokenize the char
                */
                while (i < line.length())
                {
                    if (line[i] == '\\')
                    {
                        // skip escape sequence (\' or \\n, etc.)
                        i++;
                        if (i < line.length())
                            i++;
                    }
                    else if (line[i] == '\'')
                    {
                        // closing quote found
                        i++;
                        valid = true;
                        break;
                    }
                    else if (line[i] == ';')
                    {
                        // reached a semicolon before closing quote → malformed
                        break;
                    }
                    else {
                        i++;
                    }
                }

                if (valid)
                {
                    tokenize.push_back(line.substr(start, i - start));
                }
                else
                {
                    tokenize.push_back(""); // malformed literal
                    // Don't consume the ';' here.  Let the outer loop pick it up.
                }
                continue;
            }

            // these next lines of code only tokenize <<= and >>=
            if (i + 2 < line.length()) // this if-statement checks for the min requirement for 3 char tokens
            {
                string oper = line.substr(i, 3); // here we extract a three-char substring at i
                if (oper == ">>=" || oper == "<<=")
                {
                    tokenize.push_back(oper);
                    i += 3;
                    continue;
                }
            }

            // The following lines of code tokenize two-char operators
            if (i + 1 < line.length()) // we check for at least two chars at i and i+1
            {
                string oper = line.substr(i, 2);
                if (oper == "++" || oper == "--" || oper == "<<" || oper == ">>" ||
                    oper == "+=" || oper == "-=" || oper == "*=" || oper == "/=" || oper == "%=") {
                    tokenize.push_back(oper);
                    i += 2;
                    continue;
                }

                // Reject unsupported 2-char ops like ||, &&, |=, &= → push two empty tokens
                if (oper == "||" || oper == "&&" || oper == "|=" || oper == "&=") {
                    tokenize.push_back("");
                    tokenize.push_back("");
                    i += 2;
                    continue;
                }
            }

            /* Single-character operators/punctuators
             Very comfortable with switch operator during 1st year and
             I find the switch operator allows for well-organized code.
             Unfortunately, I cannot use switch for two- or three-char ops as it only works on a
             single integral at compile time.
            */
            switch (character)
            {
            case '+': case '-': case '*': case '/': case '%': case '=':
            case '<': case '>': case '&': case '^': case '!':
            case '~': case '?': case ':': case '(': case ')': case ';':
                tokenize.push_back(string(1, character));
                i++;
                continue;
            }

            // Unrecognized character → push empty string
            tokenize.push_back("");
            i++;
        }
    }

    return tokenize;
}

