#pragma once
#include "lexical_analyzer.h"
#include "exception.h"
#include "error_reporter.h"
#include "symbol_table.h"

typedef int32_t lex_id_t;
typedef int32_t pos_id_t;
struct Token {
    pos_id_t pos_;
    lex_id_t id_;
    std::string lexeme_;
};

class TokenStream {
public:
    void PushBack(pos_id_t pos, lex_id_t id, std::string&& lexeme);

    // print all the tokens in `[position]: <[lexeme],[id]>` format.
    void PrintAll();

    // print a token in `[position]: <[lexeme],[id]>` format.
    void Print(int index);
private:
    std::vector<Token> tokens_;
};