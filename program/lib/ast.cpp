//---------------------
// Ivan Chetverin M3113 - ICHetverin
// Реализация AST-узлов
// Содержит реализацию методов для Leaf и InnerNode
//---------------------

#include <ast.h>
#include <iostream>

void ASTNode::saveAsGraphViz(const ASTNode* root, const std::string& filename) {
    std::ofstream dotFile(filename + ".dot");
    dotFile << "digraph AST {\n";
    dotFile << "  node [shape=box, style=\"rounded,filled\", fillcolor=\"#f0f0f0\", fontname=\"Courier\"];\n";
    dotFile << "  edge [arrowhead=vee];\n\n";

    int nodeCounter = 0;
    root->generateGraphViz(dotFile, nodeCounter);

    dotFile << "}\n";
    dotFile.close();

    system(("dot -Tpng " + filename + ".dot -o " + filename + ".png").c_str());
}

Leaf::Leaf(Token t) : token(t) {}

bool Leaf::equals(const ASTNode* other) const {
    auto leaf = dynamic_cast<const Leaf*>(other);
    return leaf && token.type == leaf->token.type && token.value == leaf->token.value;
}

void Leaf::print(int indent) const {
    std::cout << std::string(indent, ' ') << "Leaf: ";
    switch(token.type) {
        case TokenType::CHAR: std::cout << token.value; break;
        case TokenType::CHOICE: std::cout << "|"; break;
        case TokenType::KLEENE: std::cout << "*"; break;
        case TokenType::LPAREN: std::cout << "("; break;
        case TokenType::RPAREN: std::cout << ")"; break;
        case TokenType::EPSILON: std::cout << "ε"; break;
        default: std::cout << "?"; break;
    }
    std::cout << std::endl;
}

std::string Leaf::getGraphVizLabel() const {
    switch (token.type) {
        case TokenType::CHAR: return std::string("CHAR: '") + token.value + "'";
        case TokenType::CHOICE: return "CHOICE: |";
        case TokenType::KLEENE: return "KLEENE: *";
        case TokenType::PLUS: return "PLUS: +";
        case TokenType::QUESTION: return "QUESTION: ?";
        case TokenType::LPAREN: return "LPAREN: (";
        case TokenType::RPAREN: return "RPAREN: )";
        case TokenType::EPSILON: return "ε";
        case TokenType::EOF_TOKEN: return "EOF";
        default: return "UNKNOWN_TOKEN";
    }
}

void Leaf::generateGraphViz(std::ostream& out, int& counter, const std::string& parentId) const {
    std::string nodeId = "node_" + std::to_string(counter++);
    out << "  " << nodeId << " [label=\"" << getGraphVizLabel() << "\"";
    out << ", fillcolor=\"#c0e0ff\"];\n";

    if (!parentId.empty()) {
        out << "  " << parentId << " -> " << nodeId << ";\n";
    }
}

InnerNode::InnerNode(NonTerminal n) : nt(n) {}

void InnerNode::addChild(std::unique_ptr<ASTNode> child) {
    children.push_back(std::move(child));
}

bool InnerNode::equals(const ASTNode* other) const {
    auto node = dynamic_cast<const InnerNode*>(other);
    if (!node || nt != node->nt || children.size() != node->children.size())
        return false;

    for (size_t i = 0; i < children.size(); ++i) {
        if (!children[i]->equals(node->children[i].get()))
            return false;
    }
    return true;
}

void InnerNode::print(int indent) const {
    std::cout << std::string(indent, ' ') << "Node: ";
    switch(nt) {
        case NonTerminal::R0: std::cout << "R0"; break;
        case NonTerminal::R1: std::cout << "R1"; break;
        case NonTerminal::S0: std::cout << "S0"; break;
        case NonTerminal::S1: std::cout << "S1"; break;
        case NonTerminal::T: std::cout << "T"; break;
        case NonTerminal::A: std::cout << "A"; break;
        case NonTerminal::C: std::cout << "C"; break;
    }
    std::cout << std::endl;

    for (auto& child : children) {
        child->print(indent + 2);
    }
}

std::string InnerNode::getGraphVizLabel() const {
    switch (nt) {
        case NonTerminal::R0: return "R0";
        case NonTerminal::S0: return "S0";
        case NonTerminal::T: return "T";
        case NonTerminal::A: return "A";
        case NonTerminal::C: return "C";
        case NonTerminal::S1: return "S1";
        case NonTerminal::R1: return "R1";
        default: return "UNKNOWN_NONTERM";
    }
}

void InnerNode::generateGraphViz(std::ostream& out, int& counter, const std::string& parentId) const {
    std::string nodeId = "node_" + std::to_string(counter++);
    out << "  " << nodeId << " [label=\"" << getGraphVizLabel() << "\"";
    out << ", fillcolor=\"#a0d0a0\"];\n";

    if (!parentId.empty()) {
        out << "  " << parentId << " -> " << nodeId << ";\n";
    }

    for (const auto& child : children) {
        child->generateGraphViz(out, counter, nodeId);
    }
}
