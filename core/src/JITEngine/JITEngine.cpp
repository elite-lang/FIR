
#include "JITEngine/JITEngine.h"
#include <string>
#include <iostream>
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"
#include <llvm/Support/MemoryBuffer.h>
#include "llvm/Support/raw_ostream.h"
#include <llvm/Support/DynamicLibrary.h>
#include "llvm/Support/Debug.h"


using namespace llvm;
using namespace std;

namespace fir {

class JITEngine_private
{
public:
    JITEngine_private() {
        InitializeNativeTarget();
        InitializeNativeTargetAsmPrinter();
        InitializeNativeTargetAsmParser();
    }
    ~JITEngine_private() {
        delete EE;
        delete RTDyldMM;
    }
    LLVMContext context;
    ExecutionEngine* EE = NULL;
    RTDyldMemoryManager* RTDyldMM = NULL;

    void addModule(std::unique_ptr<Module> Owner) {
        string ErrStr;
        if (EE == NULL) {
            RTDyldMM = new SectionMemoryManager();
            EE = EngineBuilder(std::move(Owner))
                .setEngineKind(EngineKind::JIT)
                .setErrorStr(&ErrStr)
                .setVerifyModules(false)
                .setMCJITMemoryManager(std::unique_ptr<RTDyldMemoryManager>(RTDyldMM))
                .setOptLevel(CodeGenOpt::Default)
                .create();
        } else
            EE->addModule(std::move(Owner));
        if (ErrStr.length() != 0)
            cerr << "Create Engine Error" << endl << ErrStr << endl;
        EE->finalizeObject();
    }

    GenericValue runFunction(std::string name, ArrayRef< GenericValue > ArgValues) {
        return EE->runFunction(EE->FindFunctionNamed(name.c_str()), ArgValues);
    }

    int runMain(const std::vector< std::string > &argv, const char *const *envp) {
        EE->runStaticConstructorsDestructors(false);
        int ans = EE->runFunctionAsMain(EE->FindFunctionNamed("main"), argv, envp);
        EE->runStaticConstructorsDestructors(true);
        return ans;
    }

};

JITEngine::JITEngine() {
    priv = new JITEngine_private();
}


JITEngine::~JITEngine() {
    delete priv;
}


}
