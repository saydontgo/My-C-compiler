// C语言词法分析器
#include "lexical_analyzer.h"

LexicalAnalyzer::LexicalAnalyzer(std::string& source): source_(source) {
	reporter_ = std::make_shared<ErrorReporter>();
	table_ = std::make_shared<SymbolTable>();
	tokens_ = std::make_shared<TokenStream>();
}

auto LexicalAnalyzer::Tokenize() -> std::shared_ptr<const TokenStream> {
	return tokens_;
}

/* 不要修改这个标准输入函数 */
void read_prog(std::string& prog)
{
	char c;
	while (scanf("%c", &c) != EOF) {
		prog += c;
	}

	prog += '\n';
}
/* 你可以添加其他函数 */

void Analysis()
{
	std::string prog = "";
	// read_prog(prog);
    /********* Begin *********/
    auto lexer = LexicalAnalyzer(prog);
	auto tokens = lexer.Tokenize();
    tokens->PrintAll();
    /********* End *********/
	
}