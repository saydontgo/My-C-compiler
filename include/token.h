#pragma once
#include <iostream>
#include <vector>
#include <atomic>

typedef int32_t lex_id_t;
typedef int32_t pos_id_t;
struct Token {
    pos_id_t pos_;
    lex_id_t id_;
    std::string lexeme_;
};

class TokenStream {
public:
    void PushBack(lex_id_t id, std::string&& lexeme);

    // print all the tokens in `[position]: <[lexeme],[id]>` format.
    void PrintAll() const;

    // print a token in `[position]: <[lexeme],[id]>` format.
    void Print(int index) const;
private:
    std::vector<Token> tokens_;
    std::atomic<int> pos_{0};
};