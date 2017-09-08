/*
* @Author: sxf
* @Date:   2015-11-23 21:37:15
* @Last Modified by:   sxf
* @Last Modified time: 2016-01-01 17:16:39
*/


#pragma once

#include "LLCG/llcg.h"

#include "llvm/IR/Verifier.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/IR/ValueSymbolTable.h"

using namespace llvm;

namespace fir {

typedef void (*LibFunc)(Module*);

class llcg_llvm : public llcg
{
public:
	llcg_llvm();
	virtual ~llcg_llvm();

	virtual LValue FuncType(FunctionModel* fmodel); // 返回FunctionType
	virtual LValue FuncType(LValue ret_type, vector<LValue>& types, bool isNotSure = false);
	virtual LValue GetOrInsertFunction(FunctionModel* fmodel); // 返回Function
	virtual LValue GetOrInsertFunction(const string& name, LValue func_type);
	virtual LValue GetOrInsertFunction(const string& name, LValue ret_type, vector<LValue>& types, bool isNotSure = false);
	virtual void   FunctionBodyBegin(LValue func, vector<string>& name_list); // 设置当前BasicBlock
	virtual void   FunctionBodyEnd(); // 处理函数结束
	virtual LValue getFunction(const string& name); // 从当前模块中获取一个函数
	virtual LValue Call(FunctionModel* fmodel, vector<LValue>& args); // 返回CallInst
	virtual LValue Call(LValue func, vector<LValue>& args);
	virtual LValue Struct(StructModel* smodel); // 返回StructType
	virtual LValue Struct(LValue _struct, vector<LValue>& types);
	virtual LValue DeclareStruct(const string& name);
	virtual LValue DefVar(LValue var_type, const string& name); // 返回分配的地址
	virtual LValue DefVar(LValue var_type, const string& name, LValue init);
	virtual LValue DefGlobalVar(LValue var_type, const string& name);
	virtual LValue DefGlobalVar(LValue var_type, const string& name, LValue init);
	virtual LValue Load(LValue var_addr);
	virtual LValue Store(LValue var_addr, LValue value);
	virtual LValue Opt1(const string& opt, LValue value);
	virtual LValue Opt2(const string& opt, LValue value1, LValue value2);
	virtual LValue Cmp(const string& opt, LValue value1, LValue value2);
	virtual LValue Assignment(const string& opt, LValue value1, LValue value2);
	virtual LValue Dot(LValue value, int num);
	virtual LValue Select(LValue value, vector<LValue>& args);
	virtual void   If(LValue cond, LValue father, LValue true_block, LValue true_block_end,
					   LValue false_block, LValue false_block_end, bool isElseWork);
	virtual void   For(LValue cond, LValue init, LValue pd, LValue work, LValue statement, LValue statement_end, LValue end);
	virtual void   While(LValue cond, LValue father, LValue pd, LValue statement, LValue statement_end, LValue end);
	virtual void   DoWhile(LValue statement, LValue pd);
	virtual void   DoUntil(LValue statement, LValue pd);
	virtual void   Goto(LValue target);
	virtual LValue New(LValue var_type, vector<LValue>& args, const string& funcname = "");
	virtual LValue NewArray(LValue var_type, vector<LValue>& wd, const string& funcname = "");
	virtual LValue Delete(LValue pointer, const string& funcname = "");
	virtual LValue DeleteArray(LValue pointer, const string& funcname = "");
	virtual LValue Return();
	virtual LValue Return(LValue var);

	virtual LValue Int8();
	virtual LValue Int16();
	virtual LValue Int32();
	virtual LValue Int64();
	virtual LValue Float();
	virtual LValue Double();
	virtual LValue Void();

	virtual LValue ConstString(const string& str);
	virtual LValue ConstInt(int num);
	virtual LValue ConstDouble(double num);

	virtual void   BeginModule(const string& name);
	virtual void   VerifyAndWrite(const string& outfile_name);
	virtual void   MakeMetaModule(const string& outfile_name, const string& module_name);

	virtual LValue GetNowBasicBlock();
	virtual LValue CreateBasicBlock();
	virtual LValue CreateBasicBlock(LValue func);

	virtual void MakeMetaList(vector<string>& list);
	virtual void MakeMetaList(const string& name, vector<string>& list, LValue fp);
	virtual void CloseTerminator(LValue basicblock, LValue target);
	virtual void SetNowBasicBlock(LValue nowBlock);

protected:

	// 当前的LLVM Module
	Module* M;
	// 模块元数据 Module
	Module* meta_M;

	LLVMContext context;
	Function* nowFunc;
	BasicBlock* nowBlock;

	void register_stdlib(Module* M, const LibFunc*);
	void register_metalib();
	void verifyModuleAndWrite(llvm::Module* M, const string& outfile_name);
	static Constant* geti8StrVal(Module& M, char const* str, Twine const& name);
	static Constant* getPtrArray(Module& M, vector<Constant*>& args_list);
	GetElementPtrInst* ptrMove(Value* v, int n);
	BasicBlock* createBlock();
	BasicBlock* createBlock(Function* f);

	FunctionType* getMallocType();
	FunctionType* getMallocArrayType();
	static FunctionType* malloc_type;
	static FunctionType* malloc_array_type;

};


}