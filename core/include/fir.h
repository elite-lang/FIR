//
// Created by sxf on 17-2-18.
//

#ifndef FIR_FIR_H
#define FIR_FIR_H

#include "Model/Node.h"

extern "C" {


extern Node* parseFile(const char* path);

extern struct FirVM* createVM();
extern void deleteVM(struct FirVM*);

extern bool loadNode(struct FirVM*, Node*);

extern bool loadFile(struct FirVM*, const char* path);

extern int runMain(struct FirVM*);


};

#endif //FIR_FIR_H
