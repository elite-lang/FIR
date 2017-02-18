/* 
* @Author: sxf
* @Date:   2015-11-24 08:43:52
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-21 16:44:22
*/


#pragma once


#include "LLCG/lvalue.h"

class llvm_type;

typedef llvm_type* LLVMType;
#define LLTYPE(T) (dynamic_cast<llvm_type*>(T))

namespace llvm {
	class Type;
} // llvm

class llvm_type : public lvalue
{
public:
	llvm_type(llvm::Type* v);
	virtual ~llvm_type();

	operator llvm::Type* () const { return data; }
	virtual bool isStructType();
	virtual string getTypeName();
	virtual LValue getPointerTo();
private:
	llvm::Type* data;
};

