#include <stdio.h>
#include <fstream>
#include <cstring>
#include "Model/nodes.h"
#include "redapple_parser.hpp"
#include "RedCodeGen.h"
#include "cmdline.h"
using namespace std;

extern FILE* yyin;
extern Node *programBlock;

char* make_default_name(const char* filename) {
	int size = 0;
	for (const char* p = filename; *p != 0; ++p, ++size)
		if (*p == '.') break;
	char* str = new char[size+4];
	strncpy(str, filename, size+1);
	str[size+1] = 'b';
	str[size+2] = 'c';
	str[size+3] = 0;
	return str;
}

Node* parseFile(const char* path) {
	FILE* file_in;
	if ((file_in = fopen(path, "r")) == NULL) {
		printf("找不到程序源文件: %s\n", path);
		return 0;
	}
	
	yyin = file_in;
	yyparse();
	fclose(file_in);

	// 打印语法树
	printf("源文件 - %s\n", path);
	programBlock->print(0);
	return programBlock;
}

int main(int argc, char **argv)
{
	cmdline::parser parser;
	parser.add("compile", 'c', "compile the fir script");
	parser.add<string>("out", 'o', "output file path", false, "run");
	parser.footer("script-file [args...]");
	parser.set_program_name("fir");
	parser.parse_check(argc, argv);
	if (parser.rest().size() == 0) {
		std::cerr<<parser.usage();
		exit(0);
	}
	for (int i = 0; i < parser.rest().size(); i++)
		cout << parser.rest()[i] << endl;


	string file_in_name = parser.rest()[0];
	Node* ans = parseFile(file_in_name.c_str());

	// 语法生成
	char* output_name = make_default_name(file_in_name.c_str());
	CodeGen* codegen = RedCodeGen::Create();
	codegen->Init();
	codegen->PreScan(ans);
	codegen->Make(ans, output_name);
	codegen->MakeMeta("meta.bc", "Meta");
	delete output_name;
	delete codegen;

	/* you should close the file. */
	return 0;
}
