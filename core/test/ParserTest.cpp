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
#include "RedCodeGen.h"
// #include "fir.h"
using namespace std;


TEST(ParserTest, Construction)
{
    // CodeGen* codegen = RedCodeGen::Create();
}

// TEST(ParserTest, TestParse)
// {
//     // FirVM* vm = createFirVM();
//     // firLoadString(vm, "// normal function\nvoid Hello() {\nprintf(\"Hello\")\n}");
// }
