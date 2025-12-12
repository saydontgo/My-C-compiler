#include "lexical_analyzer.h"
#include "ll1_parser.h"
#include "ll1_analyzer.h"
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

void Analysis(std::string& prog)
{
    /********* Begin *********/
    LexicalAnalyzer lexer(prog);
	auto tokens = lexer.Tokenize();
	lexer.PrintErrors();
    tokens->PrintAll();
	LL1Parser parser(lexer.GetTable());
	auto trees = parser.ParseTokens(tokens);
	parser.PrintErrors();
	// trees->PrintOutput();
	trees->Abstract();
	trees->PrintOutput();
    /********* End *********/
}

void test_ll1Analyzer() {
	std::string prog = "";
	LexicalAnalyzer lexer(prog);
	LL1Analyzer ana(lexer.GetTable());
	auto res = ana.BuildTable();
	LL1Parser parser(lexer.GetTable());

	ana.PrintProds();
	for (int i = static_cast<int>(NonTerminalType::threshold) + 1; i < static_cast<int>(NonTerminalType::end); i++) {
		auto nonterminal = parser.GetName(i);
		std::cout << nonterminal << ": " << std::endl;
		auto prods = res[static_cast<NonTerminalType>(i)];
		for (const auto& prod : prods) {
			std::cout << "\t" << parser.GetName(prod.first) << ": " << std::endl;
			std::cout << "\t\t" << nonterminal << " -> ";
			for (const auto& id : prod.second) {
				std::string str = "eplison";
				if (id != static_cast<int>(NonTerminalType::end)) {
					str = parser.GetName(id);
				}
				std::cout << str << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

int main(int argc, char*argv[])
{
	std::string prog = "";
	// read_prog(prog);

	if (argc != 2) { 
		std::cout << "insufficent or reduntant parameters" << std::endl;
		std::abort();
	}
	// using files to read
	std::ifstream ifs;
	ifs.open(argv[1], std::ios::in);
	if (!ifs.is_open())
    {
        std::cout << "read fail." << std::endl;
		std::abort();
	}
	char c;
	while ((c = ifs.get()) != EOF)
	{
		prog += c;
	}
	prog += '\n';


	Analysis(prog); 
	// test_ll1Analyzer();
 	return 0;
}
