/**
 * Project Untitled
 */


#pragma once
#include "Node.h"

namespace fir {

class IntNode: public Node {
public: 
	static IntNode* Create(const char* num);
	virtual LValue codeGen(CodeGenContext* context); 
	virtual void printSelf();
	virtual NodeType getType();
	virtual Node* copy() {
		return new IntNode(*this);
	}
protected:
	IntNode(const char* num);
	int value;
};

}