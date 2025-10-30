// C语言词法分析器
#include "lexical_analyzer.h"
#include "symbol_table.h"

LexicalAnalyzer::LexicalAnalyzer(std::string& source): source_(source), pos_(0), cur_state_(StateType::Initial) {
	reporter_ = std::make_shared<ErrorReporter>();
	symbol_table_ = std::make_shared<SymbolTable>();
	tokens_ = std::make_shared<TokenStream>();

	C_keys_table_.insert({"auto", 1});
	C_keys_table_.insert({"break", 2});
	C_keys_table_.insert({"case", 3});
	C_keys_table_.insert({"char", 4});
	C_keys_table_.insert({"const", 5});

	C_keys_table_.insert({"continue", 6});
	C_keys_table_.insert({"default", 7});
	C_keys_table_.insert({"do", 8});
	C_keys_table_.insert({"double", 9});
	C_keys_table_.insert({"else", 10});
	
	C_keys_table_.insert({"enum", 11});
	C_keys_table_.insert({"extern", 12});
	C_keys_table_.insert({"float", 13});
	C_keys_table_.insert({"for", 14});
	C_keys_table_.insert({"goto", 15});

	C_keys_table_.insert({"if", 16});
	C_keys_table_.insert({"int", 17});
	C_keys_table_.insert({"long", 18});
	C_keys_table_.insert({"register", 19});
	C_keys_table_.insert({"return", 20});

	C_keys_table_.insert({"short", 21});
	C_keys_table_.insert({"signed", 22});
	C_keys_table_.insert({"sizeof", 23});
	C_keys_table_.insert({"static", 24});
	C_keys_table_.insert({"struct", 25});

	C_keys_table_.insert({"switch", 26});
	C_keys_table_.insert({"typedef", 27});
	C_keys_table_.insert({"union", 28});
	C_keys_table_.insert({"unsigned", 29});
	C_keys_table_.insert({"void", 30});

	C_keys_table_.insert({"volatile", 31});
	C_keys_table_.insert({"while", 32});
	C_keys_table_.insert({"-", 33});
	C_keys_table_.insert({"--", 34});
	C_keys_table_.insert({"-=", 35});

	C_keys_table_.insert({"->", 36});
	C_keys_table_.insert({"!", 37});
	C_keys_table_.insert({"!=", 38});
	C_keys_table_.insert({"%", 39});
	C_keys_table_.insert({"%=", 40});

	C_keys_table_.insert({"&", 41});
	C_keys_table_.insert({"&&", 42});
	C_keys_table_.insert({"&=", 43});
	C_keys_table_.insert({"(", 44});
	C_keys_table_.insert({")", 45});

	C_keys_table_.insert({"*", 46});
	C_keys_table_.insert({"*=", 47});
	C_keys_table_.insert({",", 48});
	C_keys_table_.insert({".", 49});
	C_keys_table_.insert({"/", 50});

	C_keys_table_.insert({"/=", 51});
	C_keys_table_.insert({":", 52});
	C_keys_table_.insert({";", 53});
	C_keys_table_.insert({"?", 54});
	C_keys_table_.insert({"[", 55});

	C_keys_table_.insert({"]", 56});
	C_keys_table_.insert({"^", 57});
	C_keys_table_.insert({"^=", 58});
	C_keys_table_.insert({"{", 59});
	C_keys_table_.insert({"|", 60});

	C_keys_table_.insert({"||", 61});
	C_keys_table_.insert({"|=", 62});
	C_keys_table_.insert({"}", 63});
	C_keys_table_.insert({"~", 64});
	C_keys_table_.insert({"+", 65});

	C_keys_table_.insert({"++", 66});
	C_keys_table_.insert({"+=", 67});
	C_keys_table_.insert({"<", 68});
	C_keys_table_.insert({"<<", 69});
	C_keys_table_.insert({"<<=", 70});

	C_keys_table_.insert({"<=", 71});
	C_keys_table_.insert({"=", 72});
	C_keys_table_.insert({"==", 73});
	C_keys_table_.insert({">", 74});
	C_keys_table_.insert({">=", 75});

	C_keys_table_.insert({">>", 76});
	C_keys_table_.insert({">>=", 77});
	C_keys_table_.insert({"\"", 78});
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
		FlagType flag = FlagType::Other;
		auto finish = false;
		while (!finish) {
			switch (cur_state_) {
				case StateType::Initial : {
					char ch;
					while ((ch = Peek()) == ' ' || ch == '\n' || ch == '\t') { 
						if (pos_ >= static_cast<int>(source_.size() - 1)) { return tokens_;}
						Advance(); 
					}

					if (std::isalpha(ch)) { cur_state_ = StateType::Identifier; }
					else if (std::isdigit(ch)) { cur_state_ = StateType::Integer; }

					// follow the order of ASCII
					switch (ch) {
						// ignore this two;
						case '\n': case ' ':
						cur_state_ = StateType::Initial; break;

						case '!': cur_state_ = StateType::QuestionMark; break;
						case '"': cur_state_ = StateType::DoubleQuotationMark; break;
						case '%': cur_state_ = StateType::Mod; break;
						case '&': cur_state_ = StateType::And; break;
						// case '\'': cur_state_ = StateType::QuestionMark; break; TODO!!!

						case '(': cur_state_ = StateType::LeftParenthesis; break;
						case ')': cur_state_ = StateType::RightParenthesis; break;
						case '*': cur_state_ = StateType::Multiply; break;
						case '+': cur_state_ = StateType::Plus; break;
						case ',': cur_state_ = StateType::Comma; break;

						case '-': cur_state_ = StateType::Minus; break;
						case '.': cur_state_ = StateType::Period; break;
						case '/': cur_state_ = StateType::Division; break;
						case ':': cur_state_ = StateType::Colon; break;
						case ';': cur_state_ = StateType::Semicolon; break;

						case '<': cur_state_ = StateType::LeftArrow; break;
						case '=': cur_state_ = StateType::Equal; break;
						case '>': cur_state_ = StateType::RightArrow; break;
						case '?': cur_state_ = StateType::QuestionMark; break;
						case '[': cur_state_ = StateType::LeftBracket; break;

						case ']': cur_state_ = StateType::RightBracket; break;
						case '^': cur_state_ = StateType::Xor; break;
						case '{': cur_state_ = StateType::LeftBrace; break;
						case '|': cur_state_ = StateType::And; break;
						case '}': cur_state_ = StateType::RightBrace; break;

						case '~': cur_state_ = StateType::Tilde; break;

						default :
						// report error here!
						break;
					}
					}
					break;
				case StateType::Identifier : {
					auto ch = PeekNext();
					if (std::isalnum(ch) || ch == '_') { cur_state_ = StateType::Identifier; }
					else {
						flag = FlagType::Identifier;
						cur_state_ = StateType::Finish;
					}
					token += Peek();
					Advance();
					}
					break;
				case StateType::Integer : {
					auto ch = PeekNext();
					if (std::isdigit(ch)) { cur_state_ = StateType::Integer; }
					else if (ch == '.' || ch == 'e') { cur_state_ = StateType::Float; }
					else {
						flag = FlagType::Constant;
						cur_state_ = StateType::Finish;
					}
					token += Peek();
					Advance();
					}
					break;
				case StateType::Float : {
					auto ch = PeekNext();
					if (std::isdigit(ch)) { cur_state_ = StateType::Float; }
					else {
						flag = FlagType::Constant;
						cur_state_ = StateType::Finish;
					}
					token += Peek();
					Advance();
					}
					break;
				case StateType::Minus : {
					auto ch = PeekNext();
					if (std::isdigit(ch)) { cur_state_ = StateType::Integer; }
					else if (ch == '=') { cur_state_ = StateType::MinusEqual; }
					else if (ch == '-') { cur_state_ = StateType::MinusMinus; }
					else if (ch == '>') { cur_state_ = StateType::Dereference; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::MinusMinus :
				case StateType::MinusEqual :
				case StateType::Dereference :
				case StateType::PlusPlus :
				case StateType::PlusEqual :
				case StateType::LeftParenthesis :
				case StateType::RightParenthesis :
				case StateType::Comma :
				case StateType::Period :
				case StateType::Colon :
				case StateType::Semicolon :
				case StateType::LeftBracket :
				case StateType::RightBracket :
				case StateType::LeftBrace :
				case StateType::RightBrace :
				case StateType::Tilde :
				case StateType::Reverse :
				case StateType::ModSelf :
				case StateType::AndSelf :
				case StateType::AndAnd :
				case StateType::MultiplySelf : 
				case StateType::DivisionSelf :
				case StateType::XorSelf :
				case StateType::OrSelf :
				case StateType::OrOr :
				case StateType::LeftMoveEqual :
				case StateType::LessEqual :
				case StateType::EqualEqual :
				case StateType::GreaterEqual :
				case StateType::RightMoveEqual :
				case StateType::RightWrapperHalfComments : {
					cur_state_ = StateType::Finish;
					token += Peek();
					Advance();
					}
					break;
				case StateType::QuestionMark : {
					auto ch = PeekNext();

					if (ch == '=') { cur_state_ = StateType::Reverse; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::DoubleQuotationMark : {
					auto ch = PeekNext();
					std::string str_token;

					tokens_->PushBack(C_keys_table_.find("\"")->second, "\"");
					while (ch != '\"') {
						// support multi lines, but in standard, a `\` should be added to the end of a str to indicate multi lines.
						Advance();
						// quotation is never wrapped. have to report it.
						if (IsEnd()) { /* report error here! */ }
						str_token += Peek();
						ch  = PeekNext();
					}
					if (!str_token.empty()) { tokens_->PushBack(81, std::move(str_token)); }

					token += PeekNext();
					Advance();
					Advance();
					cur_state_ = StateType::Finish;
					}
					break;
				case StateType::Mod : {
					auto ch = PeekNext();

					if (ch == '=') { cur_state_ = StateType::ModSelf; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::And : {
					auto ch = PeekNext();

					if (ch == '=') { cur_state_ = StateType::AndSelf; }
					else if (ch == '&') { cur_state_ = StateType::AndAnd; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::Multiply : {
					auto ch = PeekNext();

					if (ch == '=') { cur_state_ = StateType::MultiplySelf; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::Division : {
					auto ch = PeekNext();

					if (ch == '=') { cur_state_ = StateType::DivisionSelf; }
					else if (ch == '/') { cur_state_ = StateType::LineComments; }
					else if (ch == '*') { cur_state_ = StateType::LeftWrapperComments; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::Xor : {
					auto ch = PeekNext();

					if (ch == '=') { cur_state_ = StateType::XorSelf; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::Or : {
					auto ch = PeekNext();

					if (ch == '=') { cur_state_ = StateType::OrSelf; }
					else if (ch == '|') { cur_state_ = StateType::OrOr; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::LeftArrow : {
					auto ch = PeekNext();

					if (ch == '=') { cur_state_ = StateType::LessEqual; }
					else if (ch == '<') { cur_state_ = StateType::LeftMove; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::LeftMove : {
					auto ch = PeekNext();

					if (ch == '=') { cur_state_ = StateType::LeftMoveEqual; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::Equal : {
					auto ch = PeekNext();

					if (ch == '=') { cur_state_ = StateType::EqualEqual; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::RightArrow : {
					auto ch = PeekNext();

					if (ch == '=') { cur_state_ = StateType::GreaterEqual; }
					else if (ch == '>') { cur_state_ = StateType::RightMove; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::RightMove : {
					auto ch = PeekNext();

					if (ch == '=') { cur_state_ = StateType::RightMoveEqual; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::LineComments : {
					flag = FlagType::Comments;
					char ch;
					while((ch = PeekNext()) != '\n') {
						token += Peek();
						Advance();
					}
					token += Peek();
					Advance();
					cur_state_ = StateType::Finish;
					}
					break;
				case StateType::LeftWrapperComments : {
					flag = FlagType::Comments;
					char ch;
					while((ch = PeekNext()) != '*') {
						token += Peek();
						if (pos_ == static_cast<int>(source_.size() - 2)) { /* report error here! */ }
						Advance();
					}
					token += Peek();
					}
					cur_state_ = StateType::RightWrapperHalfComments;
					break;
				case StateType::RightWrapperComments : {
					token += Peek();
					Advance();
					}
					break;
				case StateType::Plus : {
					auto ch = PeekNext();
					if (std::isdigit(ch)) { cur_state_ = StateType::Integer; }
					else if (ch == '+') { cur_state_ = StateType::PlusPlus; }
					else if (ch == '=') { cur_state_ = StateType::PlusEqual; }
					else { cur_state_ = StateType::Finish; }

					token += Peek();
					Advance();
					}
					break;
				case StateType::Finish : {
					// first determine the type of this token, using existed table
					lex_id_t id = -1;
					switch (flag) {
						case FlagType::Comments: {
							id = 79;
						}
							break;
						case FlagType::Constant: {
							id = 80;
						}
							break;
						case FlagType::Identifier: {
							id = 81;
							auto symbol = symbol_table_->Lookup(token);
							if (!symbol.has_value()) {
								symbol_table_->InsertIdentifier(token);
							} else if (symbol.value().type_ == SymbolCategory::Keyword) {
								id = C_keys_table_.find(token)->second;
							}
						}
							break;
						case FlagType::Other: {
							id = C_keys_table_.find(token)->second;
						}
							break;
					}
					// a token has been recognized, push it to TokenStream. 
					tokens_->PushBack(id, std::move(token));
					finish = true;
					cur_state_ = StateType::Initial;
					}
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

	// using files to read
	std::ifstream ifs;
	ifs.open("../test_data/test3_in", std::ios::in);
	if (!ifs.is_open())
    {
        std::cout << "read fail." << std::endl;
        // return -1;
		std::abort();
	}
	char c;
	while ((c = ifs.get()) != EOF)
	{
		prog += c;
	}
	prog += '\n';
	// ------------------

    /********* Begin *********/
    auto lexer = LexicalAnalyzer(prog);
	auto tokens = lexer.Tokenize();
    tokens->PrintAll();
    /********* End *********/
	
}