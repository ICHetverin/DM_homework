//---------------------
// Ivan Chetverin M3113 - ICHetverin
// Главный модуль программы
// Содержит тесты для проверки лексера и парсера
// TODO:
// * implement other tests
// * how-to compare AST (given-builded)
//---------------------

#include <iostream>
#include "lib/lexer.h"
#include "lib/grammar.h"
#include "lib/parser.h"

void test(const std::string& input, bool shouldPass = true) {
    static Grammar grammar;

    try {
        Lexer lexer(input);
        auto tokens = lexer.tokenize();

        Parser parser(grammar, std::move(tokens));
        auto ast = parser.parse();

        std::cout << "[PASS] " << input << std::endl;
        ast->print(1);

        if (!shouldPass) {
            std::cout << "[FAIL] Expected failure but passed: " << input << std::endl;
        }
    }
    catch (const std::exception& e) {
        if (shouldPass) {
            std::cout << "[FAIL] " << input << " - " << e.what() << std::endl;
        }
        else {
            std::cout << "[PASS] (expected fail) " << input << " - " << e.what() << std::endl;
        }
    }
}

int main() {
    // Correctness tests
    test("a");
    test("a|b");
    test("a*");
    test("a+");
    test("a??");
    test("(a)");
    test("ab");
    test("a(b|c)*");

    // Exceptions tests
    test("", false);
    test("A", false);
    test("1", false);
    test("a||b", false);
    test("*a", false);
    test("a)", false);

    return 0;
}
