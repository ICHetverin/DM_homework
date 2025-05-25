#pragma once
#include "ast.h"
#include <memory>
#include <vector>
#include <initializer_list>

class ASTBuilder {
public:
    static std::unique_ptr<ASTNode> leaf(TokenType type, char value = 0) {
        return std::make_unique<Leaf>(Token{type, value});
    }

    template <typename... Args>
    static std::unique_ptr<ASTNode> node(NonTerminal nt, Args&&... args) {
        auto node = std::make_unique<InnerNode>(nt);
        (node->addChild(std::forward<Args>(args)), ...);
        return node;
    }
};
