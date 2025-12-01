#pragma once
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <stack>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include "token.h"
#include "error_reporter.h"
#include "ll1_analyzer.h"
#include "parse_tree.h"

class LL1Parser {
public:
    explicit LL1Parser(const std::unordered_map<std::string, lex_id_t>& key_table);
    LL1Parser() = delete;
    LL1Parser(const LL1Parser& other) = delete;
    LL1Parser& operator=(const LL1Parser&) = delete;
    LL1Parser(LL1Parser&& other);
    auto ParseTokens(const TokenStream&) -> std::shared_ptr<const ParseTreeNode>;
    void PrintErrors();

    // for debug and output purposes
    auto GetName(int index) -> const std::string {
        assert(name_table_.find(index) != name_table_.end());
        return name_table_[index];
    }

private:
    std::shared_ptr<ErrorReporter> reporter_;
    std::shared_ptr<ParseTreeNode> root_;
    std::unordered_map<NonTerminalType, std::unordered_map<lex_id_t, std::vector<int>>> predict_table_;

    // name table, only for debug and output purposes
    std::unordered_map<int, std::string> name_table_;
};