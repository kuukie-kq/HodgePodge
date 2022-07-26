//
// Created by kuu*kie on 2022/7/22.
//

#ifndef VIRTUAL_CPU_H
#define VIRTUAL_CPU_H

#pragma once

// notice
// 注意，切忌在自定义的命名空间中引用系统头文件，避免造成标识符的混乱。
// 存在多层namespace的情况，里层namespace对于系统namespace中的函数错乱，找不到的情况
#include <iostream> //输入输出
#include <string> //字符串类
#include <vector> //不定数组，字符串分割
#include <fstream> //读写文件

namespace kuu {
    //考虑使用匿名命名空间，只在本文件内可见
    namespace cpu {
        //.h文件部分
        class [[maybe_unused]] tagscccc;//定义部分
        //类型定义
        //统一类型，只有所占字节大小不同，都按整数类型进行处理
        typedef unsigned long u8int;
        typedef unsigned int u4int;
        typedef unsigned short u2int;
        typedef unsigned char u1int;
        typedef long s8int;
        typedef int s4int;
        typedef short s2int;
        typedef char s1int;
        //工具函数，计算hash值和字符串的分割
        u4int hash_code(const char* key);
        std::vector<std::string> spilt(std::string str, const std::string& pattern);
        //成员类
        // 说明
        // 内存地址大小 1 16 16 16 16 16 16 16 16 32 32 32 32 64 64 128 511
        // 总共1024，每个可以存放32位数据
        // 使用方法
        // 内存先申请，再使用，用完释放
        // 并且对于read不做限制，释放也只是设置使用大小为0，内容不变
        class virtual_memory;
        // 说明
        // 函数调用栈
        // 目前无限制，加个size限制栈大小
        // 使用方法
        // 压栈弹栈，函数名采用hash存储
        class function_stack;
        // 说明
        // 寄存器组
        // ax bx cx dx e1x e2x e3x e4x e5x e6x e7x e8x e9x rx fx
        // 对应数组顺序，考虑到hashmap也是使用数组实现的
        // 不对应需加一个键值对映射，键为寄存器名值为index
        // 使用方法
        // 从寄存器中取值和存值
        class virtual_register;
        // 说明
        // 编码树，统一存放指令对应函数的树
        // 与二进制指令相对应，0左1右
        // 使用方法
        // 绑定函数以及查找函数，其中有位运算，用于计算二进制对应位置的值
        class coding_tree;
        //主类
        // 说明
        // 主类，CPU解释器的执行，模拟CPU按照机器码做出相应动作
        // 使用方法
        // 先读取，读取汇编翻译成机器码，后面的CPU调度树，通过读取切换，既内容逻辑复杂
        // 然后按步骤执行，pc计数器用于记录总共执行了多少个机器码
        // 结果输出，相当于测试用例仅用于查看一些成员对象中的数据是否符合预期
        class counter_step;
        //指令对应的函数
        using function = s4int (*)(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int mov(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int inc(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int dec(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int jnz(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int jny(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int cal(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int ret(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        // end 七进制分别为C，D，E，F，G(7)，A，B，标识7s
        class [[maybe_unused]] tagscccc {};




        //.cpp文件部分
        class [[maybe_unused]] tagscccd;//实现部分
        u4int hash_code(const char* key) {
            register u4int result;
            register u1int* byte;
            for (result = 0, byte = (u1int*)key; *byte; byte++) {
                result = result * 31 + *byte;
            }
            return result;
        }

        std::vector<std::string> spilt(std::string str, const std::string& pattern) {
            std::string::size_type pos;
            std::vector<std::string> result;
            str += pattern;  //扩展字符串以方便操作
            u4int size = str.size();
            for (u4int i = 0; i < size; i++) {
                pos = str.find(pattern, i);
                if (pos < size) {
                    std::string s = str.substr(i, pos - i);
                    result.push_back(s);
                    i = pos + pattern.size() - 1;
                }
            }
            return result;
        }

        class virtual_memory {
        private:
            u1int use[16];
            u2int index[16];
            u4int memory[1024];
        public:
            virtual_memory();
            ~virtual_memory();
            u4int apply(u4int size);
            s4int release(u4int segment);
            void overlay(u4int segment, u4int offset, u4int value);
            u4int read(u4int segment, u4int offset) const;
        };

        virtual_memory::virtual_memory() {
            for(u1int& i : use) {
                i = 0;
            }
            index[0] = 1;
            index[1] = 17;
            index[2] = 33;
            index[3] = 49;
            index[4] = 65;
            index[5] = 81;
            index[6] = 97;
            index[7] = 113;
            index[8] = 129;
            index[9] = 161;
            index[10] = 193;
            index[11] = 225;
            index[12] = 257;
            index[13] = 321;
            index[14] = 385;
            index[15] = 513;
            for (u4int& i : memory) {
                i = 0u;
            }
            // magic number
            memory[0] = 3260681415u;
        }

        virtual_memory::~virtual_memory() {
            for(u1int& i : use) {
                i = 0;
            }
        }

        u4int virtual_memory::apply(const u4int size) {
            if (size <= 1u << 4u) {
                for (s4int i = 0; i < 8; i++) {
                    if (use[i] == 0) {
                        use[i] = size;
                        return index[i];
                    }
                }
                return index[15];
            } else if (size <= 1u << 5u) {
                for (s4int i = 0; i < 4; i++) {
                    if (use[8 + i] == 0) {
                        use[8 + i] = size;
                        return index[8 + i];
                    }
                }
                return index[15];
            } else if (size <= 1u << 6u) {
                for (s4int i = 0; i < 2; i++) {
                    if (use[12 + i] == 0) {
                        use[12 + i] = size;
                        return index[12 + i];
                    }
                }
                return index[15];
            } else if (size <= 1u << 7u) {
                if (use[14] == 0) {
                    use[14] = size;
                    return index[14];
                }
                return index[15];
            }
            return 0u;
        }

        s4int virtual_memory::release(const u4int segment) {
            for (s4int i = 0; i < 16; i++) {
                if (index[i] == segment) {
                    use[i] = 0;
                    return 1;
                }
            }
            return 0;
        }

        void virtual_memory::overlay(const u4int segment, const u4int offset, const u4int value) {
            for (s4int i = 0; i < 16; i++) {
                if (index[i] == segment) {
                    if (use[i] > offset) {
                        memory[segment + offset] = value;
                    }
                    break;
                }
            }
        }

        u4int virtual_memory::read(const u4int segment, const u4int offset) const {
            return memory[segment + offset];
        }

        class function_stack {
        private:
            class function_stack_node {
            public:
                u4int name;
                u4int segment;
                function_stack_node* next;
                function_stack_node();
                ~function_stack_node();
            };
            function_stack_node* main;
        public:
            function_stack();
            ~function_stack();
            void entrance(u4int segment) const;
            u4int exit() const;
        };

        function_stack::function_stack_node::function_stack_node() {
            name = hash_code("main");
            segment = 0;
            next = nullptr;
        }

        function_stack::function_stack_node::~function_stack_node() {
            delete next;
        }

        function_stack::function_stack() {
            main = new function_stack_node();
        }

        function_stack::~function_stack() {
            delete main;
        }

        void function_stack::entrance(const u4int segment) const {
            function_stack_node* node = new function_stack_node();
            node->name = 0;
            node->segment = segment;

            node->next = main->next;
            main->next = node;
        }

        u4int function_stack::exit() const {
            function_stack_node* node = main->next;
            if (node == nullptr) { return 0u; }
            main->next = node->next;
            node->next = nullptr;
            node->name;
            u4int segment = node->segment;
            delete node;
            return segment;
        }

        class virtual_register {
        private:
            u4int array[15];
        public:
            virtual_register();
            ~virtual_register();
            void set(s4int index, u4int value);
            u4int get(s4int index) const;
        };

        virtual_register::virtual_register() {
            for (u4int& i : array) {
                i = 0;
            }
        }

        virtual_register::~virtual_register() {
            for (u4int& i : array) {
                i = 0;
            }
        }

        void virtual_register::set(const s4int index, const u4int value) {
            array[index] = value;
        }

        u4int virtual_register::get(const s4int index) const {
            return array[index];
        }

        class coding_tree {
        private:
            class coding_tree_node {
            public:
                function operation;
                coding_tree_node* left;
                coding_tree_node* right;
                coding_tree_node();
                ~coding_tree_node();
            };
            coding_tree_node* base;
            bool bit_one(u1int code, u4int index_positive) const;
        public:
            coding_tree();
            ~coding_tree();
            s4int generation(u1int code, function fun) const;
            function found(u4int code) const;
        };

        coding_tree::coding_tree_node::coding_tree_node() {
            operation = nullptr;
            left = nullptr;
            right = nullptr;
        }

        coding_tree::coding_tree_node::~coding_tree_node() {
            delete left;
            delete right;
        }

        coding_tree::coding_tree() {
            base = new coding_tree_node();
        }

        coding_tree::~coding_tree() {
            delete base;
        }

        bool coding_tree::bit_one(const u1int code, const u4int index_positive) const {
            base;
            return code & 1u << (index_positive - 1);
        }

        s4int coding_tree::generation(const u1int code, const function fun) const {
            coding_tree_node* node = base;
            for (s4int i = 3; i > 0; i--) {
                if (bit_one(code, i)) {
                    if (node->right == nullptr) {
                        node->right = new coding_tree_node();
                    }
                    node = node->right;
                } else {
                    if (node->left == nullptr) {
                        node->left = new coding_tree_node();
                    }
                    node = node->left;
                }
            }
            node->operation = fun;
            return 1;
        }

        function coding_tree::found(const u4int code) const {
            u1int first = code >> 24u;
            coding_tree_node* node = base;
            for (s4int i = 3; i > 0; i--) {
                if (bit_one(first, i)) {
                    node = node->right;
                } else {
                    node = node->left;
                }
                if (node == nullptr) {
                    return nullptr;
                }
            }
            return node->operation;
        }

        class counter_step {
        private:
            s4int pc;
            u4int cs;
            u4int nc;
            virtual_register* ncr;
            virtual_memory* vmm;
            function_stack* scf;
            coding_tree* ins;
            u4int constant(const std::string& str) const;
            u4int calculate(s4int index, const std::string& word) const;
        public:
            counter_step();
            ~counter_step();
            s4int read(u4int length = 0, const char* file = nullptr);
            s4int step_point();
            void result() const;
        };

        u4int counter_step::constant(const std::string &str) const {
            pc;
            std::string sta[22] = {
                    "mov", "inc", "dec", "jnz", "jny", "cal", "ret",
                    "ax", "bx", "cx", "dx",
                    "e1x", "e2x", "e3x", "e4x", "e5x", "e6x", "e7x", "e8x", "e9x",
                    "rx", "fx"
            };
            u4int stb[22] = {
                    8u, 9u, 10u, 12u, 13u, 14u, 15u,
                    129u, 130u, 131u, 132u,
                    133u, 134u, 135u, 136u, 137u, 138u, 139u, 140u, 141u,
                    142u, 143u
            };
            for (int i = 0; i < 22; i++) {
                if (sta[i] == str) {
                    return stb[i];
                }
            }
            return 0u;
        }

        u4int counter_step::calculate(const s4int index, const std::string& word) const {
            if (constant(word) == 0 && index == 2) {
                s4int number = std::stoi(word);
                if (number < 0) {
                    return 0u;
                } else {
                    return (u4int)number;
                }
            } else {
                u4int number = constant(word);
                if (index == 0) {
                    return number << 24u;
                } else if (index == 1) {
                    return number << 16u;
                } else {
                    return number << 8u;
                }
            }
        }

        counter_step::counter_step() {
            pc = 0;
            cs = 1;
            nc = 0;
            ncr = new virtual_register();
            vmm = new virtual_memory();
            scf = new function_stack();
            ins = new coding_tree();
            ins->generation(8u, mov);
            ins->generation(9u, inc);
            ins->generation(10u, dec);
            ins->generation(12u, jnz);
            ins->generation(13u, jny);
            ins->generation(14u, cal);
            ins->generation(15u, ret);
        }

        counter_step::~counter_step() {
            delete ncr;
            delete vmm;
            delete scf;
            delete ins;
        }

        s4int counter_step::read(const u4int length, const char* file) {
            std::string str;
            u4int segment;
            if (file == nullptr) {
                if (length == 15) {
                    str = "mov e1x 12\n"
                          "mov e2x 31\n"
                          "mov e3x 5\n"
                          "mov e4x 36\n"
                          "mov ax e1x\n"
                          "mov bx e2x\n"
                          "cal 0 17\n"
                          "mov e5x rx\n"
                          "mov ax e3x\n"
                          "mov bx e4x\n"
                          "cal 0 17\n"
                          "mov ax e5x\n"
                          "mov bx rx\n"
                          "cal 0 17\n"
                          "mov e6x rx";
                    segment = vmm->apply(length);
                } else if (length == 9) {
                    str = "mov e1x ax\n"
                          "mov e2x bx\n"
                          "cal 0 33\n"
                          "mov dx rx\n"
                          "inc e1x\n"
                          "dec e2x\n"
                          "jnz e2x 2\n"
                          "mov rx e1x\n"
                          "ret";
                    segment = vmm->apply(length);
                } else if (length == 11) {
                    str = "mov e1x ax\n"
                          "mov e2x bx\n"
                          "dec ax\n"
                          "dec bx\n"
                          "jny ax 2\n"
                          "jny bx 4\n"
                          "jnz bx 4\n"
                          "mov rx e1x\n"
                          "ret\n"
                          "mov rx e2x\n"
                          "ret";
                    segment = vmm->apply(length);
                }
            } else {
                str = "";
                std::ifstream in_read(file, std::ios::in);
                s4int number = 0;
                for (std::string line;std::getline(in_read, line);) {
                    number++;
                    str.append(line).append("\n");
                }
                segment = vmm->apply(number);
            }
            // 真正的主要部分
            std::vector<std::string> lines = spilt(str, "\n");
            for (s4int i = 0; i < lines.size(); i++) {
                std::vector<std::string> words = spilt(lines[i], " ");
                u4int code = 0;
                for (s4int j = 0; j < words.size(); j++) {
                    code = code + calculate(j,words[j]);
                }
                vmm->overlay(segment, i, code);
            }

            return 1;
        }

        s4int counter_step::step_point() {
            if (pc >= 0 && pc < 2000000000) {
                u4int code = vmm->read(cs, nc);
                if (code == 0) { return 0; }
                function fun = ins->found(code);
                if (fun == nullptr) { return 0; }
                if (fun(nc, code, ncr, vmm, scf, cs) == 0) { return 0; }
                pc++;
                return 1;
            } else {
                return 0;
            }
        }

        void counter_step::result() const {
            std::printf("pc = [%010d]\n", pc);
            std::printf("[%08x]\n", ncr->get(3));
            std::printf("[%08x]\n", ncr->get(4));
            std::printf("[%08x]\n", ncr->get(5));
            std::printf("[%08x]\n", ncr->get(6));
            std::printf("[%08x]\n", ncr->get(7));
            std::printf("[%08x]\n", ncr->get(8));
            std::printf("[%08x]\n", ncr->get(9));
        }

        s4int mov(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs) {
            u4int first = code >> 24u;
            u4int second = (code << 8u) >> 24u;
            u4int third = (code << 16u) >> 16u;

            if (first != 8u) { mem;scf;return 0; }

            if (third > 1u << 15u) {
                third = third >> 8u;
                ncr->set(second - 129, ncr->get(third - 129));
            } else {
                ncr->set(second - 129, third);
            }
            nc++;
            return 1;
        }

        s4int inc(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs) {
            u4int first = code >> 24u;
            u4int second = (code << 8u) >> 24u;

            if (first != 9u) { mem;scf;return 0; }

            ncr->set(second - 129, ncr->get(second - 129) + 1);
            nc++;
            return 1;
        }

        s4int dec(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs) {
            u4int first = code >> 24u;
            u4int second = (code << 8u) >> 24u;

            if (first != 10u) { mem;scf;return 0; }

            ncr->set(second - 129, ncr->get(second - 129) - 1);
            nc++;
            return 1;
        }

        s4int jnz(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs) {
            u4int first = code >> 24u;
            u4int second = (code << 8u) >> 24u;
            u4int third = (code << 16u) >> 16u;

            if (first != 12u) { mem;scf;return 0; }

            if (ncr->get(second - 129) == 0) {
                nc++;
            } else {
                nc = nc - third;
            }
            return 1;
        }

        s4int jny(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs) {
            u4int first = code >> 24u;
            u4int second = (code << 8u) >> 24u;
            u4int third = (code << 16u) >> 16u;

            if (first != 13u) { mem;scf;return 0; }

            if (ncr->get(second - 129) == 0) {
                nc++;
            } else {
                nc = nc + third;
            }
            return 1;
        }

        s4int cal(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs) {
            u4int first = code >> 24u;
            u4int second = (code << 8u) >> 24u;
            u4int third = (code << 16u) >> 16u;

            if (first != 14u) { return 0; }

            nc++;
            u4int segment = mem->apply(12u);
            scf->entrance(segment);
            mem->overlay(segment, 1, cs);
            mem->overlay(segment, 2, nc);
            mem->overlay(segment, 3, ncr->get(4));
            mem->overlay(segment, 4, ncr->get(5));
            mem->overlay(segment, 5, ncr->get(6));
            mem->overlay(segment, 6, ncr->get(7));
            mem->overlay(segment, 7, ncr->get(8));
            mem->overlay(segment, 8, ncr->get(9));
            mem->overlay(segment, 9, ncr->get(10));
            mem->overlay(segment, 10, ncr->get(11));
            mem->overlay(segment, 11, ncr->get(12));

            if (second == 0) { cs = third; }
            nc = 0;
            return 1;
        }

        s4int ret(u4int& nc, const u4int code, virtual_register* ncr, virtual_memory* const mem, function_stack* const scf, u4int& cs) {
            u4int first = code >> 24u;

            if (first != 15u) { return 0; }

            u4int segment = scf->exit();
            cs = mem->read(segment,1);
            nc = mem->read(segment,2);
            ncr->set(4,mem->read(segment,3));
            ncr->set(5,mem->read(segment,4));
            ncr->set(6,mem->read(segment,5));
            ncr->set(7,mem->read(segment,6));
            ncr->set(8,mem->read(segment,7));
            ncr->set(9,mem->read(segment,8));
            ncr->set(10,mem->read(segment,9));
            ncr->set(11,mem->read(segment,10));
            ncr->set(12,mem->read(segment,11));
            mem->release(segment);
            return 1;
        }
        class [[maybe_unused]] tagscccd {};
        //notice
        //CLang-Tidy属于静态代码扫描，语法要求高，但有时却需要那种写法
    }

    //main函数写法，既示例
    int cpu_run_main() {
        auto* counter = new cpu::counter_step();
        counter->read(15);
        counter->read(9);
        counter->read(11);
        for (;;) {
            if (counter->step_point() == 0) { break; }
        }
        counter->result();
        return 0;
    }
}

#endif //VIRTUAL_CPU_H
