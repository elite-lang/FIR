#pragma once

#include <string>
#include "Model/nodes.h"

namespace fir {

class ImportManager {

public:
    ImportManager();
    ~ImportManager();

    /** 
     * 核心的导入设置，在第一次最早的宏扫描的时候，就检测import，并记录在这里，会立即打开文件并解析缓存下来
     */
    bool addImport(std::string path, std::string import);

    /** 
     * 获取文件缓存的方法，如果有缓存，则从缓存中取出语法树，否则打开文件并解析
     */
    Node* getFile(std::string path);

    /** 
     * getFile的便捷方法，知道当前文件和相对import的目录，可以直接读取缓存
     */
    Node* getImport(std::string path, std::string import);

    /**
     * 获取lib入口点的方法，会查找第一个脚本运行位置下的fir_vendors目录
     */
    Node* getLibEntry(std::string name);

    /** 
     * 设置三个重要的库路径，如果不存在，则会提示warning，stdlib找不到会报错
     */
    void setVendersPath(std::string vender_path, std::string global_path, std::string stdlib_path);

private:
    std::string vender_path;
    std::string global_path;
    std::string stdlib_path;

};

}