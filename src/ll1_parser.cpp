#include "ll1_parser.h"
#include <stdexcept>

LL1Parser::LL1Parser(const std::unordered_map<std::string, lex_id_t>& key_table) : reporter_(std::make_shared<ErrorReporter>()), root_(nullptr) {
    LL1Analyzer tmp(key_table);
    predict_table_ = tmp.BuildTable();

    for (const auto& KVpair : key_table) {
        name_table_.insert({KVpair.second, KVpair.first});
    }

    name_table_.insert({static_cast<int>(NonTerminalType::program), std::string("program")});
    name_table_.insert({static_cast<int>(NonTerminalType::stmt), std::string("stmt")});
    name_table_.insert({static_cast<int>(NonTerminalType::compoundstmt), std::string("compoundstmt")});
    name_table_.insert({static_cast<int>(NonTerminalType::stmts), std::string("stmts")});
    name_table_.insert({static_cast<int>(NonTerminalType::ifstmt), std::string("ifstmt")});
    name_table_.insert({static_cast<int>(NonTerminalType::whilestmt), std::string("whilestmt")});
    name_table_.insert({static_cast<int>(NonTerminalType::assgstmt), std::string("assgstmt")});
    name_table_.insert({static_cast<int>(NonTerminalType::boolexpr), std::string("boolexpr")});
    name_table_.insert({static_cast<int>(NonTerminalType::boolop), std::string("boolop")});
    name_table_.insert({static_cast<int>(NonTerminalType::arithexpr), std::string("arithexpr")});
    name_table_.insert({static_cast<int>(NonTerminalType::arithexprprime), std::string("arithexprprime")});
    name_table_.insert({static_cast<int>(NonTerminalType::multexpr), std::string("multexpr")});
    name_table_.insert({static_cast<int>(NonTerminalType::multexprprime), std::string("multexprprime")});
    name_table_.insert({static_cast<int>(NonTerminalType::simpleexpr), std::string("simpleexpr")});
}

/*
 *  parse the tokens into a parse tree (not an abstract one), if there is already a root, it will rewrite the root with a new one.
 */
auto LL1Parser::ParseTokens(std::shared_ptr<const TokenStream> tokens) -> std::shared_ptr<ParseTreeNode> {
    std::stack<int> parsing_stack;
    auto index = 0;
    parsing_stack.push(static_cast<int>(NonTerminalType::threshold) + 1);

    while (index < tokens->Size() && !parsing_stack.empty()) {
        auto symbol = parsing_stack.top();
        parsing_stack.pop();

        auto token = tokens->TokenAt(index);
        if (symbol < static_cast<int>(NonTerminalType::threshold)) {
            // it is a terminal symbol
            if (symbol == token.id_) {
                index++;
            } else {
                // missing non-terminal symbol, add it to the reporter.
                reporter_->Report(ErrorLevel::Error, ErrorCode::MissingSymbol, token.line_, token.col_, name_table_[symbol]);
            }
        } else if (symbol < static_cast<int>(NonTerminalType::end)) {
            // it is a non-terminal symbol
            auto prods = predict_table_[static_cast<NonTerminalType>(symbol)];
            if (prods.find(token.id_) != prods.end()) {
                auto prod = prods[token.id_];
                for (auto i = prod.size() - 1; i > -1; i--) {
                    parsing_stack.push(prod[i]);
                }
            } else {
                // unexpected token
                reporter_->Report(ErrorLevel::Error, ErrorCode::UnexpectedCharacterChinese, token.line_, token.col_, token.lexeme_);
                index++;
            }
        } else if (symbol > static_cast<int>(NonTerminalType::end)) {
            throw std::runtime_error("invalid symbol!\n");
        }
    }
}

void LL1Parser::PrintErrors() const {
    reporter_->PrintLL1();
}