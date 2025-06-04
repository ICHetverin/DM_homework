//---------------------
// Ivan Chetverin M3113 - ICHetverin
// Класс Parser
// Реализует синтаксический анализ на основе грамматики
// Строит AST для регулярных выражений
//---------------------

#pragma once

#include <grammar.h>
#include <ast.h>
#include <vector>
#include <memory>

class Parser {
    const Grammar& grammar;
    std::vector<Token> tokens;
    size_t pos = 0;

    Token current() const;
    void consume();
    bool match(TokenType type);

public:
    Parser(const Grammar& g, std::vector<Token> toks);
    std::unique_ptr<ASTNode> parse();

private:
    std::unique_ptr<ASTNode> parseR0();
    std::unique_ptr<ASTNode> parseR1();
    std::unique_ptr<ASTNode> parseS0();
    std::unique_ptr<ASTNode> parseS1();
    std::unique_ptr<ASTNode> parseT();
    std::unique_ptr<ASTNode> parseA();
    std::unique_ptr<ASTNode> parseC();
};
