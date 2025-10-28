#include "error_reporter.h"

void ErrorReporter::Report(ErrorLevel level, ErrorCode code, int line, int column, const std::string& extra) {
    std::string messageTemplate = ErrorMessages::kMessageTable.at(code);

    // replace placeholder with string `extra`
    std::string formatted = messageTemplate;
    size_t pos = formatted.find("{}");
    if (pos != std::string::npos) {
        formatted.replace(pos, 2, extra);
    }

    errors_.push_back({ level, code, formatted, line, column });
}

void ErrorReporter::PrintAll() {
    if (errors_.empty()) { return; }

    std::cout << std::endl;
    for (const auto& error : errors_) {
        std::string level = error.level == ErrorLevel::Warning ? "Warning " : "Error ";
        std::cout << level << "[line " << error.line << ", col " << error.column << "]: " << error.formattedMessage << std::endl;
    }
    std::cout << std::endl;
}