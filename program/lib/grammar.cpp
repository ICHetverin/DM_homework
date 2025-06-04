//---------------------
// Ivan Chetverin M3113 - ICHetverin
// Реализация Grammar
// Инициализирует множества First и Follow для нетерминалов
//---------------------

#include <grammar.h>

Grammar::Grammar() {
    // First
    first[R0] = {TokenType::CHAR, TokenType::LPAREN};
    first[R1] = {TokenType::CHOICE, TokenType::EPSILON};
    first[S0] = {TokenType::CHAR, TokenType::LPAREN};
    first[S1] = {TokenType::CHAR, TokenType::LPAREN, TokenType::EPSILON};
    first[T] = {TokenType::CHAR, TokenType::LPAREN};
    first[A] = {TokenType::CHAR, TokenType::LPAREN};
    first[C] = {TokenType::KLEENE, TokenType::PLUS, TokenType::QUESTION, TokenType::EPSILON};

    // Follow
    follow[R0] = {TokenType::EOF_TOKEN, TokenType::RPAREN};
    follow[R1] = {TokenType::EOF_TOKEN, TokenType::RPAREN};
    follow[S0] = {TokenType::CHOICE, TokenType::EOF_TOKEN, TokenType::RPAREN};
    follow[S1] = {TokenType::CHOICE, TokenType::EOF_TOKEN, TokenType::RPAREN};
    follow[T] = {TokenType::CHAR, TokenType::LPAREN, TokenType::CHOICE,
                TokenType::EOF_TOKEN, TokenType::RPAREN};
    follow[A] = {TokenType::KLEENE, TokenType::PLUS, TokenType::QUESTION,
                TokenType::CHAR, TokenType::LPAREN, TokenType::CHOICE,
                TokenType::EOF_TOKEN, TokenType::RPAREN};
    follow[C] = {TokenType::CHAR, TokenType::LPAREN, TokenType::CHOICE,
                TokenType::EOF_TOKEN, TokenType::RPAREN};
}

bool Grammar::inFirst(NonTerminal nt, TokenType t) const {
    return first.at(nt).count(t);
}

bool Grammar::inFollow(NonTerminal nt, TokenType t) const {
    return follow.at(nt).count(t);
}
