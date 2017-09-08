/**
 * Project Untitled
 */

#pragma once

#include "Node.h"
#include <string>

using namespace std;

namespace fir {

class IDNode: public Node {
public: 
	static IDNode* Create(const char* _value);
	static IDNode* Create(char _value);
	std::string& getStr() { return value; }
	virtual LValue codeGen(CodeGenContext* context); 
	virtual NodeType getType();
	virtual Node* copy() {
		return new IDNode(*this);
	}
protected:
	IDNode(const char* _value);
	IDNode(char _value);
	virtual void printSelf();
private:
	string value;
};

}