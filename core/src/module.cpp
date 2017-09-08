#include "module.h"
#include "parser.hpp"
#include "scanner.h"
#include <fstream> // for std::ofstream
#include <sstream> // for std::stringstream

extern "C" {

module *
new_module_from_stdin()
{
	module *mod = (module *) malloc(sizeof(module));
	mod->src = stdin;
	return mod;
}

module *
new_module_from_file(FILE *file)
{
	module *mod = (module *) malloc(sizeof(module));
	mod->src = file;
	return mod;
}

module *
new_module_from_string(char *src)
{
	module *mod = (module *) malloc(sizeof(module));
	// TODO: using sstream
	// mod->src = fmemopen(src, strlen(src)+1, "r");
	return mod;
}

void
delete_module(module *mod)
{
	if (mod->root != NULL) {
		delete mod->root;
	}
	fclose(mod->src);
	free(mod);
}

int
parse_module(module *mod)
{
	yyscan_t sc;
	int res;

	yylex_init(&sc);
	yyset_in(mod->src, sc);
	res = yyparse(sc, mod);
	yylex_destroy(sc);

	return res;
}


}