/* 
* @Author: sxf
* @Date:   2015-12-24 08:56:30
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-24 08:58:15
*/

#pragma once
#include "Model/Node.h"
#include "LLCG/llcg.h"

namespace fir {

class CodeGenContext;

class ICodeGenFunction
{
public:
	virtual LValue call(CodeGenContext*, Node*) = 0;	
};


}