//
// Created by sxf on 17-2-18.
//

#include "fir.h"
#include <fstream>
#include "module.h"
#include "Model/Node.h"

extern "C" {

fir::Node* parseFile(const char* path) {
    FILE* file_in;
    if ((file_in = fopen(path, "r")) == NULL) {
        printf("找不到程序源文件: %s\n", path);
        return 0;
    }

    module mod = { file_in, nullptr };
    parse_module(&mod);
    fclose(file_in);
    // 打印语法树
    printf("源文件 - %s\n", path);
    mod.root->print(0);
    return mod.root;
}


struct FirVM {
    
};

struct FirVM* createVM() {
    return new FirVM();
}

void deleteVM(struct FirVM* vm) {
    delete vm;
}

bool loadNode(struct FirVM* vm, fir::Node* node) {
    
}

bool loadFile(struct FirVM* vm, const char* path) {

}

int runMain(struct FirVM* vm) {

}
















};