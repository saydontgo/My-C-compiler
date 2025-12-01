#include "ll1_parser.h"
#include <memory>

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

auto LL1Parser::ParseTokens(std::shared_ptr<const TokenStream>) -> std::shared_ptr<ParseTreeNode> {
    
}

void LL1Parser::PrintErrors() const {
    reporter_->PrintLL1();
}