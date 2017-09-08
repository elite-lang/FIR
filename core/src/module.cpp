#include "module.h"
#include "parser.hpp"
#include "scanner.h"

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
	mod->buffer = NULL;
	return mod;
}

module *
new_module_from_string(char *src)
{
	module *mod = (module *) malloc(sizeof(module));
	mod->src = NULL;
	mod->buffer = src;
	return mod;
}

void
delete_module(module *mod)
{
	if (mod->root != NULL) {
		delete mod->root;
	}
	if (mod->src != NULL) fclose(mod->src);
	free(mod);
}

int
parse_module(module *mod)
{
	yyscan_t sc;
	int res;
	yylex_init(&sc);
	if (mod->src) {
		yyset_in(mod->src, sc);
		res = yyparse(sc, mod);
	} else if (mod->buffer) {
		YY_BUFFER_STATE buffer = yy_scan_string(mod->buffer, sc);
		res = yyparse(sc, mod);
		yy_delete_buffer(buffer, sc);
	} else {
		printf("module 异常");
		exit(1);
	}
	yylex_destroy(sc);
	
	return res;
}


}