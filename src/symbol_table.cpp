#include "symbol_table.h"

SymbolTable::SymbolTable() {
    RegisterKeyword("auto");
}

auto SymbolTable::Lookup(const std::string& symbol) const -> std::optional<SymbolEntry> {
    auto it = table_.find(symbol);
    if (it == table_.end()) { return std::nullopt; }

    return it->second;
}

void SymbolTable::InsertIdentifier(const std::string& identifier) {
    table_.insert({identifier, {SymbolCategory::Identifier, identifier}});
}
