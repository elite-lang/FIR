#include <stdio.h>
#include <cstring>
#include "Model/nodes.h"
#include "RedCodeGen.h"
#include "cmdline.h"
#include "fir.h"
using namespace std;



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
