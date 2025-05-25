#include "test_framework.h"
#include "ast_builder.h"
#include "parser.h"
#include "lexer.h"
#include "grammar.h"

namespace {
    void registerTests() {
        // Тест на одиночный символ
        TestRunner::instance().addTest(
            TestCase("SingleChar", [] {
                Grammar grammar;
                Lexer lexer("a");
                Parser parser(grammar, lexer.tokenize());
                auto ast = parser.parse();

                auto expected = ASTBuilder::node(R0,
                    ASTBuilder::node(S0,
                        ASTBuilder::node(T,
                            ASTBuilder::node(A,
                                ASTBuilder::leaf(TokenType::CHAR, 'a')
                            ),
                            ASTBuilder::node(C,
                                ASTBuilder::leaf(TokenType::EPSILON)
                            )
                        ),
                        ASTBuilder::node(S1,
                            ASTBuilder::leaf(TokenType::EPSILON)
                        )
                    ),
                    ASTBuilder::node(R1,
                        ASTBuilder::leaf(TokenType::EPSILON)
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for single char");
                }
            })
        );

        // Тест на выбор (a|b)
        TestRunner::instance().addTest(
            TestCase("Choice", [] {
                Grammar grammar;
                Lexer lexer("a|b");
                Parser parser(grammar, lexer.tokenize());
                auto ast = parser.parse();

                auto expected = ASTBuilder::node(R0,
                    ASTBuilder::node(S0,
                        ASTBuilder::node(T,
                            ASTBuilder::node(A,
                                ASTBuilder::leaf(TokenType::CHAR, 'a')
                            ),
                            ASTBuilder::node(C,
                                ASTBuilder::leaf(TokenType::EPSILON)
                            )
                        ),
                        ASTBuilder::node(S1,
                            ASTBuilder::leaf(TokenType::EPSILON)
                        )
                    ),
                    ASTBuilder::node(R1,
                        ASTBuilder::leaf(TokenType::CHOICE),
                        ASTBuilder::node(R0,
                            ASTBuilder::node(S0,
                                ASTBuilder::node(T,
                                    ASTBuilder::node(A,
                                        ASTBuilder::leaf(TokenType::CHAR, 'b')
                                    ),
                                    ASTBuilder::node(C,
                                        ASTBuilder::leaf(TokenType::EPSILON)
                                    )
                                ),
                                ASTBuilder::node(S1,
                                    ASTBuilder::leaf(TokenType::EPSILON)
                                )
                            ),
                            ASTBuilder::node(R1,
                                ASTBuilder::leaf(TokenType::EPSILON)
                            )
                        )
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for choice");
                }
            })
        );

        // Тест на ошибку
        TestRunner::instance().addTest(
            TestCase("InvalidInput", [] {
                Grammar grammar;
                Lexer lexer("A"); // Недопустимый символ
                Parser parser(grammar, lexer.tokenize());
                parser.parse(); // Должен бросить исключение
            }, true) // Ожидаем ошибку
        );
    }

    // Автоматическая регистрация тестов
    static bool testsRegistered = []() {
        registerTests();
        return true;
    }();
}
