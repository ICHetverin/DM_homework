//---------------------
// Ivan Chetverin M3113 - ICHetverin
// AST Visualization Tests
// Тесты для проверки визуализации AST через GraphViz
//---------------------

#include "test_framework.h"
#include "ast_builder.h"
#include <parser.h>
#include <lexer.h>
#include <grammar.h>
#include <ast.h>
#include <iostream>

const std::string path = "../../tests/";

namespace {
    void registerVisualizationTests() {
        //--------------------------------------------------
        // Test 1: Vizualization 'a'
        //--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("VisualizationSingleChar", [] {
                Grammar grammar;
                Lexer lexer("a");
                Parser parser(grammar, lexer.tokenize());
                auto ast = parser.parse();

                ASTNode::saveAsGraphViz(ast.get(), path + "ast_single_char");

                std::ifstream dot_file(path + "ast_single_char.dot");
                if (!dot_file.good()) {
                    throw std::runtime_error("DOT file not created for single char");
                }
                dot_file.close();

                std::ifstream png_file(path + "ast_single_char.png");
                if (!png_file.good()) {
                    throw std::runtime_error("PNG file not created for single char");
                }
                png_file.close();
            })
        );

        //--------------------------------------------------
        // Test 2: Vizualization 'a|b'
        //--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("VisualizationChoice", [] {
                Grammar grammar;
                Lexer lexer("a|b");
                Parser parser(grammar, lexer.tokenize());
                auto ast = parser.parse();

                ASTNode::saveAsGraphViz(ast.get(), path + "ast_choice");

                std::ifstream dot_file(path + "ast_choice.dot");
                std::ifstream png_file(path + "ast_choice.png");

                if (!dot_file.good() || !png_file.good()) {
                    throw std::runtime_error("Files not created for choice");
                }
            })
        );

        //--------------------------------------------------
        // Test 3: Vizualization 'a*'
        //--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("VisualizationKleene", [] {
                Grammar grammar;
                Lexer lexer("a*");
                Parser parser(grammar, lexer.tokenize());
                auto ast = parser.parse();

                ASTNode::saveAsGraphViz(ast.get(), path + "ast_kleene");

                std::ifstream dot_file(path + "ast_kleene.dot");
                if (!dot_file) {
                    throw std::runtime_error("Kleene star visualization failed");
                }
            })
        );

        //--------------------------------------------------
        // Test 4: Vizualization '(a|b)*c'
        //--------------------------------------------------
        TestRunner::instance().addTest(
            TestCase("VisualizationComplex", [] {
                Grammar grammar;
                Lexer lexer("(a|b)*c");
                Parser parser(grammar, lexer.tokenize());
                auto ast = parser.parse();

                ASTNode::saveAsGraphViz(ast.get(), path + "ast_complex");

                std::ifstream dot_file(path + "ast_complex.dot");
                dot_file.seekg(0, std::ios::end);
                if (dot_file.tellg() < 100) {
                    throw std::runtime_error("Complex AST visualization too small");
                }
            })
        );
    }

    struct TestRegistrar {
        TestRegistrar() {
            registerVisualizationTests();
        }
    };
    static TestRegistrar registrar;
}