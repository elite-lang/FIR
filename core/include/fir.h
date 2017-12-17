//
// Created by sxf on 17-2-18.
//

#ifndef FIR_FIR_H
#define FIR_FIR_H

#include "Model/nodes.h"
extern "C" {

extern fir::Node* firParseFile(const char* path);
extern fir::Node* firParseString(const char *string);

extern struct FirVM* createFirVM();
extern void deleteFirVM(struct FirVM*);

extern bool firLoadNode(struct FirVM*, fir::Node*, const char* output_name);

extern bool firLoadFile(struct FirVM*, const char* path);
extern bool firLoadString(struct FirVM *, const char *path);

extern int firRunMain(struct FirVM *);
};

#endif //FIR_FIR_H
