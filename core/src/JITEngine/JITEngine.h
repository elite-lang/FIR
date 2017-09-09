#pragma once

namespace fir {

class JITEngine_private;


/**
 * @brief JIT引擎基础类
 * @details 这里调用了LLVM的JIT引擎，可以执行任意一个语义分析后的Module
 *          JIT引擎负责将LLVM代码转换成本地机代码，不进行任何缓存操作，Module的缓存需要在本类外部实现
 *          在某些不支持的CPU平台下，JIT引擎有可能失效，并退化为一般的解释型引擎
 */
class JITEngine {
public:
    JITEngine();
    virtual ~JITEngine();
private:
    JITEngine_private* priv;
};

}