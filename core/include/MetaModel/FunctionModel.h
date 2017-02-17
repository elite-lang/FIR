/*
* @Author: sxf
* @Date:   2015-11-13 12:07:03
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-14 17:16:42
*/


#pragma once


#include "MetaModel.h"
#include <vector>
#include <string>

/**
 * @brief 函数模型元类型
 */
class FunctionModel : public MetaModel
{
public:
	FunctionModel(
		std::string& 			  name,
		std::string& 			  ret_type,
		std::vector<std::string>& type_list,
		std::vector<std::string>& name_list
	);

    /**
     * @brief 查找参数表的名字,找出参数是第几个传入的
     * @param name 待查参数名
     * @return 参数名的序号数,从0开始,-1表示不存在
     */
	int find(std::string& name);

    /**
     * @brief 设定简单成员函数的结构体名字,全局C函数不应调用该方法
     * @details 该方法会设置一个结构体名,在该函数名前添加"结构体名_"作为修饰
     *          并且会为函数自动添加一个this指针指向调用时的结构体
     *          请务必在genCode前,最好是刚刚构造好该对象时,就为其设置结构体名
     * @param name 要设置的所属结构体名
     */
	void setStructName(const string& name);

	LValue getFunction(CodeGenContext* context);
	LValue getFunctionType() { return func_type; }

	virtual void insertToST(CodeGenContext* context);
	virtual void genCode(CodeGenContext* context);
	virtual void genMetaCode(CodeGenContext* context);
	virtual MetaType getMetaType();

	std::string return_type;
	std::vector<std::string> type_list;
	std::vector<std::string> name_list;
	std::string struct_name;
private:
    LValue func_type;
};


