
# Часть 1. Лексический анализ

## 1. Анализ тестовых случаев
Изучив файлы `Test.kt` и `Tests.kt`, выделяем ключевые требования:
#### Корректные выражения:
- Одиночные символы: `a`, `x`
- Операторы:
  ```bnf
  Конкатенация: ab
  Выбор: a|b
  Повторение: a*, a+, a?
  Группировка: (a)
  Комбинации:  a(b|c)*,  x+y?,  [a-z]
  ```
## 2. Определение грамматики (LL(1))
#### Формальная грамматика с приоритетами:
```bnf
Regex         → Expr RegexTail
RegexTail     → "|" Expr RegexTail | ε
Expr          → Term ExprTail
ExprTail      → Term ExprTail | ε
Term          → Factor TermTail
TermTail      → ("*" | "+" | "?") TermTail | ε
Factor        → "(" Regex ")" | Char | "[" Range "]"
Char          → [a-z]
Range         → Char "-" Char
```
## 3. Анализ тестовых AST**
Из файла `Tests.kt` видно, что дерево использует:

**Нетерминалы** (внутренние узлы):
```kotlin
me.R0, me.S0, me.T, me.A, me.C, me.S1, me.R1
```
Это названия правил грамматики (например, `R` =  `Regex`, `A` = `Atom` и т.д.).
**Терминалы** (листья):
```kotlin
AT('a'), CHOICE ('|'), KLEENE ('*'), LPAREN ('('), RPAREN (')'), EPSILON
```

### **Соответствие токенов и AST**

Каждый терминал в тестах становится  **листом**  (`Leaf`), а нетерминал —  **внутренним узлом**  (`InnerNode`).

**Пример для  `a|b`:**
```kotlin
InnerNode(R0,
  InnerNode(S0, InnerNode(T, InnerNode(A, Leaf(AT('a')))),
  InnerNode(R1,
    Leaf(CHOICE),
    InnerNode(R0, InnerNode(S0, InnerNode(T, InnerNode(A, Leaf(AT('b')))))
  )
)
```

## **4. Реализация токенов на C++**

Создадим  `enum`  для типов токенов и структуру для хранения значений:
Типы токенов (соответствуют тестам)
```cpp
enum class TokenType {
    CHAR,               // Буква (a-z), в тестах обозначен как AT('a')
    CHOICE,             // |
    KLEENE,             // *
    PLUS,               // +
    QUESTION,           // ?
    LPAREN,             // (
    RPAREN,             // )
    EPSILON,            // Пустое правило
    EOF_TOKEN           // Конец ввода
};

// Структура токена
struct Token {
    TokenType type;
    char value;         // Для CHAR храним символ (например, 'a')
};
```

## **5. Лексер (токенизатор)**

Класс, который преобразует строку в вектор токенов:
```cpp
class Lexer {
public:
    Lexer(const std::string& input) : input(input), pos(0) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        while (pos < input.size()) {
            char c = input[pos];
            switch (c) {
                case 'a' ... 'z':
                    tokens.push_back({TokenType::CHAR, c});
                    break;
                case '|':
                    tokens.push_back({TokenType::CHOICE, 0});
                    break;
                case '*':
                    tokens.push_back({TokenType::KLEENE, 0});
                    break;
                case '+':
                    tokens.push_back({TokenType::PLUS, 0});
                    break;
                case '?':
                    tokens.push_back({TokenType::QUESTION, 0});
                    break;
                case '(':
                    tokens.push_back({TokenType::LPAREN, 0});
                    break;
                case ')':
                    tokens.push_back({TokenType::RPAREN, 0});
                    break;
                default:
                    throw std::runtime_error("Lexer error: invalid char '" + std::string(1, c) + "'");
            }
            pos++;
        }
        tokens.push_back({TokenType::EOF_TOKEN, 0}); // Конец строки
        return tokens;
    }

private:
    std::string input;
    size_t pos;
};
```