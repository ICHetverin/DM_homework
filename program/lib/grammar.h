//---------------------
// Ivan Chetverin M3113 - ICHetverin
// Класс Grammar
// Содержит множества First и Follow для нетерминалов грамматики
// Используется парсером для принятия решений при разборе
//---------------------

#pragma once

#include <token.h>
#include <nonterminal.h>
#include <unordered_map>
#include <unordered_set>

class Grammar {
    std::unordered_map<NonTerminal, std::unordered_set<TokenType>> first;
    std::unordered_map<NonTerminal, std::unordered_set<TokenType>> follow;

public:
    Grammar();
    bool inFirst(NonTerminal nt, TokenType t) const;
    bool inFollow(NonTerminal nt, TokenType t) const;
};
