#ifndef __MODULE_H
#define __MODULE_H

#include <stdio.h>
#include "Model/Node.h"

extern "C" {

typedef struct {
	FILE *src;
	const char* buffer;
	fir::Node *root;
	bool at_line_end;
} module;

module *new_module_from_stdin();
module *new_module_from_file(FILE* file);
module *new_module_from_string(char *src);
void delete_module(module *mod);
int parse_module(module *mod);

}

#endif // __MODULE_H
