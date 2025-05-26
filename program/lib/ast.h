//---------------------
// Ivan Chetverin M3113 - ICHetverin
// Классы AST (Abstract Syntax Tree)
// Определяет узлы абстрактного синтаксического дерева для регулярных выражений
// Включает базовый класс ASTNode и его реализации (Leaf и InnerNode)
//---------------------

#pragma once

#include <token.h>
#include <nonterminal.h>
#include <memory>
#include <vector>

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual bool equals(const ASTNode* other) const = 0;
    virtual void print(int indent = 0) const = 0;
};

class Leaf : public ASTNode {
    Token token;
public:
    Leaf(Token t);
    bool equals(const ASTNode* other) const override;
    void print(int indent) const override;
};

class InnerNode : public ASTNode {
    NonTerminal nt;
    std::vector<std::unique_ptr<ASTNode>> children;
public:
    InnerNode(NonTerminal n);

    template<typename... Args>
    InnerNode(NonTerminal n, Args&&... args) : nt(n) {
        (children.emplace_back(std::forward<Args>(args)), ...);
    }

    void addChild(std::unique_ptr<ASTNode> child) {
        children.push_back(std::move(child));
    }

    bool equals(const ASTNode* other) const override;
    void print(int indent) const override;
};
