// C语言词法分析器
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
	std::string prog;
	read_prog(prog);
    /********* Begin *********/
    
    
    /********* End *********/
	
}