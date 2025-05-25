#include "test_framework.h"
#include "ast_builder.h"
#include "parser.h"
#include "lexer.h"
#include "grammar.h"

namespace {
    void registerTests() {
        // 1. Тест для одиночного символа 'a'
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeLetter", [] {
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
                    throw std::runtime_error("AST mismatch for single letter");
                }
            })
        );

        // 2. Тест для выбора 'a|b'
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeChoice", [] {
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

        // 3. Тест для замыкания 'a*'
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeKleene", [] {
                Grammar grammar;
                Lexer lexer("a*");
                Parser parser(grammar, lexer.tokenize());
                auto ast = parser.parse();

                auto expected = ASTBuilder::node(R0,
                    ASTBuilder::node(S0,
                        ASTBuilder::node(T,
                            ASTBuilder::node(A,
                                ASTBuilder::leaf(TokenType::CHAR, 'a')
                            ),
                            ASTBuilder::node(C,
                                ASTBuilder::leaf(TokenType::KLEENE),
                                ASTBuilder::node(C,
                                    ASTBuilder::leaf(TokenType::EPSILON)
                                )
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
                    throw std::runtime_error("AST mismatch for kleene star");
                }
            })
        );

        // 4. Тест для конкатенации 'ab'
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeConcatenate", [] {
                Grammar grammar;
                Lexer lexer("ab");
                Parser parser(grammar, lexer.tokenize());
                auto ast = parser.parse();

                std::cout << "Actual AST:\n";
                ast->print(2);

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
                            )
                        )
                    ),
                    ASTBuilder::node(R1,
                        ASTBuilder::leaf(TokenType::EPSILON)
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for concatenation");
                }
            })
        );

        // 5. Тест для скобок '(a)'
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeParenthesis", [] {
                Grammar grammar;
                Lexer lexer("(a)");
                Parser parser(grammar, lexer.tokenize());
                auto ast = parser.parse();

                auto expected = ASTBuilder::node(R0,
                    ASTBuilder::node(S0,
                        ASTBuilder::node(T,
                            ASTBuilder::node(A,
                                ASTBuilder::leaf(TokenType::LPAREN),
                                ASTBuilder::node(R0,
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
                                ),
                                ASTBuilder::leaf(TokenType::RPAREN)
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
                    throw std::runtime_error("AST mismatch for parenthesis");
                }
            })
        );
    }

    // Автоматическая регистрация тестов при запуске
    static bool testsRegistered = []() {
        registerTests();
        return true;
    }();
}