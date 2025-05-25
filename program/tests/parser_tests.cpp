#include "test_framework.h"
#include "ast_builder.h"
#include "parser.h"
#include "lexer.h"
#include "grammar.h"

namespace {
    void registerTests() {
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

        TestRunner::instance().addTest(
            TestCase("Choice", [] {
                Grammar grammar;
                Lexer lexer("a|b");
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

        TestRunner::instance().addTest(
            TestCase("InvalidInput", [] {
                Grammar grammar;
                Lexer lexer("A");
                Parser parser(grammar, lexer.tokenize());
                parser.parse();
            }, true)
        );
    }

    static bool testsRegistered = []() {
        registerTests();
        return true;
    }();
}
