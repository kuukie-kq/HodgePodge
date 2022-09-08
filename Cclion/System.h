//
// Created by kuu-kie on 2022-09-06.
//

#ifndef SYSTEM_H
#define SYSTEM_H
//
//  创建日期  2022-07-08
//  【看完设计模式，发现其带来的便利性】
//  版本日志  ==== 日期 ====  标识及说明
//  ==== 2022-09-06 ====  hickey system_stream
//  确定编写格式，并将两个最基本的类完成
//  特别注意，本格式在使用时还是存在问题，类声明需要对类内信息进行声明
//  不能单独声明一个类，否则打包成库后，引用头文件无法使用类的具体功能
//  既出现错误：class has incomplete type
//  目前就按照这个方式写
//  ==== 2022-09-07 ====  red_black_tree iterable stack
//  继续增加相关类，红黑树（常用）以及栈（常用且可迭代）
//  同时对enum进行扩充且加入注释
//  发现输出流的校验（check_serialize）扩展性并不太好
//  ==== 2022-09-08 ====  utils
//  还是补上一些单例模式（常用量，常用函数）
//  不确定是否一定需要，后面看情况，有没有更好的写法等
//

#ifndef _H_FILE
#define _H_FILE

#include <iostream> //输入输出
#include <sstream> //输入输出缓冲
#include <cstdarg> //不定参数处理
#include <chrono> //时间戳
#include <string> //字符串类
#include <vector> //不定数组，字符串分割
#include <fstream> //读写文件

namespace kuu {
    // typedef unsigned int u4int;
    // typedef unsigned char u1int;
    // typedef int s4int;
    // typedef char s1int;

    // 对于有内部类的情况，可以声明友元类来访问private成员

    enum {
        HICKEY = 3260681415u,
        SYSTEM_STREAM = 101u,
        RED_BLACK_TREE = 144u,
        STACK = 151u
    };

    class hickey;
    class system_stream;
    template<class SERIAL> class red_black_tree;
    class iterable;
    template<class SERIAL> class stack;
}

#endif //_H_FILE

#if true
// 是否声明与定义在同一文件中
#define _CPP_FILE

namespace kuu {
    // 单例
    // 对于一些很难受的警告可以使用注释 //NOLINT 来消除
    // 明知代码没有问题，规范上也说得过去
    class utils final {
    private:
        utils() = default;
        ~utils() = default;
        utils &operator=(utils&) = default;
        utils(const utils&) = default;
        utils &operator=(utils&&) = default;
        utils(utils&&) = default;
        static utils* u;
    public:
        static utils* signal() { return u; }
        inline unsigned int hash_code(const char* key) const { unsigned int result; unsigned char* byte; for (result = 0, byte = (unsigned char*) key; *byte; byte++) { result = result * 31 + *byte; } return result; } //NOLINT
        inline std::vector<std::string> spilt(std::string str, const std::string& pattern) const { std::string::size_type pos; std::vector<std::string> result; str += pattern; unsigned int size = str.size(); for (unsigned int i = 0; i < size; i++) { pos = str.find(pattern, i); if (pos < size) { std::string s = str.substr(i, pos - i); result.push_back(s); i = pos + pattern.size() - 1; } } return result; } //NOLINT
        // 一种写法
        inline unsigned int encode(const char* key) const { //NOLINT
            // 由于数据大小的限制，27进制最大只能存7位
            // 4294967295
            // b28jpdl  标准编码数
            // 为下划线和26个字母，对应应用于类的标识，由于类名一般不短，需摘要部分
            // 固，保证全覆盖，key只能为6位，且不允许下划线开头
            unsigned int result;
            unsigned char* byte;
            for (result = 0, byte = (unsigned char*) key; *byte; byte++) {
                if ((*byte - 96) > 0 && (*byte - 96) < 27) {
                    result = result * 27 + *byte - 96;
                } else if (*byte == 95) {
                    result = result * 27;
                } else {
                    return 0;
                }
            }
            return result;
        }
        // 对应的
        inline int decode(unsigned int secret, std::string* key) const { //NOLINT
            int stack[6];
            for (int& i : stack) { i = -1; }
            if (secret == 0) { return 0; }
            int s = 0;
            for (unsigned int i = secret; i > 0; i = i / 27) {
                stack[s++] = static_cast<int>(i % 27u);
            }
            for (s--; s >= 0; s--) {
                if (stack[s] == 0) {
                    key->append("_");
                } else {
                    key->push_back(static_cast<char>(stack[s] + 96));
                }
            }
            return 1;
        }
    };
    // 单例初始化
    utils* utils::u = new utils(); //NOLINT
    // 接口
    class hickey { //NOLINT
    private:
        // 禁用拷贝构造函数
        // 禁用赋值运算符
        hickey& operator=(hickey&) = default;
        hickey(hickey&) = default;
        hickey& operator=(hickey&&) = default;
        hickey(hickey&&) = default;
    protected:
        // 禁用构造函数，也不算禁用，就是无法正常使用，防止产生实例
        // 如果存在纯虚函数，就产生不了实例
        hickey() = default;
        inline bool check_conversion(const hickey* const target) const { return sign() == target->sign(); } // 方便使用，判断是否是同一种类
        virtual inline bool check_serialize(const hickey* const target) const { return target->sign() == SYSTEM_STREAM; }
        inline system_stream* replace_serialize(const hickey* const target) const { return (system_stream*)target; } //NOLINT
    public:
        virtual ~hickey() = default;
        virtual unsigned int sign() const { return HICKEY; } // 类的签名//相当于java.getClass，由于类之间的关系问题，如果为static模板中还是无法直接使用，且static的情况不能使用虚函数定义，故，作为数据类来说，需要保证存在无参的构造函数
        virtual bool equals(const hickey* const target) const { return this == target; } // 判断两个对象是否相等//相当于java.equals
        virtual int clone(hickey*& target) const { return 0; } // 克隆出一个内容一样的不同内存，注意，使用深拷贝，另外注意参数的传递，可能会出现内存无法回收的情况（自己传自己）//相当于java.clone
        virtual int hash() const { return 0; } // 对象的标识或排序规则//相当于java.hashCode
        virtual int serialize(hickey* sys) const { return 0; } // 非规范的序列化//相当于java.toString
    };
    // 特别说明，由于hickey::clone参数的问题，可能出现o.clone(o)的情况
    // 如果是两个栈指针，且条件分支实现了，则clone的功能完全没问题
    // 但是以防万一，默认条件分支不实现，需要最少有一个无参的构造函数可以使用
    class system_stream : public hickey {
    protected:
        class time_stamp {
        private:
            std::chrono::nanoseconds start_stamp = std::chrono::nanoseconds::zero();
        public:
            time_stamp() { start_stamp = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()); }
            ~time_stamp() { start_stamp = std::chrono::nanoseconds::zero(); }
            unsigned long long time_line_passed() { std::chrono::nanoseconds now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()); unsigned long long passed = now.count() - start_stamp.count(); if (passed > 0) { return (passed); } return 0; }
            unsigned long long time_start() { return start_stamp.count(); }
            static unsigned long long time_now() { std::chrono::nanoseconds now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()); unsigned long long passed = now.count(); return passed; }
        };
        static inline unsigned int time_nano(unsigned long long stamp) { unsigned int re = stamp % 1000; return re; }
        static inline unsigned int time_milli(unsigned long long stamp) { unsigned int re = stamp / 1000 % 1000; return re; }
        static inline unsigned int time_micro(unsigned long long stamp) { unsigned int re = stamp / 1000000 % 1000; return re; }
        static inline unsigned int time_second(unsigned long long stamp) { unsigned int re = stamp / 1000000000 % 60; return re; }
        static inline unsigned int time_minute(unsigned long long stamp) { unsigned int re = stamp / 1000000000 / 60 % 60; return re; }
        static inline unsigned int time_hour(unsigned long long stamp) { unsigned int re = stamp / 1000000000 / (60 * 60) % 24; return re + 8; }// UTC+8 (GMT)
        const static int MAX_LENGTH = 1024;
        const static int BUFFER_SIZE = 1048575; // 2^20 - 1
        void upgrade(std::stringstream* sys, const char *format, ...) const {
            if (level & on_or_off) {
                char *buff = (char *) malloc(MAX_LENGTH);
                va_list args;
                va_start(args, format);
                int length = vsnprintf(buff, MAX_LENGTH, format, args);
                (length >= MAX_LENGTH) ? *sys << length << "- format and args too long" : *sys << buff;
                va_end(args);
                delete buff;
            }
        }
        time_stamp* timer;
        unsigned int on_or_off;
        unsigned int level;
        std::stringstream* stream;
        std::stringstream* buffer;
        // 可做扩展
        virtual void step() const {
            if (buffer->rdbuf()->in_avail() > BUFFER_SIZE) {
                std::cout << buffer->str();
                buffer->clear();
                buffer->str("");
            }
            unsigned long long tmp = time_stamp::time_now();
            upgrade(buffer, "<-\t[%02d:%02d:%02d %03dms%03dus%03dns]", time_hour(tmp), time_minute(tmp), time_second(tmp), time_micro(tmp), time_milli(tmp), time_nano(tmp));
            *buffer << stream->str();
            unsigned long stamp = timer->time_line_passed();
            upgrade(buffer,"\t%llu[%d s %d ms %d us %d ns] <\n", stamp, stamp / 1000000000, time_micro(stamp), time_milli(stamp), time_nano(stamp));
        }
        virtual void log() const {
            if (buffer->rdbuf()->in_avail() > 0) {
                std::cout << buffer->str();
                buffer->clear();
                buffer->str("");
            }
            unsigned long long tmp = time_stamp::time_now();
            upgrade(buffer, "<*\t[%02d:%02d:%02d %03dms%03dus%03dns]", time_hour(tmp), time_minute(tmp), time_second(tmp), time_micro(tmp), time_milli(tmp), time_nano(tmp));
            *buffer << stream->str();
            unsigned long stamp = timer->time_line_passed();
            upgrade(buffer,"\t%llu[%d s %d ms %d us %d ns] >\n", stamp, stamp / 1000000000, time_micro(stamp), time_milli(stamp), time_nano(stamp));
            std::cout << buffer->str();
            buffer->clear();
            buffer->str("");
        }
        virtual void warning() const {
            unsigned long long tmp = time_stamp::time_now();
            upgrade(buffer, ">-\t[%02d:%02d:%02d %03dms%03dus%03dns]", time_hour(tmp), time_minute(tmp), time_second(tmp), time_micro(tmp), time_milli(tmp), time_nano(tmp));
            *buffer << stream->str();
            unsigned long stamp = timer->time_line_passed();
            upgrade(buffer,"\t%llu[%d s %d ms %d us %d ns] <\n", stamp, stamp / 1000000000, time_micro(stamp), time_milli(stamp), time_nano(stamp));
            std::cout << buffer->str();
            buffer->clear();
            buffer->str("");
        }
        virtual void error() const {
            unsigned long long tmp = time_stamp::time_now();
            upgrade(buffer, ">*\t[%02d:%02d:%02d %03dms%03dus%03dns]", time_hour(tmp), time_minute(tmp), time_second(tmp), time_micro(tmp), time_milli(tmp), time_nano(tmp));
            *buffer << stream->str();
            unsigned long stamp = timer->time_line_passed();
            upgrade(buffer,"\t%llu[%d s %d ms %d us %d ns] <\n", stamp, stamp / 1000000000, time_micro(stamp), time_milli(stamp), time_nano(stamp));
            std::cerr << buffer->str();
            buffer->clear();
            buffer->str("");
        }
    public:
        explicit system_stream(unsigned int ooo = 1u, unsigned int mode = 0) { stream = new std::stringstream(); buffer = new std::stringstream(); on_or_off = ooo; level = mode; timer = new time_stamp(); }
        ~system_stream() override { delete timer; delete stream; delete buffer; }
        void clear() { stream->clear(); stream->str(""); level = 0; }
        void start(unsigned int mode) { if (stream->rdbuf()->in_avail() > 0) { clear(); } level = mode; }
        void maybe(unsigned int mode) { level = mode; }
        void append(const char *format, ...) const {
            if (level & on_or_off) {
                char *buff = (char *) malloc(MAX_LENGTH);
                va_list args;
                va_start(args, format);
                int length = vsnprintf(buff, MAX_LENGTH, format, args);
                (length >= MAX_LENGTH) ? *stream << length << "- format and args too long" : *stream << buff;
                va_end(args);
                delete buff;
            }
        }
        void end() {
            if (level == 0) return;
            bool error_on = (level & 1u) & (on_or_off & 1u);
            bool warning_on = (level & 2u) & (on_or_off & 2u);
            bool log_on = (level & 4u) & (on_or_off & 4u);
            bool step_on = (level & 8u) & (on_or_off & 8u);
            if (error_on) {
                error();
            } else if (warning_on) {
                warning();
            } else if (log_on) {
                log();
            } else if (step_on) {
                step();
            }
            clear();
        }
        unsigned int sign() const override { return SYSTEM_STREAM; }
        bool equals(const hickey* target) const override { if (check_conversion(target)) { return ((system_stream*)target)->stream->str() == stream->str() && ((system_stream*)target)->buffer->str() == buffer->str(); } return false; }
        int clone(hickey*& target) const override { if (target == nullptr) { return 0; } if (check_conversion(target)) { if (this == target) { return 2; } else { delete target; target = new system_stream(on_or_off, level); return 1; } } return 0; }
        int hash() const override { return static_cast<int>(timer->time_start()); }
        int serialize(hickey* sys) const override { return 0; }
    };
    // 红黑树，需要实现hickey接口，且确保实现了hash sign serialize
    // 红黑树中的value既标识排序的字段需要用到
    template<class SERIAL> class red_black_tree final : public hickey {
        // 定义
        // 红黑树是特殊的二叉查找树（AVL）
        // 特性
        // 1）每个节点只有可能为黑色或者红色
        // 2）根节点为黑色
        // 3）叶子节点一定是null，即为黑色
        // 4）如果一个节点是红色，则它的子节点一定是黑色
        // 5）从一个节点到其叶子节点的所有路径包含相同数量的黑色节点
    private:
        // Linux内核中的红黑树，color和parent合为一个long指针
        // 因为在系统中的地址，最后两位一定是0（一般情况）
        enum red_black { RED = 0, BLACK = 1};
        class node {
        public:
            hickey* value;
            red_black color;
            node* left;
            node* right;
            void* parent;
            explicit node(hickey* value = new SERIAL()) : value(value) {
                color = RED;
                left = nullptr;
                right = nullptr;
                parent = nullptr;
            }
            ~node() { delete left; delete right; delete value; }
        };
        void left_rotate(node* pivot) { // 左旋
            node* right = pivot->right;
            pivot->right = right->left;
            if (right->left != nullptr) {
                right->left->parent = pivot;
            }
            right->parent = pivot->parent;
            if (pivot->parent == nullptr) {
                root = right;
            } else if (parent_node(pivot)->left == pivot) {
                parent_node(pivot)->left = right;
            } else {
                parent_node(pivot)->right = right;
            }
            right->left = pivot;
            pivot->parent = right;
        }
        void right_rotate(node* pivot) { // 右旋
            node* left = pivot->left;
            pivot->left = left->right;
            if (left->right != nullptr) {
                left->right->parent = pivot;
            }
            left->parent = pivot->parent;
            if (pivot->parent == nullptr) {
                root = left;
            } else if (parent_node(pivot)->left == pivot) {
                parent_node(pivot)->left = left;
            } else {
                parent_node(pivot)->right = left;
            }
            left->right = pivot;
            pivot->parent = left;
        }
        node* parent_node(node* child) const { if(child == nullptr) { return nullptr; } return (node*)child->parent; }
        void fix_after_append(node* check) { // 插入后的调整
            for (; check != nullptr && root != check && parent_node(check)->color == RED;) {
                if (parent_node(check) == parent_node(parent_node(check))->left) {
                    node* uncle = parent_node(parent_node(check))->right;
                    if (uncle != nullptr && uncle->color == RED) {
                        uncle->color = BLACK;
                        parent_node(check)->color = BLACK;
                        check = parent_node(parent_node(check));
                        check->color = RED;
                    } else {
                        if (check == parent_node(check)->right) {
                            check = parent_node(check);
                            left_rotate(check);
                        }
                        parent_node(check)->color = BLACK;
                        parent_node(parent_node(check))->color = RED;
                        right_rotate(parent_node(parent_node(check)));
                    }
                } else {
                    node* uncle = parent_node(parent_node(check))->left;
                    if (uncle != nullptr && uncle->color == RED) {
                        uncle->color = BLACK;
                        parent_node(check)->color = BLACK;
                        check = parent_node(parent_node(check));
                        check->color = RED;
                    } else {
                        if (check == parent_node(check)->left) {
                            check = parent_node(check);
                            right_rotate(check);
                        }
                        parent_node(check)->color = BLACK;
                        parent_node(parent_node(check))->color = RED;
                        left_rotate(parent_node(parent_node(check)));
                    }
                }
            }
            root->color = BLACK;
        }
        node* found(int value) {
            node* current = root;
            for (; current != nullptr;) {
                if (current->value->hash() > value) {
                    current = current->left;
                } else if (current->value->hash() < value) {
                    current = current->right;
                } else {
                    break;
                }
            }
            return current;
        }
        node* successor(node* check) const { // 查找当前节点的后继节点，既中序遍历的下一个节点
            node* most_left = check->right;
            for (; most_left != nullptr && most_left->left != nullptr;) {
                most_left = most_left->left;
            }
            return most_left;
        }
        void fix_after_subtract(node* check) { // 删除时的调整
            for (; check != root && BLACK == check->color;) {
                if (check == parent_node(check)->left) {
                    node* sister = parent_node(check)->right;
                    if (RED == sister->color) {
                        sister->color = BLACK;
                        parent_node(check)->color = RED;
                        left_rotate(parent_node(check));
                        sister = parent_node(check)->right;
                    }
                    if ((sister->left == nullptr || BLACK == sister->left->color) &&
                        (sister->right == nullptr || BLACK == sister->right->color)) {
                        sister->color = RED;
                        check = parent_node(check);
                    } else {
                        if (sister->right == nullptr || BLACK == sister->right->color) {
                            sister->left->color = BLACK;
                            sister->color = RED;
                            right_rotate(sister);
                            sister = parent_node(check)->right;
                        }
                        sister->color = parent_node(check)->color;
                        parent_node(check)->color = BLACK;
                        if (sister->right != nullptr)
                            sister->right->color = BLACK;
                        left_rotate(parent_node(check));
                        check = root;
                    }
                } else {
                    node* sister = parent_node(check)->left;
                    if (RED == sister->color) {
                        sister->color = BLACK;
                        parent_node(check)->color = RED;
                        right_rotate(parent_node(check));
                        sister = parent_node(check)->left;
                    }
                    if ((sister->left == nullptr || BLACK == sister->left->color) &&
                        (sister->right == nullptr || BLACK == sister->right->color)) {
                        sister->color = RED;
                        check = parent_node(check);
                    } else {
                        if (sister->left == nullptr || BLACK == sister->left->color) {
                            sister->right->color = BLACK;
                            sister->color = RED;
                            left_rotate(sister);
                            sister = parent_node(check)->left;
                        }
                        sister->color = parent_node(check)->color;
                        if (sister->left != nullptr)
                            sister->left->color = BLACK;
                        parent_node(check)->color = BLACK;
                        right_rotate(parent_node(check));
                        check = root;
                    }
                }
            }
            check->color = BLACK;
        }
        inline void pre_order(unsigned int index, const unsigned int offset, node* node, const unsigned int level, system_stream* out) const {
            if (node == nullptr) { return; }
            // 树放入数组中，由两个指标表示下标
            // 一个是父节点的下标，一个是父节点的左子（1）还是右子（2）
            // 既，根节点默认0，0
            // 这样父节点的下标乘以2，再加上一个数，即为本节点在数组中的下标
            index = index * 2 + offset;

            out->append("[%4u]{level:%2u,\tcolor:%s\t,value:",
                        index, level, node->color ? "Black\0" : "Red\0");
            node->value->serialize(out);
            out->append("}\n");

            pre_order(index, 1, node->left, level + 1, out);
            pre_order(index, 2, node->right, level + 1, out);
        }
        node* root;
        inline bool template_check(hickey* const data) const { auto* s = new SERIAL(); return s->sign() == data->sign(); }
    public:
        red_black_tree() { root = nullptr; }
        ~red_black_tree() override { delete root; }
        void rb_insert(hickey* value) {
            // 插入节点
            // 1）父节点是黑的，无需做处理
            // 2）父节点和叔节点为红，修改父节点和叔节点为黑色，改变祖父节点为红色
            // 3）父节点为红叔节点为黑，四种情况，有直接旋转变色和先反向旋转再旋转变色之分
            if(!template_check(value)) { return; }
            auto* new_node = new node(value);
            if (root == nullptr) {
                new_node->color = BLACK;
                root = new_node;
            }

            node* current = root;
            node* temp = current;
            for (; current != nullptr;) {
                temp = current;
                if (current->value->hash() > value->hash()) {
                    current = current->left;
                } else if (current->value->hash() < value->hash()) {
                    current = current->right;
                } else {
                    return;
                }
            }

            if (temp->value->hash() > value->hash()) {
                temp->left = new_node;
            } else {
                temp->right = new_node;
            }
            new_node->parent = temp;
            fix_after_append(new_node);
        }
        void rb_delete(int hash_value) {
            // 删除节点
            // 1）删除的节点为叶子节点，可以直接删除
            // 2）删除的节点只有一个子节点，子节点顶替
            // 3）删除的节点有两个子节点，先找其后继节点，然后复制内容，则删除的是（替身）后继节点所在的位置
            node* delete_node = found(hash_value);
            if (delete_node == nullptr) { return; }
            if (delete_node->left != nullptr && delete_node->right != nullptr) {
                node* temp = successor(delete_node);
                temp->value->clone(delete_node->value);
                delete_node = temp;
            }
            node* replacement = delete_node->left == nullptr ? delete_node->right : delete_node->left;
            if (replacement == nullptr) {
                if (delete_node->parent == nullptr) {
                    root = nullptr;
                } else {
                    if (BLACK == delete_node->color) {
                        fix_after_subtract(delete_node);
                    }
                    if (delete_node == parent_node(delete_node)->left) {
                        parent_node(delete_node)->left = nullptr;
                    } else {
                        parent_node(delete_node)->right = nullptr;
                    }
                    delete_node->parent = nullptr;
                }
            } else {
                replacement->color = BLACK;
                replacement->parent = parent_node(delete_node);
                if (delete_node->parent == nullptr) {
                    root = replacement;
                } else if (delete_node == parent_node(delete_node)->left) {
                    parent_node(delete_node)->left = replacement;
                } else {
                    parent_node(delete_node)->right = replacement;
                }
                delete_node->parent = nullptr;
                delete_node->left = nullptr;
                delete_node->right = nullptr;
            }
            // 注意此处将数据部分的内存进行了回收，不需要再手动删除find找到的指针
            delete delete_node;
        }
        SERIAL* find(int hash_value) {
            node* new_node = found(hash_value);
            if (new_node == nullptr) { return nullptr; }
            return (SERIAL*)new_node->value;
        }
        void scanning() const {
            auto* out = new system_stream(15u);
            out->start(1u << 2u);
            out->append("\n");
            pre_order(0u, 0, root, 1u, out);
            out->end();
        }
        unsigned int sign() const override { return RED_BLACK_TREE; }
        bool equals(const hickey* target) const override { return target == this; }
        int clone(hickey*& target) const override { return 0; }
        int hash() const override { return 0; }
        int serialize(hickey* sys) const override { if (check_serialize(sys)) { auto* out = replace_serialize(sys); pre_order(0u,0u,root,1u,out); return 1; } return 0; }
    };
    // 在原接口中又加入了迭代器相关的接口
    // 注意需要内部实现iterator接口
    class iterable : public hickey {
    protected:
        iterable() = default;
        class iterator {
        public:
            iterator() = default;
            virtual ~iterator() = default;
            virtual hickey* next() { return nullptr; }
            virtual bool last() { return true; }
        };
    public:
        virtual iterator* iter() const { return new iterator(); }
        ~iterable() override = default;
    };
    // 栈，与红黑树相似，只不过有迭代器相关功能
    // 原则上是只能存放同类型的数据
    template<class SERIAL> class stack final : public iterable {
    private:
        class node {
        public:
            hickey* value;
            node* next;
            explicit node(hickey* value = new SERIAL()) : value(value) { next = nullptr; }
            ~node() { delete next; delete value; }
        };
        node* head;
        class ite : public iterator {
        private:
            node* flow;
        public:
            hickey* next() override { flow = flow->next; return flow->value; }
            bool last() override { return flow->next == nullptr; }
            explicit ite(node* head) : flow(head) {}
            ~ite() override = default;
        };
        inline bool template_check(hickey* const data) const { return head->value->sign() == data->sign(); }
    public:
        iterator* iter() const override { return new ite(head); }
        SERIAL* iter_replace(hickey* value) const { return (SERIAL*)value; }
        void push(hickey* value) { if (!template_check(value)) { return; } auto* v = new node(value); v->next = head->next; head->next = v; }
        void pop() { auto* v = head->next; head->next = v->next; v->next = nullptr; delete v; }
        stack() { head = new node(); }
        ~stack() override { delete head; }
        unsigned int sign() const override { return STACK; }
        bool equals(const hickey* const target) const override { if(check_conversion(target)) { return this == target; } return false; }
        int clone(hickey*& target) const override {
            if(target == nullptr) { return 0; }
            if(check_conversion(target)) {
                if(this == target) {
                    target = new stack<SERIAL>();
                    auto* tst = new stack<SERIAL>();
                    for(node* tstn = head->next; tstn != nullptr; tstn = tstn->next) {
                        auto* tss = new SERIAL();
                        tstn->value->clone(reinterpret_cast<hickey*&>(tss));
                        tst->push(tss);
                    }
                    auto* tsti = tst->iter();
                    for(;!tsti->last();) {
                        auto* tss = new SERIAL();
                        iter_replace(tsti->next())->clone(reinterpret_cast<hickey*&>(tss));
                        ((stack<SERIAL>*)target)->push(tss);
                    }
                    delete tsti;
                    delete tst;
                    return 2;
                } else {
                    delete target;
                    target = new stack<SERIAL>();
                    auto* tst = new stack<SERIAL>();
                    for(node* tstn = head; tstn->next != nullptr; tstn = tstn->next) {
                        if(tstn == head) { continue; }
                        auto* tss = new SERIAL();
                        tstn->value->clone(reinterpret_cast<hickey*&>(tss));
                        tst->push(tss);
                    }
                    auto* tsti = tst->iter();
                    for(;!tsti->last();) {
                        auto* tss = new SERIAL();
                        iter_replace(tsti->next())->clone(reinterpret_cast<hickey*&>(tss));
                        ((stack<SERIAL>*)target)->push(tss);
                    }
                    delete tsti;
                    delete tst;
                    return 1;
                }
            } else { return 0; }
        }
        int hash() const override { return 0; }
        int serialize(hickey *sys) const override {
            if(check_serialize(sys)) {
                auto* out = (system_stream*)sys;
                out->append("\n[ ");
                iterator* ite = iter();
                for(;!ite->last();) {
                    hickey* u = ite->next();
                    if(!u->equals(head->next->value)) { out->append(", "); }
                    u->serialize(out);
                }
                out->append(" ]\n");
            }
            return 1;
        }
    };
}

#endif //_CPP_FILE

#ifdef _CPP_FILE
#define _TEST_FILE
// 可通过#if false消除
// 测试用例，主要用来消除太多unused
#define KUS ({ kuu::utils::signal(); })

namespace {
    // 测试数据节点
    class user final : public kuu::hickey {
    private:
        int id;
        std::string* name;
    public:
        explicit user(int id = 0, const char* n = "") : id(id) { name = new std::string(n); }
        ~user() override { delete name; }
        unsigned int sign() const override { return 0; }
        bool equals(const hickey* const target) const override { if(check_conversion(target)) { return ((user*)target)->id == id && *((user*)target)->name == *name; } return false; }
        int hash() const override { return id; }
        int clone(hickey*& target) const override { if(target == nullptr) { return 0; } if(check_conversion(target)) { if(this == target) { target = new user(id, name->c_str()); return 2; } else { delete target; target = new user(id, name->c_str()); return 1; } } else { return 0; } }
        int serialize(hickey* sys) const override { if(check_serialize(sys)) { auto* out = replace_serialize(sys); out->append("{ 'class-name' : 'user', 'class-member' : { 'id' : %d, 'name' : '%s' }, 'direction' : 'bean' }", id, name->c_str()); return 1; } return 0; }
    };

    int testUtil() {
        auto* t = new std::string("user-name");
        KUS->hash_code(t->c_str());
        KUS->spilt(*t, "-");
        KUS->decode(KUS->encode(t->c_str()), t);
        delete t;
        return 1;
    }

    int testRedBlackTree() {
        auto* out = new kuu::system_stream(1u,1u);
        auto* rbt = new kuu::red_black_tree<user>();
        rbt->rb_insert(new user(1,"Alice"));
        rbt->rb_insert(new user(2,"Alice"));
        rbt->rb_insert(new user(3,"Alice"));
        rbt->rb_insert(new user(4,"Alice"));
        rbt->rb_insert(new user(5,"Alice"));
        rbt->serialize(out);
        out->end();
        auto* u = rbt->find(5);
        auto* uu = new user();
        u->clone(reinterpret_cast<kuu::hickey*&>(uu));
        rbt->rb_delete(u->hash());
        rbt->scanning();

        delete uu;
        delete rbt;
        delete out;
        return 1;
    }

    int testStack() {
        auto* out = new kuu::system_stream(1u,1u);
        auto* s = new kuu::stack<user>();
        s->push(new user(1,"Alice"));
        s->push(new user(2,"Alice"));
        s->push(new user(3,"Alice"));
        s->push(new user(4,"Alice"));
        s->push(new user(5,"Alice"));
        s->serialize(out);
        out->end();
        out->maybe(1u);
        s->pop();
        s->serialize(out);
        out->end();

        delete s;
        delete out;
        return 1;
    }
}

int test_system_main() {
    testUtil();
    testRedBlackTree();
    testStack();
    return 1;
}

#endif //_TEST_FILE

#endif //SYSTEM_H
