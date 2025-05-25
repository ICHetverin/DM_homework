//---------------------
// Ivan Chetverin M3113 - ICHetverin
// Класс Lexer
// Преобразует входную строку в последовательность токенов
// Обрабатывает символы и преобразует их в токены для парсера
//---------------------

#pragma once

#include "token.h"
#include <vector>
#include <string>

class Lexer {
    std::string input;
    size_t pos = 0;
public:
    Lexer(const std::string& str);
    std::vector<Token> tokenize();
};
