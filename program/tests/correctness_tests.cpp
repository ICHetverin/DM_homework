//---------------------
// Ivan Chetverin M3113 - ICHetverin
// Parser correctness tests implementation
//---------------------

#include "test_framework.h"
#include "ast_builder.h"
#include <parser.h>
#include <lexer.h>
#include <grammar.h>

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

//--------------------------------------------------
// Test 6: abc
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeABC", [] {
                Grammar grammar;
                Lexer lexer("abc");
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
                                    ASTBuilder::node(S0,
                                        ASTBuilder::node(T,
                                            ASTBuilder::node(A,
                                                ASTBuilder::leaf(TokenType::CHAR, 'c')
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
                            )
                        )
                    ),
                    ASTBuilder::node(R1,
                        ASTBuilder::leaf(TokenType::EPSILON)
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for abc");
                }
            })
        );

//--------------------------------------------------
// Test 7: (a)
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeParenthesisA", [] {
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
                    throw std::runtime_error("AST mismatch for (a)");
                }
            })
        );

//--------------------------------------------------
// Test 8: xy
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeXY", [] {
                Grammar grammar;
                Lexer lexer("xy");
                Parser parser(grammar, lexer.tokenize());
                auto ast = parser.parse();

                auto expected = ASTBuilder::node(R0,
                    ASTBuilder::node(S0,
                        ASTBuilder::node(T,
                            ASTBuilder::node(A,
                                ASTBuilder::leaf(TokenType::CHAR, 'x')
                            ),
                            ASTBuilder::node(C,
                                ASTBuilder::leaf(TokenType::EPSILON)
                            )
                        ),
                        ASTBuilder::node(S1,
                            ASTBuilder::node(S0,
                                ASTBuilder::node(T,
                                    ASTBuilder::node(A,
                                        ASTBuilder::leaf(TokenType::CHAR, 'y')
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
                    throw std::runtime_error("AST mismatch for xy");
                }
            })
        );

//--------------------------------------------------
// Test 9: a|b|c
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeAorBorC", [] {
                Grammar grammar;
                Lexer lexer("a|b|c");
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
                                ASTBuilder::leaf(TokenType::CHOICE),
                                ASTBuilder::node(R0,
                                    ASTBuilder::node(S0,
                                        ASTBuilder::node(T,
                                            ASTBuilder::node(A,
                                                ASTBuilder::leaf(TokenType::CHAR, 'c')
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
                        )
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for a|b|c");
                }
            })
        );

//--------------------------------------------------
// Test 10: ab*
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeABstar", [] {
                Grammar grammar;
                Lexer lexer("ab*");
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
                                        ASTBuilder::leaf(TokenType::KLEENE),
                                        ASTBuilder::node(C,
                                            ASTBuilder::leaf(TokenType::EPSILON)
                                        )
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
                    throw std::runtime_error("AST mismatch for ab*");
                }
            })
        );

//--------------------------------------------------
// Test 11: x|y|z
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeXorYorZ", [] {
                Grammar grammar;
                Lexer lexer("x|y|z");
                Parser parser(grammar, lexer.tokenize());
                auto ast = parser.parse();

                auto expected = ASTBuilder::node(R0,
                    ASTBuilder::node(S0,
                        ASTBuilder::node(T,
                            ASTBuilder::node(A,
                                ASTBuilder::leaf(TokenType::CHAR, 'x')
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
                                        ASTBuilder::leaf(TokenType::CHAR, 'y')
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
                                                ASTBuilder::leaf(TokenType::CHAR, 'z')
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
                        )
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for x|y|z");
                }
            })
        );

//--------------------------------------------------
// Test 12: ab(c|d)*
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeABParenCDStar", [] {
                Grammar grammar;
                Lexer lexer("ab(c|d)*");
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
                                    ASTBuilder::node(S0,
                                        ASTBuilder::node(T,
                                            ASTBuilder::node(A,
                                                ASTBuilder::leaf(TokenType::LPAREN),
                                                ASTBuilder::node(R0,
                                                    ASTBuilder::node(S0,
                                                        ASTBuilder::node(T,
                                                            ASTBuilder::node(A,
                                                                ASTBuilder::leaf(TokenType::CHAR, 'c')
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
                                                                        ASTBuilder::leaf(TokenType::CHAR, 'd')
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
                                                ),
                                                ASTBuilder::leaf(TokenType::RPAREN)
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
                                    )
                                )
                            )
                        )
                    ),
                    ASTBuilder::node(R1,
                        ASTBuilder::leaf(TokenType::EPSILON)
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for ab(c|d)*");
                }
            })
        );

//--------------------------------------------------
// Test 13: ((a))
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeDoubleParenthesesA", [] {
                Grammar grammar;
                Lexer lexer("((a))");
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
                    throw std::runtime_error("AST mismatch for ((a))");
                }
            })
        );

//--------------------------------------------------
// Test 14: a***
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeAMultipleStars", [] {
                Grammar grammar;
                Lexer lexer("a***");
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
                                    ASTBuilder::leaf(TokenType::KLEENE),
                                    ASTBuilder::node(C,
                                        ASTBuilder::leaf(TokenType::KLEENE),
                                        ASTBuilder::node(C,
                                            ASTBuilder::leaf(TokenType::EPSILON)
                                        )
                                    )
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
                    throw std::runtime_error("AST mismatch for a***");
                }
            })
        );

//--------------------------------------------------
// Test 15: a|b*c
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("CorrectnessTreeAorBStarC", [] {
                Grammar grammar;
                Lexer lexer("a|b*c");
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
                                        ASTBuilder::leaf(TokenType::KLEENE),
                                        ASTBuilder::node(C,
                                            ASTBuilder::leaf(TokenType::EPSILON)
                                        )
                                    )
                                ),
                                ASTBuilder::node(S1,
                                    ASTBuilder::node(S0,
                                        ASTBuilder::node(T,
                                            ASTBuilder::node(A,
                                                ASTBuilder::leaf(TokenType::CHAR, 'c')
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
                        )
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for a|b*c");
                }
            })
        );

//--------------------------------------------------
// Test 16: abcdef
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("ParsesLongConcatenation", [] {
                Grammar grammar;
                Lexer lexer("abcdef");
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
                                    ASTBuilder::node(S0,
                                        ASTBuilder::node(T,
                                            ASTBuilder::node(A,
                                                ASTBuilder::leaf(TokenType::CHAR, 'c')
                                            ),
                                            ASTBuilder::node(C,
                                                ASTBuilder::leaf(TokenType::EPSILON)
                                            )
                                        ),
                                        ASTBuilder::node(S1,
                                            ASTBuilder::node(S0,
                                                ASTBuilder::node(T,
                                                    ASTBuilder::node(A,
                                                        ASTBuilder::leaf(TokenType::CHAR, 'd')
                                                    ),
                                                    ASTBuilder::node(C,
                                                        ASTBuilder::leaf(TokenType::EPSILON)
                                                    )
                                                ),
                                                ASTBuilder::node(S1,
                                                    ASTBuilder::node(S0,
                                                        ASTBuilder::node(T,
                                                            ASTBuilder::node(A,
                                                                ASTBuilder::leaf(TokenType::CHAR, 'e')
                                                            ),
                                                            ASTBuilder::node(C,
                                                                ASTBuilder::leaf(TokenType::EPSILON)
                                                            )
                                                        ),
                                                        ASTBuilder::node(S1,
                                                            ASTBuilder::node(S0,
                                                                ASTBuilder::node(T,
                                                                    ASTBuilder::node(A,
                                                                        ASTBuilder::leaf(TokenType::CHAR, 'f')
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
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    ),
                    ASTBuilder::node(R1,
                        ASTBuilder::leaf(TokenType::EPSILON)
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for long concatenation abcdef");
                }
            })
        );

//--------------------------------------------------
// Test 17: a|b|c|d|e|f
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("ParsesLongChoice", [] {
                Grammar grammar;
                Lexer lexer("a|b|c|d|e|f");
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
                                ASTBuilder::leaf(TokenType::CHOICE),
                                ASTBuilder::node(R0,
                                    ASTBuilder::node(S0,
                                        ASTBuilder::node(T,
                                            ASTBuilder::node(A,
                                                ASTBuilder::leaf(TokenType::CHAR, 'c')
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
                                                        ASTBuilder::leaf(TokenType::CHAR, 'd')
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
                                                                ASTBuilder::leaf(TokenType::CHAR, 'e')
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
                                                                        ASTBuilder::leaf(TokenType::CHAR, 'f')
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
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for long choice a|b|c|d|e|f");
                }
            })
        );

//--------------------------------------------------
// Test 18: a*****
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("ParsesLongKleene", [] {
                Grammar grammar;
                Lexer lexer("a*****");
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
                                    ASTBuilder::leaf(TokenType::KLEENE),
                                    ASTBuilder::node(C,
                                        ASTBuilder::leaf(TokenType::KLEENE),
                                        ASTBuilder::node(C,
                                            ASTBuilder::leaf(TokenType::KLEENE),
                                            ASTBuilder::node(C,
                                                ASTBuilder::leaf(TokenType::KLEENE),
                                                ASTBuilder::node(C,
                                                    ASTBuilder::leaf(TokenType::EPSILON)
                                                )
                                            )
                                        )
                                    )
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
                    throw std::runtime_error("AST mismatch for long kleene a*****");
                }
            })
        );

//--------------------------------------------------
// Test 19: (((((a)))))
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("ParsesLongParenthesis", [] {
                Grammar grammar;
                Lexer lexer("(((((a)))))");
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
                                                ASTBuilder::leaf(TokenType::LPAREN),
                                                ASTBuilder::node(R0,
                                                    ASTBuilder::node(S0,
                                                        ASTBuilder::node(T,
                                                            ASTBuilder::node(A,
                                                                ASTBuilder::leaf(TokenType::LPAREN),
                                                                ASTBuilder::node(R0,
                                                                    ASTBuilder::node(S0,
                                                                        ASTBuilder::node(T,
                                                                            ASTBuilder::node(A,
                                                                                ASTBuilder::leaf(TokenType::LPAREN),
                                                                                ASTBuilder::node(R0,
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
                    throw std::runtime_error("AST mismatch for long parenthesis (((((a)))))");
                }
            })
        );

//--------------------------------------------------
// Test 20: ab|c*d(e|f)
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("ParsesMixedComplex", [] {
                Grammar grammar;
                Lexer lexer("ab|c*d(e|f)");
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
                        ASTBuilder::leaf(TokenType::CHOICE),
                        ASTBuilder::node(R0,
                            ASTBuilder::node(S0,
                                ASTBuilder::node(T,
                                    ASTBuilder::node(A,
                                        ASTBuilder::leaf(TokenType::CHAR, 'c')
                                    ),
                                    ASTBuilder::node(C,
                                        ASTBuilder::leaf(TokenType::KLEENE),
                                        ASTBuilder::node(C,
                                            ASTBuilder::leaf(TokenType::EPSILON)
                                        )
                                    )
                                ),
                                ASTBuilder::node(S1,
                                    ASTBuilder::node(S0,
                                        ASTBuilder::node(T,
                                            ASTBuilder::node(A,
                                                ASTBuilder::leaf(TokenType::CHAR, 'd')
                                            ),
                                            ASTBuilder::node(C,
                                                ASTBuilder::leaf(TokenType::EPSILON)
                                            )
                                        ),
                                        ASTBuilder::node(S1,
                                            ASTBuilder::node(S0,
                                                ASTBuilder::node(T,
                                                    ASTBuilder::node(A,
                                                        ASTBuilder::leaf(TokenType::LPAREN),
                                                        ASTBuilder::node(R0,
                                                            ASTBuilder::node(S0,
                                                                ASTBuilder::node(T,
                                                                    ASTBuilder::node(A,
                                                                        ASTBuilder::leaf(TokenType::CHAR, 'e')
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
                                                                                ASTBuilder::leaf(TokenType::CHAR, 'f')
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
                                            )
                                        )
                                    )
                                )
                            ),
                            ASTBuilder::node(R1,
                                ASTBuilder::leaf(TokenType::EPSILON)
                            )
                        )
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for mixed complex expression ab|c*d(e|f)");
                }
            })
        );

//--------------------------------------------------
// Test 21: ((ab)*)*|x
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("ParsesNestedParenthesisKleene", [] {
                Grammar grammar;
                Lexer lexer("((ab)*)*|x");
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
                                                ),
                                                ASTBuilder::leaf(TokenType::RPAREN)
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
                                ),
                                ASTBuilder::leaf(TokenType::RPAREN)
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
                        ASTBuilder::leaf(TokenType::CHOICE),
                        ASTBuilder::node(R0,
                            ASTBuilder::node(S0,
                                ASTBuilder::node(T,
                                    ASTBuilder::node(A,
                                        ASTBuilder::leaf(TokenType::CHAR, 'x')
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
                    throw std::runtime_error("AST mismatch for ((ab)*)*|x");
                }
            })
        );

//--------------------------------------------------
// Test 22: (((a)|(b))|c)*)
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("ParsesNestedChoiceKleene_CustomAST", [] {
                Grammar grammar;
                Lexer lexer("(((a)|(b))|c)*");
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
                                                ASTBuilder::leaf(TokenType::LPAREN),
                                                ASTBuilder::node(R0,
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
                                                        ASTBuilder::leaf(TokenType::CHOICE),
                                                        ASTBuilder::node(R0,
                                                            ASTBuilder::node(S0,
                                                                ASTBuilder::node(T,
                                                                    ASTBuilder::node(A,
                                                                        ASTBuilder::leaf(TokenType::LPAREN),
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
                                                        )
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
                                        ASTBuilder::leaf(TokenType::CHOICE),
                                        ASTBuilder::node(R0,
                                            ASTBuilder::node(S0,
                                                ASTBuilder::node(T,
                                                    ASTBuilder::node(A,
                                                        ASTBuilder::leaf(TokenType::CHAR, 'c')
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
                                ),
                                ASTBuilder::leaf(TokenType::RPAREN)
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
                    throw std::runtime_error("AST mismatch for (((a)|(b))|c)*");
                }
            })
        );

//--------------------------------------------------
// Test 23: (a|b)|(c|(d|e))*
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("ParsesMultipleChoiceParenthesis", [] {
                Grammar grammar;
                Lexer lexer("(a|b)|(c|(d|e))*");
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
                        ASTBuilder::leaf(TokenType::CHOICE),
                        ASTBuilder::node(R0,
                            ASTBuilder::node(S0,
                                ASTBuilder::node(T,
                                    ASTBuilder::node(A,
                                        ASTBuilder::leaf(TokenType::LPAREN),
                                        ASTBuilder::node(R0,
                                            ASTBuilder::node(S0,
                                                ASTBuilder::node(T,
                                                    ASTBuilder::node(A,
                                                        ASTBuilder::leaf(TokenType::CHAR, 'c')
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
                                                                ASTBuilder::leaf(TokenType::LPAREN),
                                                                ASTBuilder::node(R0,
                                                                    ASTBuilder::node(S0,
                                                                        ASTBuilder::node(T,
                                                                            ASTBuilder::node(A,
                                                                                ASTBuilder::leaf(TokenType::CHAR, 'd')
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
                                                                                        ASTBuilder::leaf(TokenType::CHAR, 'e')
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
                                                )
                                            )
                                        ),
                                        ASTBuilder::leaf(TokenType::RPAREN)
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
                        )
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for (a|b)|(c|(d|e))*");
                }
            })
        );

//--------------------------------------------------
// Test 24: xyz
//--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("SimpleLetters", [] {
                Grammar grammar;
                Lexer lexer("xyz");
                Parser parser(grammar, lexer.tokenize());
                auto ast = parser.parse();

                auto expected = ASTBuilder::node(R0,
                    ASTBuilder::node(S0,
                        ASTBuilder::node(T,
                            ASTBuilder::node(A,
                                ASTBuilder::leaf(TokenType::CHAR, 'x')
                            ),
                            ASTBuilder::node(C,
                                ASTBuilder::leaf(TokenType::EPSILON)
                            )
                        ),
                        ASTBuilder::node(S1,
                            ASTBuilder::node(S0,
                                ASTBuilder::node(T,
                                    ASTBuilder::node(A,
                                        ASTBuilder::leaf(TokenType::CHAR, 'y')
                                    ),
                                    ASTBuilder::node(C,
                                        ASTBuilder::leaf(TokenType::EPSILON)
                                    )
                                ),
                                ASTBuilder::node(S1,
                                    ASTBuilder::node(S0,
                                        ASTBuilder::node(T,
                                            ASTBuilder::node(A,
                                                ASTBuilder::leaf(TokenType::CHAR, 'z')
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
                            )
                        )
                    ),
                    ASTBuilder::node(R1,
                        ASTBuilder::leaf(TokenType::EPSILON)
                    )
                );

                if (!expected->equals(ast.get())) {
                    throw std::runtime_error("AST mismatch for xyz");
                }
            })
        );
    }

    static bool testsRegistered = []() {
        registerTests();
        return true;
    }();
}
