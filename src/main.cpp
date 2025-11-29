#include "lexical_analyzer.h"

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
	std::string prog = "{ while ( ID == NUM ) { ID = NUM } }";
	// read_prog(prog);

	// using files to read
	// std::ifstream ifs;
	// ifs.open("../test_data/mytest.in", std::ios::in);
	// if (!ifs.is_open())
    // {
    //     std::cout << "read fail." << std::endl;
	// 	std::abort();
	// }
	// char c;
	// while ((c = ifs.get()) != EOF)
	// {
	// 	prog += c;
	// }
	// prog += '\n';
	// ------------------

    /********* Begin *********/
    auto lexer = LexicalAnalyzer(prog);
	auto tokens = lexer.Tokenize();
	lexer.PrintErrors();
    tokens->PrintAll();
    /********* End *********/
	
}

int main()
{
	Analysis(); 
 	return 0;
}
