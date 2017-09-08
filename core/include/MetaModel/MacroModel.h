/*
* @Author: sxf
* @Date:   2015-11-25 15:01:05
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-21 16:52:50
*/


#pragma once

#include "Model/Node.h"
#include "MetaModel.h"

namespace fir {

/**
 * @brief 宏模型元类型
 */
class MacroModel : public MetaModel
{
public:
	MacroModel(const std::string& name, Node* node);
	~MacroModel();

	virtual void insertToST(CodeGenContext* context);
	virtual void genCode(CodeGenContext* context);
	virtual void genMetaCode(CodeGenContext* context);
	virtual MetaType getMetaType();

	Node* getData() { return node; }
private:
	Node* node;
};


}