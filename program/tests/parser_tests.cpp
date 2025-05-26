//---------------------
// Ivan Chetverin M3113 - ICHetverin
// Parser tests implementation
//---------------------

#include "test_framework.h"
#include "ast_builder.h"
#include "parser.h"
#include "lexer.h"
#include "grammar.h"

namespace {
    void registerTests() {
//--------------------------------------------------
// Test 1: a
//--------------------------------------------------
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

//--------------------------------------------------
// Test 2: a|b
//--------------------------------------------------
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

//--------------------------------------------------
// Test 3: a*
//--------------------------------------------------
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

//--------------------------------------------------
// Test 4: ab
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeConcatenate", [] {
                Grammar grammar;
                Lexer lexer("ab");
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

//--------------------------------------------------
// Test 5: (a)
//--------------------------------------------------
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

    static bool testsRegistered = []() {
        registerTests();
        return true;
    }();
}
