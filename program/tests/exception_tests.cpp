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
    class Test {
    public:
        static void ParseExceptionTest(const std::string& testName, const std::string& input) {
            TestRunner::instance().addTest(
                TestCase(testName, [input] {
                    Grammar grammar;
                    Lexer lexer(input);
                    Parser parser(grammar, lexer.tokenize());
                    parser.parse();
                }, true)
            );
        }
    };

    void registerExceptionTests() {
        // Lexer-related exceptions
        Test::ParseExceptionTest("LexerAlphabet", "abcDef");
        Test::ParseExceptionTest("LexerDigits", "abcd3f");
        Test::ParseExceptionTest("LexerSymbols", "^bcdef");
        Test::ParseExceptionTest("LexerAlphabetCapital", "abcDxyz");
        Test::ParseExceptionTest("CapitalLetter", "A");
        Test::ParseExceptionTest("Digit", "0abc");
        Test::ParseExceptionTest("HatSymbol", "^abc");
        Test::ParseExceptionTest("CaretInside", "abc^def");

        // Empty input cases
        Test::ParseExceptionTest("Empty", "");
        Test::ParseExceptionTest("OnlyStars", "****");

        // Choice operator issues
        Test::ParseExceptionTest("StartsWithChoice", "|abc");
        Test::ParseExceptionTest("StartsWithChoiceEmpty", "|");
        Test::ParseExceptionTest("EndsWithChoice", "a|b|c|");
        Test::ParseExceptionTest("EndWithChoiceAgain", "x|y|z|");
        Test::ParseExceptionTest("EmptyChoice", "a||b");
        Test::ParseExceptionTest("EmptyAlternative", "(a|)");
        Test::ParseExceptionTest("StartWithChoiceAndParenthesis", "|(abc)");
        Test::ParseExceptionTest("AsteriskAfterChoice", "a|b|*");

        // Parenthesis issues
        Test::ParseExceptionTest("StartsWithRightParenthesis", ")abc(d)");
        Test::ParseExceptionTest("EndsWithOpeningParenthesis", "abc(");
        Test::ParseExceptionTest("EndWithOpeningParenthesis", "abc(");
        Test::ParseExceptionTest("UnmatchedOpeningParenthesis", "a(bc(d)e");
        Test::ParseExceptionTest("UnmatchedClosingParenthesis", "x(abc)d)e");
        Test::ParseExceptionTest("ExtraClosingParenthesis", "a(bc))");
        Test::ParseExceptionTest("ExtraOpeningParenthesis", "((abc)");
        Test::ParseExceptionTest("ExtraClosingParenthesis", "abc)");
        Test::ParseExceptionTest("BadParenthesisOrder", "a)((b)");
        Test::ParseExceptionTest("TooManyClosing", "((((a)))))))");
        Test::ParseExceptionTest("NotEnoughClosing", "(((ab))(");
        Test::ParseExceptionTest("StartWithClosingParenthesis", ")(");
        Test::ParseExceptionTest("EmptyParenthesis", "ab()");
        Test::ParseExceptionTest("EmptyParenthesisWithStar", "()*");

        // Asterisk issues
        Test::ParseExceptionTest("StartsWithAsterisk", "*abcd");
        Test::ParseExceptionTest("StartsWithAsteriskEmpty", "*");
        Test::ParseExceptionTest("AsteriskAfterLeftParenthesis", "a(*b)");
    }

    static bool testsRegistered = []() {
        registerExceptionTests();
        return true;
    }();
}
