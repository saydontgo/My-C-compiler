#pragma once
#include "lexical_analyzer.h"
#include "token.h"
#include "exception.hpp"
#include "error_reporter.h"
#include <unordered_map>

enum class SymbolCategory {
    Keyword,       // C 语言关键字
    Identifier,    // 用户定义的标识符
};

struct SymbolEntry {
    SymbolCategory type_;
    std::string name_;
};

class SymbolTable {
public:
    SymbolTable();

    // return the entry if the symbol exists.
    auto Lookup(const std::string& symbol) const -> std::optional<SymbolEntry>;

    // insert identifier
    void InsertIdentifier(const std::string& identifier);

private:
    // register keywords
    void RegisterKeyword(const std::string& keyword);
    std::unordered_map<std::string, SymbolEntry> table_;
};