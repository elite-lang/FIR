//
// Created by sxf on 17-2-18.
//

#include "fir.h"
#include <fstream>
#include "module.h"

extern "C" {

Node* parseFile(const char* path) {
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



















};