/**
 * Project Untitled
 */


#pragma once
 
#include "Node.h"
#include <string>
using namespace std;

namespace fir {

class FloatNode: public Node {
public:
	static FloatNode* Create(const char* num);
	virtual LValue codeGen(CodeGenContext* context);
	virtual NodeType getType();
	float getFloat();
	virtual Node* copy() {
		return new FloatNode(*this);
	}
protected:
	void printSelf();
	float value;
	FloatNode(const char* num);
};

}