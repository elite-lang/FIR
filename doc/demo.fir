import 'stdlib' // = import all items to local env
import map, map_call from 'map' // import some part to local env
let x = import 'nfunc'

def for_demo(int x, string y) {
    for (int i = 0; i < 10; ++i) { // 标准C循环

    }

    for (int i in array) {   // 独立类型array 和 object, 这是两个不同的类型
        array[i]
    }

    for (string k in map) {  // 独立类型string, string可以转换为array, 可以直接当char*传入C代码
        array[k]
    }

    for (let item of array) {
        item
    }

    for (let key, value in array) {  // 同时关注key, value
    }

    for (let key, value of array) {  // 功能同上
    }

    for (int i in 10) { // 单个数字在for语句中, 自动生成区间迭代器

    }

    for (int i in [0, 10)) { // 区间自动调用区间迭代器

    }
}


def if_demo(v) {
    if (stat != x) { // 基本if-else

    } else {

    }

    let x = if (stat == x) "yes" else "no" // if语句会自动返回值

    if (stat)  // 单独一个语句
        call(x)
    else
        call(y)

}


def func(int a, string b = '')  // 支持默认值
def func(int a, string b, string c) // 支持重载
def func(int a, string b, c...) // 支持不定参数, 函数匹配顺序和定义顺序相同

def call_demo() {
    func(12, 'hello') // 基本调用
    func(12, 'world', '!') // 重载调用
    func(a=12, b='hello') // 名称传值
}


def object_define() {
    return {
        hello: "hello world"
    }
}

def string_different() {
    let a = 'ok\n'  // 不转义型
    let b = "ok\n"  // 常用转义型
    let c = `p$a`   // 模板型
    print(a)  // output: ok\n
    print(b)  // output: ok换行
    print(c)  // output: hello pok\n
}


// basic type:

int x, double d, string s, array arr, object o, function f
