/* 
* @Author: sxf
* @Date:   2015-09-22 22:00:32
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-25 15:46:49
*/

#pragma once
#include "Node.h"
#include <string>

using namespace std;

namespace fir {

class StringNode : public Node
{
public:
	static StringNode* Create(const char* _value);
	static StringNode* Create(char _value);
	std::string& getStr() { return value; }
	virtual LValue codeGen(CodeGenContext* context); 
	virtual NodeType getType();
	virtual Node* copy() {
		return new StringNode(*this);
	}
protected:
	virtual void printSelf();
	StringNode(const char* _value);
	StringNode(char _value);
private:
	string value;
};



}