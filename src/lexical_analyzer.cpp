// C语言词法分析器
#include "lexical_analyzer.h"

LexicalAnalyzer::LexicalAnalyzer(std::string& source): source_(source), pos_(0), cur_state_(StateType::Initial) {
	reporter_ = std::make_shared<ErrorReporter>();
	table_ = std::make_shared<SymbolTable>();
	tokens_ = std::make_shared<TokenStream>();
}

inline auto LexicalAnalyzer::Peek() const -> char {
	if (pos_ >= static_cast<int>(source_.size())) {
		throw LexerException("trying to retrive out-bound char", Module::lexical_analyzer);
	}
	return source_[pos_];
}

inline auto LexicalAnalyzer::IsEnd() const -> bool {
	return pos_ >= static_cast<int>(source_.size());
}

inline auto LexicalAnalyzer::PeekNext() const -> char {
	if (pos_ + 1 >= static_cast<int>(source_.size())) {
		throw LexerException("trying to retrive out-bound char", Module::lexical_analyzer);
	}
	return source_[pos_ + 1];
}

inline void LexicalAnalyzer::Advance() {
	++pos_;
}

auto LexicalAnalyzer::Tokenize() -> std::shared_ptr<const TokenStream> {
	while (!IsEnd()) {
		std::string token;
		while (cur_state_ != StateType::Finish) {
			switch (cur_state_) {
				case StateType::Initial : {
					auto ch = Peek();
					Advance();
					if (std::isalpha(ch)) { cur_state_ = StateType::Identifier; }
					else if (std::isdigit(ch)) { cur_state_ = StateType::Integer; }
					else if (ch == '-') { cur_state_ = StateType::Minus; }
					else if (ch == '+') { cur_state_ = StateType::Plus; }
				}
					break;
				case StateType::Identifier : {
					auto ch = Peek();
				}
					break;
				case StateType::Integer :
				break;
				case StateType::Float :
				break;
				case StateType::Minus :
				break;
				case StateType::MinusMinus :
				break;
				case StateType::MinusEqual :
				break;
				case StateType::Deference :
				break;
				case StateType::Plus :
				break;
				case StateType::PlusPlus :
				break;
				case StateType::PlusEqual :
				break;
				case StateType::Finish :
				break;
			}
		}
	}
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