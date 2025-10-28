#pragma once
#include "token.h"
#include "lexical_analyzer.h"
#include "exception.hpp"
#include "symbol_table.h"

enum class ErrorLevel {
    Warning,
    Error
};

enum class ErrorCode {
    UnexpectedCharacter,
    UnterminatedString,
    InvalidEscapeSequence,
    InvalidNumberLiteral,
    UnterminatedComment
};

namespace ErrorMessages {
    static const std::unordered_map<ErrorCode, std::string> kMessageTable = {
        { ErrorCode::UnexpectedCharacter, "Unexpected character: '{}'." },
        { ErrorCode::UnterminatedString, "Unterminated string literal." },
        { ErrorCode::InvalidEscapeSequence, "Invalid escape sequence: '\\{}'." },
        { ErrorCode::InvalidNumberLiteral, "Invalid number literal." },
        { ErrorCode::UnterminatedComment, "Unterminated comment block." },
    };
}

struct LexError {
    ErrorLevel level_;
    ErrorCode code_;
    std::string formattedMessage_;
    int line_;
    int column_;
};

class ErrorReporter {
public:
    void Report(ErrorLevel level, ErrorCode code, int line, int column, const std::string& extra); // push_back method for ErrorReporter

    void PrintAll();
private:
    std::vector<LexError> errors_;
};