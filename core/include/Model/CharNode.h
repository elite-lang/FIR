/**
 * Project Untitled
 */

#pragma once

#include "Node.h"

namespace fir {


class CharNode: public Node {
public: 
	char value;

	CharNode(char* v) {
		value = *v;
	}

	// virtual Value* codeGen(CodeGenContext* context); 
};


}
