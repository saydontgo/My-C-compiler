#pragma once
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>
#include "token.h"
#include "exception.hpp"
#include "error_reporter.h"
#include "symbol_table.h"

void read_prog(std::string& prog);

void Analysis();

class LexicalAnalyzer {
public:
    explicit LexicalAnalyzer(std::string& source);
    LexicalAnalyzer() = delete;
    LexicalAnalyzer(const LexicalAnalyzer& other) = delete;
    LexicalAnalyzer& operator=(const LexicalAnalyzer&) = delete;
    auto Tokenize() -> std::shared_ptr<const TokenStream>;
private:
    std::shared_ptr<ErrorReporter> reporter_;
    std::shared_ptr<SymbolTable> table_;
    std::shared_ptr<TokenStream> tokens_;
    std::string& source_;
};