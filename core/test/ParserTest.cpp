/*
* @Author: sxf
* @Date:   2015-12-16 12:02:18
* @Last Modified by:   sxf
* @Last Modified time: 2016-05-10 16:30:40
*/
#ifdef __APPLE__
#define GTEST_HAS_POSIX_RE 0
#endif

#include <gtest/gtest.h>
#include <string>
#include "Model/nodes.h"
#include "RedCodeGen.h"
#include "cmdline.h"
#include "fir.h"
using namespace std;

#define __PARSER_TEST__(name) TEST(ParserTest_##name, name)

__PARSER_TEST__(Construction)
{
    CodeGen* codegen = RedCodeGen::Create();
}

__PARSER_TEST__(TestPrasing)
{
    CodeGen* codegen = RedCodeGen::Create();
    
    Node* ans = parseFile("test.fir");
    codegen->Init();
    codegen->PreScan(ans);
    codegen->Make(ans, "test.bc", "main");
    codegen->MakeMeta("meta.bc", "meta");
    delete codegen;
}
