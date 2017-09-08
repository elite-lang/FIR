/* 
* @Author: sxf
* @Date:   2015-11-23 22:03:33
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-25 16:42:19
*/

#pragma once

#include "LLCG/lvalue.h"

namespace llvm {
	class Value;
} // llvm

namespace fir {

class llvm_value;
typedef llvm_value* LLVMValue;
#define LLVALUE(T) (dynamic_cast<fir::llvm_value*>(T))


class llvm_value : public lvalue
{
public:
	llvm_value(llvm::Value* v);
	virtual ~llvm_value();
	
	operator llvm::Value* () const { return data; }
	virtual string getTypeName();
	
private:
	llvm::Value* data;
};



}