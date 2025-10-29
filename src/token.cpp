#include "token.h"


void TokenStream::PushBack(lex_id_t id, std::string&& lexeme) {
    tokens_.push_back(Token({pos_.fetch_add(1), id, std::move(lexeme)}));
}

void TokenStream::PrintAll() const {
    for (const auto& token : tokens_) {
        std::cout << token.pos_ <<  ": <" << token.lexeme_ << "," << token.id_ << ">\n";
    }
}

void TokenStream::Print(int index) const {
    std::cout << tokens_[index].pos_ <<  ": <" << tokens_[index].lexeme_ << "," << tokens_[index].id_ << ">\n";
}