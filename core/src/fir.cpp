//
// Created by sxf on 17-2-18.
//

#include "fir.h"
#include <fstream>
#include "module.h"
#include "Model/Node.h"
#include "RedCodeGen.h"

using namespace fir;

extern "C" {

fir::Node* firParseFile(const char* path) {
    FILE* file_in;
    if ((file_in = fopen(path, "r")) == NULL) {
        printf("找不到程序源文件: %s\n", path);
        return 0;
    }

    module mod = {file_in, nullptr};
    parse_module(&mod);
    fclose(file_in);
    // 打印语法树
    printf("源文件 - %s\n", path);
    mod.root->print(0);
    return mod.root;
}

fir::Node* firParseString(const char* string) {
    module mod = {nullptr, string};
    printf("源文件 - %s\n", string);
    parse_module(&mod);
    // 打印语法树
    mod.root->print(0);
    return mod.root;
}


struct FirVM {
    CodeGen *codegen;
};

struct FirVM* createFirVM() {
    FirVM *vm = new FirVM();
    vm->codegen = RedCodeGen::Create();
    return vm;
}

void deleteFirVM(struct FirVM* vm) {
    delete vm;
}

bool firLoadNode(struct FirVM* vm, fir::Node* node, const char* output_name) {        
    vm->codegen->Init();
    vm->codegen->PreScan(node);
    vm->codegen->Make(node, output_name, "main");
    vm->codegen->MakeMeta("meta.bc", "meta");
    return false;
}

bool firLoadFile(struct FirVM* vm, const char* path) {
    fir::Node *node = firParseFile(path);
    return firLoadNode(vm, node, "");
}

bool firLoadString(struct FirVM *vm, const char *string)
{
    fir::Node *node = firParseString(string);
    return firLoadNode(vm, node, "");
}

int firRunMain(struct FirVM* vm) {
    return 0;
}
















};