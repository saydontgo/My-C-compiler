#pragma once
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
    explicit LL1Parser(std::string grammar);
    LL1Parser() = delete;
    LL1Parser(const LL1Parser& other) = delete;
    LL1Parser& operator=(const LL1Parser&) = delete;
    LL1Parser(LL1Parser&& other);
    auto ParseTokens(const TokenStream&) -> std::shared_ptr<const ParseTreeNode>;
    void PrintErrors();

private:
    std::shared_ptr<LL1Analyzer> Analyzer_;
    std::shared_ptr<ErrorReporter> reporter_;
    std::shared_ptr<ParseTreeNode> root_;
    std::unordered_map<int, std::unordered_map<int, std::vector<std::string>*>> predict_table_;
};