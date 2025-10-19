//============================================================================
//
//% Student Name 1: Alejandro Choapa
//% Student 1 #:
//% Student 1 userid (email):
//

//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put 'none' if nobody helped (the two of) you.
//
// Helpers: _everybody helped us/me with the assignment (list names or put 'none')__
//
// Also, list any resources beyond the course textbook and the course pages on Piazza
// that you used in making your submission.
//
// Resources:  ___________
//
//%% Instructions:
//% * Put your name(s), student number(s), userid(s) in the above section.
//% * Edit the "Helpers" line and "Resources" line.
//% * Your group name should be "P1_<userid1>_<userid2>" (eg. P1_stu1_stu2)
//% * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
//% * Submit one or two files to courses.cs.sfu.ca
//
// Name        : TestPart1.cpp
// Description : Testing Code for Course Project Part 1 (Tokenizer)
// Original Version Copyright (c) 2025 Simon Fraser University
//============================================================================


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Course Project Part 1
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/join.hpp>

#include <sstream>

#include "Part1Tokenizer.hpp"

using namespace std;
using namespace boost::algorithm;

void testTokenStrings(string codeString, vector<string> desiredTokenVector)
{
   string newLineTab{" \n\t "};
   string newLine{" \n "};
   istringstream code(codeString);
   auto vectorToTest{tokenizeCodeStrip(code)};
   string joinedVectorToTest{newLineTab + join(vectorToTest, " \n\t ") + newLine};
   string joinedDesiredTokenVector{newLineTab + join(desiredTokenVector, " \n\t ") + newLine};

   BOOST_CHECK_EQUAL(joinedVectorToTest, joinedDesiredTokenVector);
}

BOOST_AUTO_TEST_CASE( test1 )
{
   testTokenStrings("errno = errno / 10 ;",
         {"errno","=","errno","/","10",";"});
}

BOOST_AUTO_TEST_CASE( test2 )
{
   testTokenStrings("errno=errno/10;",
         {"errno","=","errno","/","10",";"});
}

BOOST_AUTO_TEST_CASE( test3 )
{
   testTokenStrings("errno=errno/10\n;",
         {"errno","=","errno","/","10",";"});
}

BOOST_AUTO_TEST_CASE( test4 )
{
   testTokenStrings("errno=errno|10;",
         {"errno","=","errno","","10",";"});
}

BOOST_AUTO_TEST_CASE( test5 )
{
   testTokenStrings("errno=errno||10;",
         {"errno","=","errno","","","10",";"});
}

BOOST_AUTO_TEST_CASE( test6 )
{
   testTokenStrings("errno++ / +errno;",
         {"errno","++","/","+","errno",";"});
}

BOOST_AUTO_TEST_CASE( test7 )
{
   testTokenStrings("errno++/+errno;",
         {"errno","++","/","+","errno",";"});
}

BOOST_AUTO_TEST_CASE( test8 )
{
   testTokenStrings("#define MY_DEFINE \n int i;",
                              {"int","i",";"});
}

BOOST_AUTO_TEST_CASE( test9 )
{
   testTokenStrings("char    aChar    ;    aChar    =    'a'    ;  ",
                   {"char", "aChar", ";", "aChar", "=", "'a'", ";"});
}

BOOST_AUTO_TEST_CASE( test10 )
{
   testTokenStrings("errno=errno<<10;",
         {"errno","=","errno","<<","10",";"});
}

BOOST_AUTO_TEST_CASE( test11 )
{
   testTokenStrings("double a; a = 50001.1123 / .25;",
         {"double", "a", ";", "a", "=", "50001.1123","/",".25", ";"});
}

BOOST_AUTO_TEST_CASE( test12 )
{
   testTokenStrings("a = 50001..1123 / .25;",
         {"a", "=", "50001.", ".1123","/",".25", ";"});
}

BOOST_AUTO_TEST_CASE( test13 )
{
   testTokenStrings("double a; a = ..1123 / .25;",
         {"double", "a", ";", "a", "=", "", ".1123","/",".25", ";"});
}

BOOST_AUTO_TEST_CASE( test14 )
{
   testTokenStrings("double pi; pi = 314159E-5;",
         {"double","pi",";","pi","=","314159E-5",";"});
}

BOOST_AUTO_TEST_CASE( test15 )
{
   testTokenStrings("double aa; aa = 314159E-5 / 12345e-3;",
         {"double", "aa", ";", "aa","=","314159E-5","/","12345e-3",";"});
}

BOOST_AUTO_TEST_CASE( test16 )
{
   testTokenStrings("double aa; aa=35e3/4120E009;",
         {"double", "aa", ";", "aa","=","35e3","/","4120E009",";"});
}

BOOST_AUTO_TEST_CASE( test17 )
{
   testTokenStrings("char    aChar    ;    aChar    =    '\\n'    ;  ",
                   {"char", "aChar", ";", "aChar", "=", "'\\n'", ";"});
}

// Below mentioned test case would generate error by C/C++ compiler.
// However, we should be able to get some tokens for it.
BOOST_AUTO_TEST_CASE( test18 )
{
   testTokenStrings("char    aChar    ;    aChar    =   'A   ;  ",
                   {"char", "aChar", ";", "aChar", "=", "", ";"});
}

BOOST_AUTO_TEST_CASE( test19 )
{
   testTokenStrings("char    aChar    ;    aChar    =   'A\n   ;  ",
                   {"char", "aChar", ";", "aChar", "=", "",   ";"});
}

BOOST_AUTO_TEST_CASE( test20 )
{
   testTokenStrings("char    aChar    ;    aChar    =   '\n   ;  ",
                   {"char", "aChar", ";", "aChar", "=", "",  ";"});
}

BOOST_AUTO_TEST_CASE( test21 )
{
   testTokenStrings("char    aChar    ;    aChar    =    '\\001'    ;  ",
                   {"char", "aChar", ";", "aChar", "=", "'\\001'", ";"});
}

BOOST_AUTO_TEST_CASE( test22 )
{
   testTokenStrings("double a; a= 1.2e/errno;",
         {"double", "a", ";", "a", "=", "1.2", "e", "/", "errno", ";"});
}

BOOST_AUTO_TEST_CASE( test23 )
{
   testTokenStrings("double a; a= 1.2eerrno;",
         {"double", "a", ";", "a", "=", "1.2", "eerrno", ";"});
}


