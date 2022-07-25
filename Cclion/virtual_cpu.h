//
// Created by kuu*kie on 2022/7/22.
//

#ifndef VIRTUAL_CPU_H
#define VIRTUAL_CPU_H

#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace kuu {

    namespace cpu {
        //
        class [[maybe_unused]] tagscccf;
        typedef unsigned long u8int;
        typedef unsigned int u4int;
        typedef unsigned short u2int;
        typedef unsigned char u1int;
        typedef long s8int;
        typedef int s4int;
        typedef short s2int;
        typedef char s1int;

        u4int hash_code(const char* key);
        std::vector<std::string> spilt(std::string str, const std::string& pattern);

        class virtual_memory;
        class function_stack;
        class virtual_register;

        using function = s4int (*)(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int mov(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int inc(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int dec(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int jnz(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int jny(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int cal(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);
        s4int ret(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs);

        class [[maybe_unused]] tagscccf {};

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

        class [[maybe_unused]] tagscccd;//内存地址 511+1 128 64 64 32 32 32 32 16 16 16 16 16 16 16 16
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
            u4int read(u4int segment, u4int offset);
        };

        class [[maybe_unused]] tagscccd {};
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

        u4int virtual_memory::apply(u4int size) {
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

        s4int virtual_memory::release(u4int segment) {
            for (s4int i = 0; i < 16; i++) {
                if (index[i] == segment) {
                    use[i] = 0;
                    return 1;
                }
            }
            return 0;
        }

        void virtual_memory::overlay(u4int segment, u4int offset, u4int value) {
            for (s4int i = 0; i < 16; i++) {
                if (index[i] == segment) {
                    if (use[i] > offset) {
                        memory[segment + offset] = value;
                    }
                    break;
                }
            }
        }

        u4int virtual_memory::read(u4int segment, u4int offset) {
            return memory[segment + offset];
        }

        class [[maybe_unused]] tagscccc;//函数调用栈
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
            void entrance(u4int segment);
            u4int exit();
        };

        class [[maybe_unused]] tagscccc {};
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

        void function_stack::entrance(const u4int segment) {
            function_stack_node* node = new function_stack_node();
            node->name = 0;
            node->segment = segment;

            node->next = main->next;
            main->next = node;
        }

        u4int function_stack::exit() {
            function_stack_node* node = main->next;
            if (node == nullptr) { return 0u; }
            main->next = node->next;
            node->next = nullptr;
            u4int segment = node->segment;
            delete node;
            return segment;
        }

        class [[maybe_unused]] tagsccce;// ax bx cx dx e1x e2x e3x e4x e5x e6x e7x e8x e9x rx fx
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

        void virtual_register::set(s4int index, u4int value) {
            array[index] = value;
        }

        u4int virtual_register::get(s4int index) const {
            return array[index];
        }

        s4int mov(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs) {
            u4int first = code >> 24u;
            u4int second = (code << 8u) >> 24u;
            u4int third = (code << 16u) >> 16u;

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

            ncr->set(second - 129, ncr->get(second - 129) + 1);
            nc++;
            return 1;
        }

        s4int dec(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs) {
            u4int first = code >> 24u;
            u4int second = (code << 8u) >> 24u;

            ncr->set(second - 129, ncr->get(second - 129) - 1);
            nc++;
            return 1;
        }

        s4int jnz(u4int& nc, u4int code, virtual_register* ncr, virtual_memory* mem, function_stack* scf, u4int& cs) {
            u4int first = code >> 24u;
            u4int second = (code << 8u) >> 24u;
            u4int third = (code << 16u) >> 16u;

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

            nc++;
            u4int segment = mem->apply(15u);
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
            cs = third;
            nc = 0;
            return 1;
        }

        s4int ret(u4int& nc, const u4int code, virtual_register* const ncr, virtual_memory* const mem, function_stack* const scf, u4int& cs) {
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
            return 1;
        }

        class [[maybe_unused]] tagsccc7;
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
            s4int generation(u1int code, function fun);
            function found(u4int code) const;
        };

        class [[maybe_unused]] tagsccc7 {};
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

        s4int coding_tree::generation(const u1int code, const function fun) {
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

        class [[maybe_unused]] tagsccca;
        class counter_step {
        private:
            s4int pc;
            u4int cs;
            u4int nc;
            virtual_register* ncr;
            virtual_memory* vmm;
            function_stack* scf;
            coding_tree* ins;
            u4int constant(const std::string& str);
            u4int calculate(s4int index, const std::string& word);
        public:
            counter_step();
            ~counter_step();
            s4int read(u4int length = 0, const char* file = nullptr);
            s4int step_point();
            void result();
        };

        class [[maybe_unused]] tagsccca {};
        u4int counter_step::constant(const std::string &str) {
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

        u4int counter_step::calculate(s4int index, const std::string& word) {
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

        s4int counter_step::read(u4int length, const char *file) {
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
                          "call 0 33\n"
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
            } else { ; }

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
                if (fun(nc, code, ncr, vmm, scf, cs) == 0) { return 0; }
                pc++;
                return 1;
            } else {
                return 0;
            }
        }

        void counter_step::result() {
            std::printf("[%08x]", vmm->read(1,0));
            std::printf("[%08x]", vmm->read(1,1));
            std::printf("[%08x]", vmm->read(1,2));
            std::printf("[%08x]", vmm->read(1,3));
            std::printf("[%08x]", vmm->read(1,4));
            std::printf("[%08x]", vmm->read(1,5));
            std::printf("[%08x]", vmm->read(1,6));
            std::printf("[%08x]", vmm->read(1,7));
            std::printf("[%08x]", vmm->read(1,8));
            std::printf("[%08x]", vmm->read(1,9));
            std::printf("[%08x]", vmm->read(1,10));
            std::printf("[%08x]", vmm->read(1,11));
            std::printf("[%08x]", vmm->read(1,12));
            std::printf("[%08x]", vmm->read(1,13));
            std::printf("[%08x]\n", vmm->read(1,14));
            std::printf("[%08x]", vmm->read(17,0));
            std::printf("[%08x]", vmm->read(17,1));
            std::printf("[%08x]", vmm->read(17,2));
            std::printf("[%08x]", vmm->read(17,3));
            std::printf("[%08x]", vmm->read(17,4));
            std::printf("[%08x]", vmm->read(17,5));
            std::printf("[%08x]\n", vmm->read(17,6));
            std::printf("[%08x]\n", ncr->get(3));
            std::printf("[%08x]\n", ncr->get(4));
            std::printf("[%08x]\n", ncr->get(5));
            std::printf("[%08x]\n", ncr->get(6));
            std::printf("[%08x]\n", ncr->get(7));
            std::printf("[%08x]\n", ncr->get(8));
            std::printf("[%08x]\n", ncr->get(9));
        }
    }

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
