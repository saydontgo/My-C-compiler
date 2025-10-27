// C语言词法分析器
#include "lexical_analyzer.h"
#include "token.h"
#include "exception.h"
#include "error_reporter.h"
#include "symbol_table.h"
#include "token_stream.h"

/* 不要修改这个标准输入函数 */
void read_prog(std::string& prog)
{
	char c;
	while (scanf("%c", &c) != EOF) {
		prog += c;
	}
}
/* 你可以添加其他函数 */

void Analysis()
{
	std::string prog;
	read_prog(prog);
    /********* Begin *********/
    
    
    /********* End *********/
	
}