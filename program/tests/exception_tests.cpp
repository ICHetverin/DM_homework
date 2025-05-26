//---------------------
// Ivan Chetverin M3113 - ICHetverin
// Parser exception tests implementation
//---------------------

#include "test_framework.h"
#include "ast_builder.h"
#include <parser.h>
#include <lexer.h>
#include <grammar.h>

namespace {
    void registerExceptionTests() {
//--------------------------------------------------
// Test 1: LexerAlphabet - uppercase letters
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("LexerAlphabet", [] {
                Grammar grammar;
                Lexer lexer("abcDef");
                Parser parser(grammar, lexer.tokenize());
                parser.parse();
            }, true)
        );

//--------------------------------------------------
// Test 2: LexerDigits - digits in expression
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("LexerDigits", [] {
                Grammar grammar;
                Lexer lexer("abcd3f");
                Parser parser(grammar, lexer.tokenize());
                parser.parse();
            }, true)
        );

//--------------------------------------------------
// Test 3: LexerSymbols - special characters
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("LexerSymbols", [] {
                Grammar grammar;
                Lexer lexer("^bcdef");
                Parser parser(grammar, lexer.tokenize());
                parser.parse();
            }, true)
        );

//--------------------------------------------------
// Test 4: StartsWithChoice - begins with pipe
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("StartsWithChoice", [] {
                Grammar grammar;
                Lexer lexer("|abcd");
                Parser parser(grammar, lexer.tokenize());
                parser.parse();
            }, true)
        );

//--------------------------------------------------
// Test 5: StartsWithChoiceEmpty - single pipe
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("StartsWithChoiceEmpty", [] {
                Grammar grammar;
                Lexer lexer("|");
                Parser parser(grammar, lexer.tokenize());
                parser.parse();
            }, true)
        );
    }

    static bool testsRegistered = []() {
        registerExceptionTests();
        return true;
    }();
}
