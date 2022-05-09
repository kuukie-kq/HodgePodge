#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstring>
using namespace std;

namespace cip {
    //Content 目录 (line number) ~ (+35) ~ (line number)  [[maybe_unused]] Clang-Tidy
    //链接  目录末尾位置
    class [[maybe_unused]] tag_one;
    //类型定义
    typedef unsigned int u4_int; //32位 4*8
    typedef unsigned char u1_int;//8位 1*8
    //未在目录中定义的类型
    //链接  类型定义
    class [[maybe_unused]] tag_two;

    //题目要求的最大容量
    #define MAX 100

    //自定义集合类型，用于CPU中不同的功能支持
    class Array;//数组 用于寄存器对应的内存
    class ListArray;//u4数组 用于字节码存储
    class LinkedNode;//链表节点 用于链表的使用
    class LinkedList;//链表 用于保存寄存器使用情况方便输出
    class CodingNode;//树节点 用于编码树的使用
    class CodingTree;//编码树 用于与操作函数绑定
    //以下为测试部分
    class MapNode;
    class [[maybe_unused]] HashMap;
    //主类
    class CounterStep;//CPU解释器核心
    //次要类
    class Time;//用于计时
    //主函数
    [[maybe_unused]] int main_c_inter();//相当于main.cpp中main
    //未在目录中的函数定义
    //链接  操作函数定义
    class [[maybe_unused]] tag_three;
    //链接  使用vector作为字符串分割
    class [[maybe_unused]] tag_four;
    //目录末尾
    class [[maybe_unused]] tag_one{};

    //Array .h .cpp
    //Array .h
    class Array {
    private:
        int array[MAX]{};
    public:
        Array();
        void exchange(int index, int value);//数组对应的值替换
        int* array_index(int index);//获取数组对应位置的地址
        int get(int index) const;//获取对应位置的值
    };

    //Array .cpp
    Array::Array() {
        for (int &i : array) {
            i = -2147483648;
        }
    }

    void Array::exchange(const int index,const int value) {
        array[index] = value;
    }

    int* Array::array_index(const int index) {
        return &array[index];
    }

    int Array::get(const int index) const {
        return array[index];
    }

    //ListArray .h .cpp
    //ListArray .h
    class ListArray {
    private:
        int size;//数组大小
        u4_int array[MAX]{};
    public:
        ListArray();
        void append(u4_int value);//添加指令字节码
        u4_int get(int index_positive) const;//获取对应位字节码  有空行bug？
    };

    //ListArray .cpp
    ListArray::ListArray() {
        size = 0;
        for (u4_int &i : array) {
            i = 0;
        }
    }

    void ListArray::append(const u4_int value) {
        if (size < 100 && size >= 0) {
            size++;
            array[size - 1] = value;
        } else {
            cerr << "append " << size << " error of " << value << endl;
        }
    }

    u4_int ListArray::get(const int index_positive) const {
        return array[index_positive - 1];
    }

    //LinkedNode .h .cpp
    //LinkedNode .h
    class LinkedNode {
    private:
    public:
        int *value;
        string name;
        LinkedNode *next;
        LinkedNode();
        ~LinkedNode();
    };

    //LinkedNode .cpp
    LinkedNode::LinkedNode() {
        value = nullptr;
        name = "head";
        next = nullptr;
    }

    LinkedNode::~LinkedNode() {
        delete next;
    }

    //LinkedList .h .cpp
    //LinkedList .h
    class LinkedList {
    private:
        LinkedNode *head;//链表头 占一个空间 用于结果输出
        bool exist(const string& name) const;//寄存器是否已经存在
    public:
        LinkedList();
        ~LinkedList();
        void insert(int *value, const string& name) const;//插入数据
        void display() const;//打印链表 一个一行
    };

    //LinkedList .cpp
    bool LinkedList::exist(const string& name) const {
        for (LinkedNode *node = head->next; node != nullptr; node = node->next) {
            if (node->name == name) {
                return true;
            }
        }
        return false;
    }

    LinkedList::LinkedList() {
        head = new LinkedNode();
    }

    LinkedList::~LinkedList() {
        delete head;
    }

    void LinkedList::insert(int*const value, const string& name) const {
        if (!exist(name)) {
            LinkedNode* node = head;
            for (; node->next != nullptr; node = node->next) {}
            node->next = new LinkedNode();
            node->next->value = value;
            node->next->name = name;
        }
    }

    void LinkedList::display() const {
        for (LinkedNode* node = head->next; node != nullptr; node = node->next) {
            cout << node->name << "\t" << *node->value << endl;
        }
    }

    //CodingNode .h .cpp
    //CodingNode .h
    class CodingNode {
    public:
        void (*function)(int &cs, u4_int ip, Array *csr);
        CodingNode *left;
        CodingNode *right;
        CodingNode();
        ~CodingNode();
    };

    //CodingNode .cpp
    CodingNode::CodingNode() {
        function = nullptr;
        left = nullptr;
        right = nullptr;
    }

    CodingNode::~CodingNode() {
        delete right;
        delete left;
    }

    //CodingTree .h .cpp
    //CodingTree .h

    //类型定义
    class [[maybe_unused]] tag_two{};
    using OP = void (*)(int &cs, u4_int ip, Array *csr);//函数指针类型

    //函数操作定义
    class [[maybe_unused]] tag_three{};
    void mov(int &cs, u4_int ip, Array *csr);//mov指令
    void inc(int &cs, u4_int ip, Array *csr);//inc指令
    void dec(int &cs, u4_int ip, Array *csr);//dec指令
    void jnz(int &cs, u4_int ip, Array *csr);//jnz指令

    class CodingTree {
    private:
        CodingNode *base;
        void generation(u1_int code, void (*fun)(int &cs, u4_int ip, Array *csr));//将定义的汇编指令与操作函数绑定到树结构中
        static bool bit_one(u1_int code, int index);//对应index的位置是否为1
    public:
        CodingTree();
        ~CodingTree();
        OP found(u4_int ip) const;//根据字节码获取到对应处理函数
    };

    //CodingTree .cpp
    void mov(int& cs, const u4_int ip, Array* csr) {
        u4_int first = ip >> 24u;
        u4_int second = (ip << 8u) >> 24u;
        u4_int third = (ip << 16u) >> 16u;
        if (first != 4) {
            cerr << "ip option error mov:" << ip << endl;
            return;
        }
        if (third > 1u << 15u) {
            third = third >> 8u;
            csr->exchange((int) (second) - 129, csr->get((int) (third) - 129));
        } else {
            csr->exchange((int) (second) - 129, (int) third - 10000);
        }
        cs++;
    }

    void inc(int &cs, const u4_int ip, Array *csr) {
        u4_int first = ip >> 24u;
        u4_int second = (ip << 8u) >> 24u;
        if (first != 5) {
            cout << "ip option error inc:" << ip << endl;
            return;
        }
        csr->exchange((int) (second) - 129, csr->get((int) (second) - 129) + 1);
        cs++;
    }

    void dec(int &cs, const u4_int ip, Array *csr) {
        u4_int first = ip >> 24u;
        u4_int second = (ip << 8u) >> 24u;
        if (first != 6) {
            cout << "ip option error dec:" << ip << endl;
            return;
        }
        csr->exchange((int) (second) - 129, csr->get((int) (second) - 129) - 1);
        cs++;
    }

    void jnz(int &cs, const u4_int ip, Array *csr) {
        u4_int first = ip >> 24u;
        u4_int second = (ip << 8u) >> 24u;
        u4_int third = (ip << 16u) >> 16u;
        if (first != 7) {
            cout << "ip option error jnz:" << ip << endl;
            return;
        }
        if (csr->get((int) (second) - 129) == 0) {
            cs++;
        } else {
            cs = cs + ((int) third - 10000);
        }
    }

    void CodingTree::generation(u1_int code, void (*fun)(int &, u4_int, Array *)) {
        code = code - 4;
        CodingNode *node = base;
        for (int i = 2; i > 0; i--) {
            if (bit_one(code, i)) {
                if (node->right == nullptr) {
                    node->right = new CodingNode();
                }
                node = node->right;
            } else {
                if (node->left == nullptr) {
                    node->left = new CodingNode();
                }
                node = node->left;
            }
        }
        node->function = fun;
    }

    bool CodingTree::bit_one(const u1_int code, const int index) {
        return code & (1u << (u4_int)(index - 1));
    }

    CodingTree::CodingTree() {
        base = new CodingNode();
        generation(4, mov);
        generation(5, inc);
        generation(6, dec);
        generation(7, jnz);
    }

    CodingTree::~CodingTree() {
        delete base;
    }

    OP CodingTree::found(const u4_int ip) const {
        u4_int first = (ip << 6u) >> 30u;
        CodingNode *node = base;
        for (int i = 2; i > 0; i--) {
            if (bit_one(first, i)) {
                node = node->right;
            } else {
                node = node->left;
            }
            if (node == nullptr) {
                cerr << "tree found error" << endl;
                return nullptr;
            }
        }
        return node->function;
    }

    //test unused
    class MapNode {
    public:
        int value;
        char* key;
        MapNode* next;
        MapNode();
        ~MapNode();
    };

    MapNode::MapNode() {
        value = 0;
        key = nullptr;
        next = nullptr;
    }

    MapNode::~MapNode() {
        delete next;
        delete key;
    }

    class [[maybe_unused]] HashMap {
    private:
        const static int size = 128;
        MapNode* map[size]{};
        static u4_int hash(char* str);
    public:
        HashMap();
        ~HashMap();
        [[maybe_unused]] void insert(char* key,int value);
        [[maybe_unused]] void remove(char* key);
        [[maybe_unused]] int get(char* key);
    };

    u4_int HashMap::hash(char* str) {
        u4_int h;
        u1_int *p;
        for(h=0,p=(u1_int*)str;*p;p++) {
            h = 31 * h + *p;
        }
        return h;
    }

    HashMap::HashMap() {
        for(auto& i : map) {
            i = nullptr;
        }
    }

    HashMap::~HashMap() {
        for(auto& i : map) {
            delete i;
        }
    }

    [[maybe_unused]] void HashMap::insert(char* key,int value) {
        u4_int h = hash(key);
        if(map[(int)h % size] == nullptr) {
            map[(int)h % size] = new MapNode();
            map[(int)h % size]->value = value;
            strcpy(map[(int)h % size]->key,key);
        } else {
            cerr << "hash insert error" << endl;
        }
    }

    [[maybe_unused]] void HashMap::remove(char* key) {
        u4_int h = hash(key);
        if(map[(int)h % size]->next == nullptr) {
            delete map[(int) h % size];
            map[(int) h % size] = nullptr;
        } else {
            cerr << "hash remove error" << endl;
        }
    }

    [[maybe_unused]] int HashMap::get(char* key) {
        u4_int h = hash(key);
        if(map[(int)h % size] == nullptr) {
            cerr << "hash get error the key maybe no insert" << endl;
            return 0;
        } else if(map[(int)h % size]->next == nullptr) {
            return map[(int)h % size]->value;
        } else {
            cerr << "hash get error" << endl;
            return 0;
        }
    }

    //CounterStep .h .cpp
    //CounterStep .h
    //字符串分割
    class [[maybe_unused]] tag_four{};
    vector<string> split(string str, const string& pattern);//字符串分割

    class CounterStep {
    private:
        int pc;//计数器
        int cs;//寻址
        Array *csr;//寄存器
        ListArray *ir;//指令
        CodingTree *ins;//编码树
        LinkedList *linked;//寄存器使用
        u4_int calculate(int index, const string& word);//解析对应位置的字节码
        int constant(const string& reg);//固定字符对应数
    public:
        CounterStep();
        ~CounterStep();
        void read(const char *filename);//输入
        int step();//写死的4种处理操作
        int step_point();//使用函数指针处理操作
        void result();//输出
    };

    //CounterStep .cpp
    vector<string> split(string str, const string& pattern) {
        string::size_type pos;
        vector<string> result;
        str += pattern;  //扩展字符串以方便操作
        unsigned int size = str.size();
        for (unsigned int i = 0; i < size; i++) {
            pos = str.find(pattern, i);
            if (pos < size) {
                string s = str.substr(i, pos - i);
                result.push_back(s);
                i = pos + pattern.size() - 1;
            }
        }
        return result;
    }

    u4_int CounterStep::calculate(int index, const string& word) {
        if (constant(word) == 0 && index == 2) {
            int number = stoi(word);
            if (number >= -10000 && number <= 10000) {
                u4_int result = number + 10000;
                return result;
            } else {
                cerr << "read file of " << index << word << " error" << endl;
                return 1u << 15u;
            }
        } else {
            u4_int result = constant(word);
            if (index == 0) {
                return result << 24u;
            } else if (index == 1) {
                return result << 16u;
            } else {
                return result << 8u;
            }
        }
    }

    int CounterStep::constant(const string& reg) {
        string sta[104] = {
                "mov", "inc", "dec", "jnz",
                "ax", "bx", "cx", "dx", "ex", "fx", "gx", "hx", "ix", "jx",
                "bax", "bbx", "bcx", "bdx", "bex", "bfx", "bgx", "bhx", "bix", "bjx",
                "cax", "cbx", "ccx", "cdx", "cex", "cfx", "cgx", "chx", "cix", "cjx",
                "dax", "dbx", "dcx", "ddx", "dex", "dfx", "dgx", "dhx", "dix", "djx",
                "eax", "ebx", "ecx", "edx", "eex", "efx", "egx", "ehx", "eix", "ejx",
                "fax", "fbx", "fcx", "fdx", "fex", "ffx", "fgx", "fhx", "fix", "fjx",
                "gax", "gbx", "gcx", "gdx", "gex", "gfx", "ggx", "ghx", "gix", "gjx",
                "hax", "hbx", "hcx", "hdx", "hex", "hfx", "hgx", "hhx", "hix", "hjx",
                "iax", "ibx", "icx", "idx", "iex", "ifx", "igx", "ihx", "iix", "ijx",
                "jax", "jbx", "jcx", "jdx", "jex", "jfx", "jgx", "jhx", "jix", "jjx"
        };
        int stb[104] = {
                4, 5, 6, 7,
                129, 130, 131, 132, 133, 134, 135, 136, 137, 138,
                139, 140, 141, 142, 143, 144, 145, 146, 147, 148,
                149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
                159, 160, 161, 162, 163, 164, 165, 166, 167, 168,
                169, 170, 171, 172, 173, 174, 175, 176, 177, 178,
                179, 180, 181, 182, 183, 184, 185, 186, 187, 188,
                189, 190, 191, 192, 193, 194, 195, 196, 197, 198,
                199, 200, 201, 202, 203, 204, 205, 206, 207, 208,
                209, 210, 211, 212, 213, 214, 215, 216, 217, 218,
                219, 220, 221, 222, 223, 224, 225, 226, 227, 228,
        };
        for (int i = 0; i < 104; i++) {
            if (reg == sta[i]) {
                if (i > 3) {
                    linked->insert(csr->array_index(i - 4), reg);
                }
                return stb[i];
            }
        }
        return 0;
    }

    CounterStep::CounterStep() {
        pc = 0;
        cs = 1;
        csr = new Array();
        ir = new ListArray();
        ins = new CodingTree();
        linked = new LinkedList();
    }

    CounterStep::~CounterStep() {
        delete linked;
        delete ins;
        delete ir;
        delete csr;
    }

    void CounterStep::read(const char *filename) {
        ifstream infile(filename, ios::in);
        for (string line; getline(infile, line);) {
            vector<string> words;
            words = split(line, " ");
            u4_int bytecode = 0;
            for (int j = 0; j < words.size(); j++) {
                bytecode = bytecode + calculate(j, words[j]);
            }
            ir->append(bytecode);
        }
    }

    int CounterStep::step() {
        if (pc <= 1000000000 && pc >= 0) {
            pc++;
            u4_int ip = ir->get(cs);
            u4_int first = ip >> 24u;
            u4_int second = (ip << 8u) >> 24u;
            u4_int third = (ip << 16u) >> 16u;
            if (first == 4) {
                if (third > 1u << 15u) {
                    third = third >> 8u;
                    csr->exchange((int) (second) - 129, csr->get((int) (third) - 129));
                } else {
                    csr->exchange((int) (second) - 129, (int) third - 10000);
                }
                cs++;
            } else if (first == 5) {
                csr->exchange((int) (second) - 129, csr->get((int) (second) - 129) + 1);
                cs++;
            } else if (first == 6) {
                csr->exchange((int) (second) - 129, csr->get((int) (second) - 129) - 1);
                cs++;
            } else if (first == 7) {
                if (csr->get((int) (second) - 129) == 0) {
                    cs++;
                } else {
                    cs = cs + ((int) third - 10000);
                }
            } else {
                cout << "the end pc=" << pc << endl;
                return 0;
            }
            return 1;
        } else {
            cerr << "error pc=" << pc << endl;
            return 0;
        }
    }

    int CounterStep::step_point() {
        if (pc <= 1000000000 && pc >= 0) {
            pc++;
            u4_int ip = ir->get(cs);
            if (ip == 0) {
                cout << "the end pc=" << pc << endl;
                return 0;
            }
            OP fun = ins->found(ip);
            fun(cs, ip, csr);
            return 1;
        } else {
            cerr << "error pc=" << pc << endl;
            return 0;
        }
    }

    void CounterStep::result() {
        linked->display();
    }

    //Time .h .cpp
    //Time .h .cpp-x
    class Time {
    private:
        chrono::nanoseconds start{};
    public:
        Time() {
            start = chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch());
        }

        void timeline() {
            chrono::nanoseconds end = chrono::duration_cast<chrono::nanoseconds>(
                    chrono::system_clock::now().time_since_epoch());
            cout << "time:" << end.count() - start.count() << "ns" << endl;
        }
    };

    //main .cpp
    [[maybe_unused]] int main_c_inter() {
        auto *t = new Time();
        auto *counter = new CounterStep();
        counter->read("../com/help/test.txt");
        for (;;) {
            if (
                    #define POINT
                    #ifdef POINT
                    counter->step_point() == 0
                    #else
                    counter->step() == 0
                    #endif
                    ) {
                break;
            }
        }
        counter->result();
        t->timeline();
        delete counter;
        delete t;
        return 0;
    }

    //help
    //思路:
    //
    //   0000 0000 0000 0000 0000 0000 0000 0000 32位   u4_int
    //   指令 4种  参数一 寄存器 100种  参数二 寄存器或立即数 100+20001种
    //   指令：00--mov 01--inc 10--dec 11--jnz 2位
    //   寄存器：2^7 = 128      1000 0000   8位
    //   数：2^15 = 32768      0000 0000 0000 0000 16位
    //   0000 0100 0000 0000 0000 0000 0000 0000 32位
    //         ↑固定位        ↑位为1则表示后面7位为寄存器 0 表示后15位为立即数(true number+10000)
    //
    //
    //两种执行方式
    //    一种写死的四种指令操作 时间≈1000000000ns = 1s  -- step()
    //    另一种可以添加指令操作 时间≈2000000000ns = 2s  -- step_point()
    //    ↑使用的是函数指针的方式
    //
    //   test.txt为测试输入汇编代码
    ////
    //mov bx 2
    //mov ax 5
    //inc bx
    //dec ax
    //jnz ax -2
    //dec ax
    ////
    //mov ax 10000
    //mov bx ax
    //dec bx
    //jnz bx -1
    //dec ax
    //jnz ax -4
    ////

    //warring debug
    //对于位操作必须使用无符号数 既使用number+u或(u4_int)(unsigned int)
    //对于未使用的使用[[maybe_unused]]修饰 变量后 函数名前 类前
    //对于未使用成员变量的函数提示maybe static使用一个[[maybe_unused]]的成员变量即可或者使用static
}

