//
// Created by kuu-kie on 2022-09-28.
//

#ifndef KUU_JSON_H
#define KUU_JSON_H
//====  ====  ====  ====  ====  ====  ====  ====  ====  ====  ====
//====  ====  ====  ====  ====  ====  ====  ====  ====  ====  ====
#include <iostream> //输入输出
#include <sstream> //输入输出缓冲
#include <cstdarg> //不定参数处理
#include <chrono> //时间戳
#include <string> //字符串类
#include <vector> //不定数组，字符串分割
#include <fstream> //读写文件
//====  ====  ====  ====  ====  ====  ====  ====  ====  ====  ====
#ifdef KUU_ONLY
#undef KUU_ONLY
#endif //KUU_ONLY 源码是否为单文件
#define KUU_ONLY true

#ifdef KUU_TEST_CASE
#undef KUU_TEST_CASE
#endif //KUU_TEST_CASE 是否包含测试用例
#define KUU_TEST_CASE true
//====  ====  ====  ====  ====  ====  ====  ====  ====  ====  ====
namespace kuu {
    // typedef unsigned int u4int;
    // typedef unsigned char u1int;
    // typedef int s4int;
    // typedef char s1int;
    // 约定函数返回值最少是int其中0表示异常1表示正常其他需要enum
    enum {
        HICKEY_K = 3260681415u,
        SYSTEM_STREAM_K = 101u,
        RED_BLACK_TREE_K = 144u,
        STACK_K = 151u
    };

    class Hickey{ //NOLINT
    private:
        // 禁用拷贝构造函数
        // 禁用赋值运算符
        Hickey& operator=(Hickey&);
        Hickey(Hickey&);
        Hickey& operator=(Hickey&&) noexcept;
        Hickey(Hickey&&) noexcept;
    protected:
        // 禁用构造函数，也不算禁用，就是无法正常使用，防止产生实例
        // 如果存在纯虚函数，就产生不了实例
        Hickey();
    public:
        virtual ~Hickey();
        // 类的签名
        // 相当于java.getClass，由于类之间的关系问题，如果为static模板中还是无法直接使用，且static的情况不能使用虚函数定义，故，作为数据类来说，需要保证存在无参的构造函数
        // 可能需要再加一个签名base用于在继承中表示统一的基类，但有不同类的问题（可能需要换一种返回值类型，也是一个解决方案）
        virtual unsigned int sign() const;
        // 判断两个对象是否相等
        // 相当于java.equals
        // 继承情况下不同子类用父类的判断可能需要相等
        virtual bool equals(const Hickey* const target) const; //NOLINT
        // 克隆出一个内容一样的不同内存，注意，使用深拷贝，另外注意参数的传递，可能会出现内存无法回收的情况（自己传自己）
        // 相当于java.clone
        // 不能省，如果父类与子类逻辑一样，只是部分函数（序列化）有细微差别，不能使用父类的clone不然就子类clone完就降级成父类，无法再使用子类的虚函数了
        virtual int clone(Hickey*& target) const;
        // 对象的标识或排序规则
        // 相当于java.hashCode
        virtual int hash() const;
        // 非规范的序列化
        // 相当于java.toString
        virtual int serialize(Hickey* sys) const;
    };

    class System_Stream : public Hickey {
    protected:
        class Time_Stamp {
        private:
            std::chrono::nanoseconds start_stamp = std::chrono::nanoseconds::zero();
        public:
            Time_Stamp();
            ~Time_Stamp();
            unsigned long long time_line_passed();
            unsigned long long time_start();
            static unsigned long long time_now();
        };

        static inline unsigned int time_nano(unsigned long long stamp);
        static inline unsigned int time_milli(unsigned long long stamp);
        static inline unsigned int time_micro(unsigned long long stamp);
        static inline unsigned int time_second(unsigned long long stamp);
        static inline unsigned int time_minute(unsigned long long stamp);
        static inline unsigned int time_hour(unsigned long long stamp);// UTC+8 (GMT)
        const static int MAX_LENGTH = 1024;
        const static int BUFFER_SIZE = 1048575; // 2^20 - 1
        void upgrade(std::stringstream *sys, const char *format, ...) const;
        Time_Stamp* timer;
        unsigned int on_or_off;
        unsigned int level;
        std::stringstream* stream;
        std::stringstream* buffer;
        // 可做扩展
        virtual void step() const;
        virtual void log() const;
        virtual void warning() const;
        virtual void error() const;
    public:
        explicit System_Stream(unsigned int ooo = 1u, unsigned int mode = 0);
        ~System_Stream() override;
        void clear();
        void start(unsigned int mode);
        void maybe(unsigned int mode);
        void append(const char *format, ...) const;
        void end();
        unsigned int sign() const override;
        bool equals(const Hickey *target) const override;
        int hash() const override;
    };
    // 红黑树，需要实现hickey接口，且确保实现了hash sign serialize
    // 红黑树中的value既标识排序的字段需要用到
    template<typename SERIAL> class Red_Black_Tree final : public Hickey {
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
        enum Red_Black { RED = 0, BLACK = 1 };
        class node {
        public:
            Hickey* value;
            Red_Black color;
            node* left;
            node* right;
            void* parent;
            explicit node(Hickey* value = new SERIAL());
            ~node();
        };
        // 左旋
        void left_rotate(node* pivot);
        // 右旋
        void right_rotate(node* pivot);
        // 父节点为void*所以做一个转换
        node* parent_node(node* child) const;
        // 插入后的调整
        void fix_after_append(node* check);
        // 查找元素
        node* found(int value);
        // 查找当前节点的后继节点，既中序遍历的下一个节点
        node* successor(node* check) const;
        // 删除时的调整
        void fix_after_subtract(node* check);
        // 树放入数组中，由两个指标表示下标
        // 一个是父节点的下标，一个是父节点的左子（1）还是右子（2）
        // 既，根节点默认0，0
        // 这样父节点的下标乘以2，再加上一个数，即为本节点在数组中的下标
        inline void pre_order(unsigned int index, const unsigned int offset, node* node, const unsigned int level, System_Stream* out) const;
        node* root;
        inline bool template_check(const Hickey* const data) const; //NOLINT
    public:
        Red_Black_Tree();
        ~Red_Black_Tree() override;
        // 插入节点
        // 1）父节点是黑的，无需做处理
        // 2）父节点和叔节点为红，修改父节点和叔节点为黑色，改变祖父节点为红色
        // 3）父节点为红叔节点为黑，四种情况，有直接旋转变色和先反向旋转再旋转变色之分
        void rb_insert(Hickey* value);
        // 删除节点
        // 1）删除的节点为叶子节点，可以直接删除
        // 2）删除的节点只有一个子节点，子节点顶替
        // 3）删除的节点有两个子节点，先找其后继节点，然后复制内容，则删除的是（替身）后继节点所在的位置
        void rb_delete(int hash_value);
        // 查找节点
        SERIAL* rb_find(int hash_value);
        unsigned int sign() const override;
        int serialize(Hickey* sys) const override;
    };

    class Iterator {
    public:
        Iterator();
        virtual ~Iterator();
        virtual Hickey* next();
        virtual bool last();
    };

    class Iterable : public Hickey {
    protected:
        // 使用友元类来替代内部类的实现
        friend class iterator;
        Iterable();
    public:
        // 目前的使用方式是一个作为循环退出的条件，一个获取下一个元素，注意此返回值的类型，需要自己去回收内存
        virtual Iterator* iter() const;
        ~Iterable() override;
    };

    template<typename SERIAL> class Stack final : public Iterable {
    private:
        class node {
        public:
            Hickey* value;
            node* next;
            explicit node(Hickey* value = new SERIAL());
            ~node();
        };
        node* head;
        class ite : public Iterator {
        private:
            node* flow;
        public:
            Hickey* next() override;
            bool last() override;
            explicit ite(node* head);
            ~ite() override;
        };
        inline bool template_check(Hickey* const data) const; //NOLINT
    public:
        Iterator* iter() const override;
        SERIAL* iter_replace(Hickey* value) const;
        void push(Hickey* value);
        void pop();
        Stack();
        ~Stack() override;
        unsigned int sign() const override;
        bool equals(const Hickey* const target) const override; //NOLINT
        int clone(Hickey*& target) const override;
        int serialize(Hickey* sys) const override;
    };
}
//====  ====  ====  ====  ====  ====  ====  ====  ====  ====  ====
#if KUU_ONLY
namespace kuu {
    //====  ====  ====  ====  ====  ====  ====  ====  ====  ====
    namespace {
        class Utils final {
        private:
            Utils();
            ~Utils(); //NOLINT
            Utils &operator=(Utils&);
            Utils(const Utils&);
            Utils &operator=(Utils&&) noexcept;
            Utils(Utils&&) noexcept;
            static Utils* u;
        public:
            static Utils* signal();
            inline unsigned int hash_code(const char* key) const;
            inline std::vector<std::string> spilt(std::string str, const std::string& pattern) const;
            inline bool check_conversion(const Hickey* const mine, const Hickey* const target) const; //NOLINT
            inline bool check_serialize(const Hickey* const target) const; //NOLINT
            inline System_Stream* replace_serialize(const Hickey* const target) const; //NOLINT
        };

        Utils::Utils() = default;
        Utils::~Utils() = default;
        Utils& Utils::operator=(Utils&) = default;
        Utils::Utils(const Utils &) = default;
        Utils& Utils::operator=(Utils&&) noexcept = default;
        Utils::Utils(Utils &&) noexcept = default;
        Utils* Utils::signal() { return u; }
        unsigned int Utils::hash_code(const char* key) const{ unsigned int result; unsigned char* byte; for (result = 0, byte = (unsigned char*) key; *byte; byte++) { result = result * 31 + *byte; } return result; } //NOLINT
        std::vector<std::string> Utils::spilt(std::string str, const std::string& pattern) const { std::string::size_type pos; std::vector<std::string> result; str += pattern; unsigned int size = str.size(); for (unsigned int i = 0; i < size; i++) { pos = str.find(pattern, i); if (pos < size) { std::string s = str.substr(i, pos - i); result.push_back(s); i = pos + pattern.size() - 1; } } return result; } //NOLINT
        bool Utils::check_conversion(const Hickey *const mine, const Hickey *const target) const { return mine->sign()==target->sign(); } //NOLINT
        bool Utils::check_serialize(const Hickey* const target) const { return target->sign() == SYSTEM_STREAM_K; } //NOLINT
        System_Stream* Utils::replace_serialize(const Hickey* const target) const { if (check_serialize(target)) { return (System_Stream*)target; } return nullptr; }

        Utils* Utils::u = new Utils(); //NOLINT
#define KUSP ({ kuu::Utils::signal(); })
    }
    //====  ====  ====  ====  ====  ====  ====  ====  ====  ====
    Hickey& Hickey::operator=(Hickey&) = default;
    Hickey::Hickey(Hickey&) = default;
    Hickey& Hickey::operator=(Hickey&&) noexcept = default;
    Hickey::Hickey(Hickey&&) noexcept = default;
    Hickey::Hickey() = default;
    Hickey::~Hickey() = default;
    unsigned int Hickey::sign() const { return HICKEY_K; }
    bool Hickey::equals(const Hickey* const target) const { return this == target; }
    int Hickey::clone(Hickey*& target) const { return 0;if(target == nullptr);if(sign() == target->sign());if(equals(target));} //NOLINT
    int Hickey::hash() const { return 0; }
    int Hickey::serialize(Hickey* sys) const { return 0; }
    //====  ====  ====  ====  ====  ====  ====  ====  ====  ====
    System_Stream::Time_Stamp::Time_Stamp() { start_stamp = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()); }
    System_Stream::Time_Stamp::~Time_Stamp() { start_stamp = std::chrono::nanoseconds::zero(); }
    unsigned long long System_Stream::Time_Stamp::time_line_passed() { std::chrono::nanoseconds now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()); unsigned long long passed = now.count() - start_stamp.count(); if (passed > 0) { return (passed); } return 0; }
    unsigned long long System_Stream::Time_Stamp::time_start() { return start_stamp.count(); }
    unsigned long long System_Stream::Time_Stamp::time_now() { std::chrono::nanoseconds now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()); unsigned long long passed = now.count(); return passed; }
    unsigned int System_Stream::time_nano(unsigned long long stamp) { unsigned int re = stamp % 1000; return re; }
    unsigned int System_Stream::time_milli(unsigned long long stamp) { unsigned int re = stamp / 1000 % 1000; return re; }
    unsigned int System_Stream::time_micro(unsigned long long stamp) { unsigned int re = stamp / 1000000 % 1000; return re; }
    unsigned int System_Stream::time_second(unsigned long long stamp) { unsigned int re = stamp / 1000000000 % 60; return re; }
    unsigned int System_Stream::time_minute(unsigned long long stamp) { unsigned int re = stamp / 1000000000 / 60 % 60; return re; }
    unsigned int System_Stream::time_hour(unsigned long long stamp) { unsigned int re = stamp / 1000000000 / (60 * 60) % 24; return re + 8; }

    void System_Stream::upgrade(std::stringstream* sys, const char* format, ...) const {
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

    void System_Stream::step() const {
        if (buffer->rdbuf()->in_avail() > BUFFER_SIZE) {
            std::cout << buffer->str();
            buffer->clear();
            buffer->str("");
        }
        unsigned long long tmp = Time_Stamp::time_now();
        upgrade(buffer, "<-\t[%02d:%02d:%02d %03dms%03dus%03dns]", time_hour(tmp), time_minute(tmp), time_second(tmp), time_micro(tmp), time_milli(tmp), time_nano(tmp));
        *buffer << stream->str();
        unsigned long stamp = timer->time_line_passed();
        upgrade(buffer,"\t%llu[%d s %d ms %d us %d ns] <\n", stamp, stamp / 1000000000, time_micro(stamp), time_milli(stamp), time_nano(stamp));
    }

    void System_Stream::log() const {
        if (buffer->rdbuf()->in_avail() > 0) {
            std::cout << buffer->str();
            buffer->clear();
            buffer->str("");
        }
        unsigned long long tmp = Time_Stamp::time_now();
        upgrade(buffer, "<*\t[%02d:%02d:%02d %03dms%03dus%03dns]", time_hour(tmp), time_minute(tmp), time_second(tmp), time_micro(tmp), time_milli(tmp), time_nano(tmp));
        *buffer << stream->str();
        unsigned long stamp = timer->time_line_passed();
        upgrade(buffer,"\t%llu[%d s %d ms %d us %d ns] >\n", stamp, stamp / 1000000000, time_micro(stamp), time_milli(stamp), time_nano(stamp));
        std::cout << buffer->str();
        buffer->clear();
        buffer->str("");
    }

    void System_Stream::warning() const {
        unsigned long long tmp = Time_Stamp::time_now();
        upgrade(buffer, ">-\t[%02d:%02d:%02d %03dms%03dus%03dns]", time_hour(tmp), time_minute(tmp), time_second(tmp), time_micro(tmp), time_milli(tmp), time_nano(tmp));
        *buffer << stream->str();
        unsigned long stamp = timer->time_line_passed();
        upgrade(buffer,"\t%llu[%d s %d ms %d us %d ns] <\n", stamp, stamp / 1000000000, time_micro(stamp), time_milli(stamp), time_nano(stamp));
        std::cout << buffer->str();
        buffer->clear();
        buffer->str("");
    }

    void System_Stream::error() const {
        unsigned long long tmp = Time_Stamp::time_now();
        upgrade(buffer, ">*\t[%02d:%02d:%02d %03dms%03dus%03dns]", time_hour(tmp), time_minute(tmp), time_second(tmp), time_micro(tmp), time_milli(tmp), time_nano(tmp));
        *buffer << stream->str();
        unsigned long stamp = timer->time_line_passed();
        upgrade(buffer,"\t%llu[%d s %d ms %d us %d ns] <\n", stamp, stamp / 1000000000, time_micro(stamp), time_milli(stamp), time_nano(stamp));
        std::cerr << buffer->str();
        buffer->clear();
        buffer->str("");
    }

    System_Stream::System_Stream(unsigned int ooo, unsigned int mode) { stream = new std::stringstream(); buffer = new std::stringstream(); on_or_off = ooo; level = mode; timer = new Time_Stamp(); }
    System_Stream::~System_Stream() { delete timer; delete stream; delete buffer; }
    void System_Stream::clear() { stream->clear(); stream->str(""); level = 0; }
    void System_Stream::start(unsigned int mode) { if (stream->rdbuf()->in_avail() > 0) { clear(); } level = mode; }
    void System_Stream::maybe(unsigned int mode) { level = mode; }

    void System_Stream::append(const char* format, ...) const {
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

    void System_Stream::end() {
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

    unsigned int System_Stream::sign() const { return SYSTEM_STREAM_K; }
    bool System_Stream::equals(const Hickey* target) const { if (KUSP->check_conversion(this,target)) { return ((System_Stream*)target)->stream->str() == stream->str() && ((System_Stream*)target)->buffer->str() == buffer->str(); } return false; }
    int System_Stream::hash() const { return static_cast<int>(timer->time_start()); }
    //====  ====  ====  ====  ====  ====  ====  ====  ====  ====
    template<typename SERIAL> Red_Black_Tree<SERIAL>::node::node(Hickey* value) : value(value) { color = RED; left = nullptr; right = nullptr; parent = nullptr; }
    template<typename SERIAL> Red_Black_Tree<SERIAL>::node::~node() { delete left; delete right; delete value; }

    template<typename SERIAL> void Red_Black_Tree<SERIAL>::left_rotate(node* pivot) {
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

    template<typename SERIAL> void Red_Black_Tree<SERIAL>::right_rotate(node* pivot) {
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

    template<typename SERIAL> typename Red_Black_Tree<SERIAL>::node* Red_Black_Tree<SERIAL>::parent_node(node* child) const { if(child == nullptr) { return nullptr; } return (node*)child->parent; }

    template<typename SERIAL> void Red_Black_Tree<SERIAL>::fix_after_append(node* check) {
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

    template<typename SERIAL> typename Red_Black_Tree<SERIAL>::node* Red_Black_Tree<SERIAL>::found(int value) {
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

    template<typename SERIAL> typename Red_Black_Tree<SERIAL>::node* Red_Black_Tree<SERIAL>::successor(node* check) const {
        node* most_left = check->right;
        for (; most_left != nullptr && most_left->left != nullptr;) {
            most_left = most_left->left;
        }
        return most_left;
    }

    template<typename SERIAL> void Red_Black_Tree<SERIAL>::fix_after_subtract(node* check) {
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

    template<typename SERIAL> void Red_Black_Tree<SERIAL>::pre_order(unsigned int index, const unsigned int offset, node *node, const unsigned int level, System_Stream *out) const {
        if (node == nullptr) { return; }
        index = index * 2 + offset;

        out->append("[%4u]{level:%2u,\tcolor:%s\t,value:",
                    index, level, node->color ? "Black\0" : "Red\0");
        node->value->serialize(out);
        out->append("}\n");

        pre_order(index, 1, node->left, level + 1, out);
        pre_order(index, 2, node->right, level + 1, out);
    }

    template<typename SERIAL> bool Red_Black_Tree<SERIAL>::template_check(const Hickey *const data) const { auto* s = new SERIAL(); return s->sign() == data->sign(); }
    template<typename SERIAL> Red_Black_Tree<SERIAL>::Red_Black_Tree() { root = nullptr; }
    template<typename SERIAL> Red_Black_Tree<SERIAL>::~Red_Black_Tree() { delete root; }

    template<typename SERIAL> void Red_Black_Tree<SERIAL>::rb_insert(Hickey* value) {
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

    template<typename SERIAL> void Red_Black_Tree<SERIAL>::rb_delete(int hash_value) {
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

    template<typename SERIAL> SERIAL* Red_Black_Tree<SERIAL>::rb_find(int hash_value) {
        node* new_node = found(hash_value);
        if (new_node == nullptr) { return nullptr; }
        return (SERIAL*)new_node->value;
    }

    template<typename SERIAL> unsigned int Red_Black_Tree<SERIAL>::sign() const { return RED_BLACK_TREE_K; }
    template<typename SERIAL> int Red_Black_Tree<SERIAL>::serialize(Hickey* sys) const { if (KUSP->check_serialize(sys)) { auto* out = KUSP->replace_serialize(sys); pre_order(0u,0u,root,1u,out); return 1; } return 0; }
    //====  ====  ====  ====  ====  ====  ====  ====  ====  ====
    Iterator::Iterator() = default;
    Iterator::~Iterator() = default;
    Hickey* Iterator::next() { return nullptr; }
    bool Iterator::last() { return true; }
    //====  ====  ====  ====  ====  ====  ====  ====  ====  ====
    Iterable::Iterable() = default;
    Iterator* Iterable::iter() const { return new Iterator(); }
    Iterable::~Iterable() = default;
    //====  ====  ====  ====  ====  ====  ====  ====  ====  ====
    template<typename SERIAL> Stack<SERIAL>::node::node(Hickey* value) : value(value) { next = nullptr; }
    template<typename SERIAL> Stack<SERIAL>::node::~node() { delete next; delete value; }
    template<typename SERIAL> Hickey* Stack<SERIAL>::ite::next() { flow = flow->next; return flow->value; }
    template<typename SERIAL> bool Stack<SERIAL>::ite::last() { return flow->next == nullptr; }
    template<typename SERIAL> Stack<SERIAL>::ite::ite(node *head) : flow(head) {}
    template<typename SERIAL> Stack<SERIAL>::ite::~ite() = default;
    template<typename SERIAL> bool Stack<SERIAL>::template_check(Hickey* const data) const { return head->value->sign() == data->sign(); }
    template<typename SERIAL> Iterator* Stack<SERIAL>::iter() const { return new ite(head); }
    template<typename SERIAL> SERIAL* Stack<SERIAL>::iter_replace(Hickey* value) const { return (SERIAL*)value; }
    template<typename SERIAL> void Stack<SERIAL>::push(Hickey* value) { if (!template_check(value)) { return; } auto* v = new node(value); v->next = head->next; head->next = v; }
    template<typename SERIAL> void Stack<SERIAL>::pop() { auto* v = head->next; head->next = v->next; v->next = nullptr; delete v; }
    template<typename SERIAL> Stack<SERIAL>::Stack() { head = new node(); }
    template<typename SERIAL> Stack<SERIAL>::~Stack() { delete head; }
    template<typename SERIAL> unsigned int Stack<SERIAL>::sign() const { return STACK_K; }
    template<typename SERIAL> bool Stack<SERIAL>::equals(const Hickey* const target) const { if(KUSP->check_conversion(this,target)) { return this == target; } return false; }

    template<typename SERIAL> int Stack<SERIAL>::clone(Hickey*& target) const {
        if(target == nullptr) { return 0; }
        if(KUSP->check_conversion(this,target)) {
            if(this == target) { return 0; } else {
                delete target;
                target = new Stack<SERIAL>();
                auto* tst = new Stack<SERIAL>();
                for(node* tstn = head; tstn->next != nullptr; tstn = tstn->next) {
                    if(tstn == head) { continue; }
                    auto* tss = new SERIAL();
                    tstn->value->clone(reinterpret_cast<Hickey*&>(tss));
                    tst->push(tss);
                }
                auto* tsti = tst->iter();
                for(;!tsti->last();) {
                    auto* tss = new SERIAL();
                    iter_replace(tsti->next())->clone(reinterpret_cast<Hickey*&>(tss));
                    ((Stack<SERIAL>*)target)->push(tss);
                }
                delete tsti;
                delete tst;
                return 1;
            }
        } else { return 0; }
    }

    template<typename SERIAL> int Stack<SERIAL>::serialize(Hickey* sys) const {
        if(KUSP->check_serialize(sys)) {
            auto* out = KUSP->replace_serialize(sys);
            out->append("\n[\n");
            Iterator* ite = iter();
            for(;!ite->last();) {
                Hickey* u = ite->next();
                if(!u->equals(head->next->value)) { out->append(", "); }
                u->serialize(out);
            }
            out->append("\n]\n");
        }
        return 1;
    }
    //====  ====  ====  ====  ====  ====  ====  ====  ====  ====
}
#endif //true false KUU_ONLY
//====  ====  ====  ====  ====  ====  ====  ====  ====  ====  ====
namespace kuu {
    namespace json {
        enum Code_K {
            MAP = 1010u,
            LIST = 1011u,
            LIST_OBJECT = 1013u,
            LIST_ARRAY = 1014u,
            OBJECT = 1020u,
            INT = 1021u,
            DOUBLE = 1025u,
            STRING = 1028u,
            Key_Value = 1031u
        };

        class Object_K : public kuu::Hickey {
        public:
            Object_K();
            ~Object_K() override;
            unsigned int sign() const override;
        };

        class Int_K final : public Object_K {
        private:
            int value;
        public:
            explicit Int_K(const int value = 0); //NOLINT
            ~Int_K() override;
            void set(const int val); //NOLINT
            int get() const;
            unsigned int sign() const override;
            bool equals(const Hickey* const target) const override; //NOLINT
            int clone(Hickey*& target) const override;
            int hash() const override;
            int serialize(Hickey* sys) const override;
        };

        class Double_K final : public Object_K {
        private:
            double value;
        public:
            explicit Double_K(const double value = 0); //NOLINT
            ~Double_K() override;
            void set(const double val); //NOLINT
            double get() const;
            unsigned int sign() const override;
            bool equals(const Hickey* const target) const override; //NOLINT
            int clone(Hickey*& target) const override;
            int hash() const override;
            int serialize(Hickey* sys) const override;
        };

        class String_K final : public Object_K {
        private:
            std::string* value;
        public:
            explicit String_K(const char* val = "");
            ~String_K() override;
            void set(const char* val);
            std::string* get() const;
            unsigned int sign() const override;
            bool equals(const Hickey* const target) const override; //NOLINT
            int clone(Hickey*& target) const override;
            int hash() const override;
            int serialize(Hickey* sys) const override;
        };

        template<typename KEY, typename VALUE> class Key_Value_K final : public Object_K {
        private:
            Hickey* key;
            Hickey* value;
        public:
            explicit Key_Value_K(KEY* key = new KEY(), VALUE* value = nullptr);
            ~Key_Value_K() override;
            KEY* get_key();
            VALUE* get_value();
            unsigned int sign() const override;
            bool equals(const Hickey* const target) const override; //NOLINT
            int clone(Hickey*& target) const override;
            int hash() const override;
            int serialize(Hickey* sys) const override;
        };

        template<typename KEY_VALUE> class Map_K : public Object_K {
        private:
            Red_Black_Tree<KEY_VALUE>* mapper;
        public:
            Map_K();
            ~Map_K() override;
            int m_insert(KEY_VALUE* value);
            int m_delete(KEY_VALUE* value);
            KEY_VALUE* m_find(KEY_VALUE* value);
            unsigned int sign() const override;
            int serialize(Hickey *sys) const override;
        };

        template<typename KEY,typename VALUE> class Map_V_K final {
        private:
            Map_K<Key_Value_K<KEY,VALUE>>* mapper;
        public:
            Map_V_K();
            ~Map_V_K();
            int m_insert(KEY* key, VALUE* value);
            int m_delete(KEY* key);
            VALUE* m_find(KEY* key);
        };

        template<typename SERIAL> class List_K : public Iterable {
        protected:
            class node {
            public:
                Hickey* value;
                node* next;
                node();
                ~node();
            };
            node* head;
            class ite : public Iterator {
            public:
                node* flow;
                explicit ite(node* flow = new node());
                ~ite() override;
                bool last() override;
                Hickey* next() override;
            };
        public:
            Iterator* iter() const override;
            List_K();
            ~List_K() override;
            int l_insert(SERIAL* value);
            int l_delete(int hash_value);
            SERIAL* l_find(int hash_value);
            unsigned int sign() const override;
            bool equals(const Hickey* const target) const override; //NOLINT
            int clone(Hickey*& target) const override;
        };

        template<typename SERIAL> class L_Array_K final : public List_K<SERIAL> {
        public:
            unsigned int sign() const override;
            int clone(Hickey*& target) const override;
            int hash() const override;
            int serialize(Hickey* sys) const override;
        };

        template<typename SERIAL> class L_Object_K final : public List_K<SERIAL> {
        public:
            unsigned int sign() const override;
            int clone(Hickey*& target) const override;
            int hash() const override;
            int serialize(Hickey* sys) const override;
        };
    }
}
//====  ====  ====  ====  ====  ====  ====  ====  ====  ====  ====
#if KUU_ONLY
namespace kuu {
    namespace json {
        //====  ====  ====  ====  ====  ====  ====  ====  ====
        Object_K::Object_K() = default;

        Object_K::~Object_K() = default;

        unsigned int Object_K::sign() const { return Code_K::OBJECT; }

        //====  ====  ====  ====  ====  ====  ====  ====  ====
        Int_K::Int_K(const int value) : value(value) {}

        Int_K::~Int_K() = default;

        void Int_K::set(const int val) { value = val; }

        int Int_K::get() const { return value; }

        unsigned int Int_K::sign() const { return Code_K::INT; }

        bool Int_K::equals(const Hickey *const target) const {
            if (KUSP->check_conversion(this, target)) {
                return value == ((Int_K *) target)->get();
            }
            return false;
        }

        int Int_K::clone(Hickey *&target) const {
            if (target != nullptr) {
                //类型检查有问题
                // if (KUSP->check_conversion(this, target)) {
                    if (target == this) {
                        target = new Int_K(value);
                        return 2;
                    }
                    else {
                        delete target;
                        target = new Int_K(value);
                        return 1;
                    }
                // }
                // return 0;
            }
            return 0;
        }

        int Int_K::hash() const { return value; }

        int Int_K::serialize(Hickey *sys) const {
            if (!KUSP->check_serialize(sys)) return 0;
            auto *out = KUSP->replace_serialize(sys);
            out->append("%d", value);
            return 1;
        }

        //====  ====  ====  ====  ====  ====  ====  ====  ====
        Double_K::Double_K(const double value) : value(value) {}

        Double_K::~Double_K() = default;

        void Double_K::set(const double val) { value = val; }

        double Double_K::get() const { return value; }

        unsigned int Double_K::sign() const { return Code_K::DOUBLE; }

        bool Double_K::equals(const Hickey *const target) const {
            if (KUSP->check_conversion(this, target)) {
                return value == ((Double_K *) target)->get();
            }
            return false;
        }

        int Double_K::clone(Hickey *&target) const {
            if (target != nullptr) {
                //类型检查有问题
                // if (KUSP->check_conversion(this, target)) {
                    if (target == this) {
                        target = new Double_K(value);
                        return 2;
                    }
                    else {
                        delete target;
                        target = new Double_K(value);
                        return 1;
                    }
                // }
                // return 0;
            }
            return 0;
        }

        int Double_K::hash() const { return (int) value; }

        int Double_K::serialize(Hickey *sys) const {
            if (!KUSP->check_serialize(sys)) return 0;
            auto *out = KUSP->replace_serialize(sys);
            out->append("%f", value);
            return 1;
        }

        //====  ====  ====  ====  ====  ====  ====  ====  ====
        String_K::String_K(const char *val) { value = new std::string(val); }

        String_K::~String_K() { delete value; }

        void String_K::set(const char *val) {
            value->clear();
            value->append(val);
        }

        std::string *String_K::get() const { return value; }

        unsigned int String_K::sign() const { return Code_K::STRING; }

        bool String_K::equals(const Hickey *const target) const {
            if (KUSP->check_conversion(this, target)) {
                return *value == *((String_K *) target)->get();
            }
            return false;
        }

        int String_K::clone(Hickey *&target) const {
            if (target != nullptr) {
                //类型检查有问题
                // if (KUSP->check_conversion(this, target)) {
                    if (target == this) {
                        target = new String_K(value->c_str());
                        return 2;
                    }
                    else {
                        delete target;
                        target = new String_K(value->c_str());
                        return 1;
                    }
                // }
                // return 0;
            }
            return 0;
        }

        int String_K::hash() const { return (int) KUSP->hash_code(value->c_str()); }

        int String_K::serialize(Hickey *sys) const {
            if (!KUSP->check_serialize(sys)) return 0;
            auto *out = KUSP->replace_serialize(sys);
            out->append("\"%s\"", value->c_str());
            return 1;
        }

        //====  ====  ====  ====  ====  ====  ====  ====  ====
        template<typename KEY, typename VALUE>
        Key_Value_K<KEY, VALUE>::Key_Value_K(KEY *key, VALUE *value) : key(key), value(value) {}

        template<typename KEY, typename VALUE>
        Key_Value_K<KEY, VALUE>::~Key_Value_K() {
            delete key;
            delete value;
        }

        template<typename KEY, typename VALUE>
        KEY *Key_Value_K<KEY, VALUE>::get_key() { return (KEY *) key; }

        template<typename KEY, typename VALUE>
        VALUE *Key_Value_K<KEY, VALUE>::get_value() { return (VALUE *) value; }

        template<typename KEY, typename VALUE>
        unsigned int Key_Value_K<KEY, VALUE>::sign() const { return Code_K::Key_Value; }

        template<typename KEY, typename VALUE>
        bool Key_Value_K<KEY, VALUE>::equals(const Hickey *const target) const {
            if (KUSP->check_conversion(this, target)) {
                return key->equals(((Key_Value_K *) target)->get_key()) &&
                       value->equals(((Key_Value_K *) target)->get_value());
            }
            return false;
        }

        template<typename KEY, typename VALUE>
        int Key_Value_K<KEY, VALUE>::clone(Hickey *&target) const {
            if (target != nullptr) {
                if (KUSP->check_conversion(this, target)) {
                    if (target == this) { return 0; }
                    else {
                        auto *k = new KEY();
                        Hickey* v = new Object_K();
                        switch (value->sign()) {
                            case Code_K::LIST:
                                delete v;
                                switch (value->hash()) {
                                    case Code_K::LIST_OBJECT:
                                        v = new L_Object_K<Key_Value_K<KEY,VALUE>>();
                                        break;
                                    case Code_K::LIST_ARRAY:
                                        v = new L_Array_K<Key_Value_K<KEY,VALUE>>();
                                        break;
                                    default:
                                        v = new Object_K();
                                }
                            default:
                                break;
                        }
                        key->clone(reinterpret_cast<Hickey *&>(k));
                        value->clone(reinterpret_cast<Hickey *&>(v));
                        delete target;
                        target = new Key_Value_K<KEY, VALUE>(k, (VALUE*)v);
                        return 1;
                    }
                }
                return 0;
            }
            return 0;
        }

        template<typename KEY, typename VALUE>
        int Key_Value_K<KEY, VALUE>::hash() const { return key->hash(); }

        template<typename KEY, typename VALUE>
        int Key_Value_K<KEY, VALUE>::serialize(Hickey *sys) const {
            if (!KUSP->check_serialize(sys)) return 0;
            auto *out = KUSP->replace_serialize(sys);
            key->serialize(out);
            out->append(":");
            if (value->sign() == Code_K::LIST) {
                if (value->hash() == Code_K::LIST_OBJECT) {
                    ((L_Object_K<Key_Value_K<KEY,VALUE>>*)value)->serialize(out);
                } else if (value->hash() == Code_K::LIST_ARRAY) {
                    ((L_Array_K<Key_Value_K<KEY,VALUE>>*)value)->serialize(out);
                }
            } else {
                value->serialize(out);
            }
            return 1;
        }

        //====  ====  ====  ====  ====  ====  ====  ====  ====
        template<typename KEY_VALUE>
        Map_K<KEY_VALUE>::Map_K() { mapper = new Red_Black_Tree<KEY_VALUE>(); }

        template<typename KEY_VALUE>
        Map_K<KEY_VALUE>::~Map_K() { delete mapper; }

        template<typename KEY_VALUE>
        int Map_K<KEY_VALUE>::m_insert(KEY_VALUE *value) {
            mapper->rb_insert(value);
            return 1;
        }

        template<typename KEY_VALUE>
        int Map_K<KEY_VALUE>::m_delete(KEY_VALUE *value) {
            auto *kv = mapper->rb_find(value->get_key()->hash());
            mapper->rb_delete(kv->get_key()->hash());
            return 1;
        }

        template<typename KEY_VALUE>
        KEY_VALUE *Map_K<KEY_VALUE>::m_find(KEY_VALUE *value) { return mapper->rb_find(value->get_key()->hash()); }

        template<typename KEY_VALUE>
        unsigned int Map_K<KEY_VALUE>::sign() const { return Code_K::MAP; }

        template<typename KEY_VALUE>
        int Map_K<KEY_VALUE>::serialize(Hickey *sys) const {
            if (!KUSP->check_serialize(sys)) return 0;
            auto *out = KUSP->replace_serialize(sys);
            mapper->serialize(out);
            return 1;
        }

        //====  ====  ====  ====  ====  ====  ====  ====  ====
        template<typename KEY, typename VALUE>
        Map_V_K<KEY, VALUE>::Map_V_K() { mapper = new Map_K<Key_Value_K<KEY, VALUE>>(); }

        template<typename KEY, typename VALUE>
        Map_V_K<KEY, VALUE>::~Map_V_K() { delete mapper; }

        template<typename KEY, typename VALUE>
        int Map_V_K<KEY, VALUE>::m_insert(KEY *key, VALUE *value) {
            return mapper->m_insert(new Key_Value_K<KEY, VALUE>(key, value));
        }

        template<typename KEY, typename VALUE>
        int Map_V_K<KEY, VALUE>::m_delete(KEY *key) {
            auto *kv = new Key_Value_K<KEY, VALUE>(key);
            mapper->m_delete(kv);
            delete kv;
            return 1;
        }

        template<typename KEY, typename VALUE>
        VALUE *Map_V_K<KEY, VALUE>::m_find(KEY *key) {
            auto *kv = new Key_Value_K<KEY, VALUE>(key);
            auto *v = mapper->m_find(kv);
            delete kv;
            return v->get_value();
        }

        //====  ====  ====  ====  ====  ====  ====  ====  ====
        template<typename SERIAL>
        List_K<SERIAL>::node::node() {
            value = nullptr;
            next = nullptr;
        }

        template<typename SERIAL>
        List_K<SERIAL>::node::~node() {
            delete value;
            delete next;
        }

        template<typename SERIAL>
        List_K<SERIAL>::ite::ite(node *flow) : flow(flow) {}

        template<typename SERIAL>
        List_K<SERIAL>::ite::~ite() = default;

        template<typename SERIAL>
        bool List_K<SERIAL>::ite::last() { return flow->next == nullptr; }

        template<typename SERIAL>
        Hickey *List_K<SERIAL>::ite::next() {
            flow = flow->next;
            return flow->value;
        }

        template<typename SERIAL>
        Iterator *List_K<SERIAL>::iter() const { return new ite(head); }

        template<typename SERIAL>
        List_K<SERIAL>::List_K() { head = new node(); }

        template<typename SERIAL>
        List_K<SERIAL>::~List_K() { delete head; }

        template<typename SERIAL>
        int List_K<SERIAL>::l_insert(SERIAL *value) {
            ite *it = (ite *) iter();
            node *lt = it->flow;
            for (; !it->last();) {
                it->next();
                lt = it->flow;
            }
            lt->next = new node();
            lt->next->value = value;
            return 1;
        }

        template<typename SERIAL>
        int List_K<SERIAL>::l_delete(int hash_value) {
            ite *it = (ite *) iter();
            node *v = nullptr;
            node *d = nullptr;
            for (; !it->last();) {
                v = it->flow;
                it->next();
                d = it->flow;
                if (d->value->hash() == hash_value) { break; }
            }
            v->next = d->next;
            d->next = nullptr;
            delete d;
        }

        template<typename SERIAL>
        SERIAL *List_K<SERIAL>::l_find(int hash_value) {
            ite *it = (ite *) iter();
            for (; !it->last();) {
                auto *v = it->next();
                if (v->hash() == hash_value) { return (SERIAL *) v; }
            }
            return nullptr;
        }

        template<typename SERIAL>
        unsigned int List_K<SERIAL>::sign() const { return Code_K::LIST; }

        template<typename SERIAL>
        bool List_K<SERIAL>::equals(const Hickey *const target) const {
            if (KUSP->check_conversion(this, target)) {
                Iterator *itt = iter();
                Iterator *itg = ((List_K<SERIAL> *) target)->iter();
                for (; !itt->last() && !itg->last();) { if (!itt->next()->equals(itg->next())) { return false; }}
                return itt->last() ? itg->last() : false;
            }
            return false;
        }

        template<typename SERIAL>
        int List_K<SERIAL>::clone(Hickey *&target) const {
            if (target != nullptr) {
                if (KUSP->check_conversion(this, target)) {
                    if (target == this) { return 0; }
                    else {
                        delete target;
                        target = new List_K<SERIAL>();
                        Iterator *it = iter();
                        for (; !it->last();) {
                            auto *i = new SERIAL();
                            auto* t = (SERIAL*)it->next();
                            t->clone(reinterpret_cast<Hickey *&>(i));
                            ((List_K<SERIAL> *) target)->l_insert(i);
                        }
                        return 1;
                    }
                }
                return 0;
            }
            return 0;
        }

        //====  ====  ====  ====  ====  ====  ====  ====  ====
        template<typename SERIAL>
        unsigned int L_Array_K<SERIAL>::sign() const { return Code_K::LIST; }

        template<typename SERIAL>
        int L_Array_K<SERIAL>::clone(Hickey *&target) const {
            if (target != nullptr) {
                if (KUSP->check_conversion(this, target)) {
                    if (target == this) { return 0; }
                    else {
                        delete target;
                        target = new L_Array_K<SERIAL>();
                        Iterator *it = List_K<SERIAL>::iter();
                        for (; !it->last();) {
                            auto *i = new SERIAL();
                            auto* t = (SERIAL*)it->next();
                            t->clone(reinterpret_cast<Hickey *&>(i));
                            ((L_Array_K<SERIAL> *) target)->l_insert(i);
                        }
                        return 1;
                    }
                }
                return 0;
            }
            return 0;
        }

        template<typename SERIAL>
        int L_Array_K<SERIAL>::hash() const { return Code_K::LIST_ARRAY; }

        template<typename SERIAL>
        int L_Array_K<SERIAL>::serialize(Hickey *sys) const {
            if (!KUSP->check_serialize(sys)) return 0;
            auto *out = KUSP->replace_serialize(sys);
            out->append("[");
            Iterator *it = List_K<SERIAL>::iter();
            for (int i = 0; !it->last(); i++) {
                if (i != 0) { out->append(","); }
                it->next()->serialize(out);
            }
            out->append("]");
            return 1;
        }

        //====  ====  ====  ====  ====  ====  ====  ====  ====
        template<typename SERIAL>
        unsigned int L_Object_K<SERIAL>::sign() const { return Code_K::LIST; }

        template<typename SERIAL>
        int L_Object_K<SERIAL>::clone(Hickey *&target) const {
            if (target != nullptr) {
                if (KUSP->check_conversion(this, target)) {
                    if (target == this) { return 0; }
                    else {
                        delete target;
                        target = new L_Object_K<SERIAL>();
                        Iterator *it = List_K<SERIAL>::iter();
                        for (; !it->last();) {
                            auto *i = new SERIAL();
                            auto* t = (SERIAL*)it->next();
                            t->clone(reinterpret_cast<Hickey *&>(i));
                            ((L_Object_K<SERIAL> *) target)->l_insert(i);
                        }
                        return 1;
                    }
                }
                return 0;
            }
            return 0;
        }

        template<typename SERIAL>
        int L_Object_K<SERIAL>::hash() const { return Code_K::LIST_OBJECT; }

        template<typename SERIAL>
        int L_Object_K<SERIAL>::serialize(Hickey *sys) const {
            if (!KUSP->check_serialize(sys)) return 0;
            auto *out = KUSP->replace_serialize(sys);
            out->append("{");
            Iterator *it = List_K<SERIAL>::iter();
            for (int i = 0; !it->last(); i++) {
                if (i != 0) { out->append(","); }
                ((SERIAL*)it->next())->serialize(out);
            }
            out->append("}");
            return 1;
        }
        //====  ====  ====  ====  ====  ====  ====  ====  ====
        int analysis(const std::string &json_string, L_Object_K<Key_Value_K<Object_K, Hickey>> *json_object) {
            //初始化
            std::string::const_iterator cit = json_string.begin();
            int level = 0;
            auto* stack = new Stack<String_K>();
            String_K* top = nullptr;
            List_K<Key_Value_K<Object_K,Hickey>>* object = json_object;
            auto* stack_object = new Stack<List_K<Key_Value_K<Object_K,Hickey>>>();
            auto* stack_string = new Stack<String_K>();
            stack_object->push(json_object);
            stack_string->push(new String_K("main"));
            bool mode_string = false;
            bool key_or_value = true;
            Object_K* str_kv[2];
            str_kv[0] = nullptr;
            str_kv[1] = nullptr;
            int type = Code_K::INT;
            std::string str;
            str.clear();
            //分析
            for(;cit != json_string.end();) {
                if (mode_string) { if ('"' == *cit) { mode_string = false; type = Code_K::STRING; } else { str.push_back(*cit); } } else {
                    if (' ' == *cit) {} else if ('"' == *cit) {
                        mode_string = true;
                    } else if (':' == *cit) {
                        if (!(key_or_value && type == Code_K::STRING)) { return 0; }
                        str_kv[0] = new String_K(str.c_str());
                        key_or_value = false;
                        str.clear();
                        type = Code_K::INT;
                    } else if ('.' == *cit) {
                        if (type != Code_K::INT) { return 0; }
                        type = Code_K::DOUBLE;
                        str.push_back(*cit);
                    } else if (',' == *cit) {
                        if (str.empty() && key_or_value) {
                            auto* tmp_object = new List_K<Key_Value_K<Object_K,Hickey>>();
                            str_kv[0] = new String_K();
                            auto* ite = stack_string->iter();
                            auto* iter = stack_object->iter();
                            if (iter->next()->hash() == Code_K::LIST_OBJECT) {
                                delete tmp_object;
                                tmp_object = new L_Object_K<Key_Value_K<Object_K,Hickey>>();
                            } else if (iter->next()->hash() == Code_K::LIST_ARRAY) {
                                delete tmp_object;
                                tmp_object = new L_Array_K<Key_Value_K<Object_K,Hickey>>();
                            }
                            delete iter;
                            iter = stack_object->iter();
                            for(;!ite->last();) { ite->next()->clone(reinterpret_cast<Hickey*&>(str_kv[0])); iter->next()->clone(reinterpret_cast<Hickey*&>(tmp_object)); break; }
                            delete ite;
                            delete iter;
                            stack_object->pop();
                            stack_string->pop();
                            object->l_insert(new Key_Value_K<Object_K, Hickey>(str_kv[0], tmp_object));
                            tmp_object = nullptr;
                        } else {
                            switch (type) {
                                case Code_K::STRING:
                                    str_kv[1] = new String_K(str.c_str());
                                    break;
                                case Code_K::INT:
                                    str_kv[1] = new Int_K(atoi(str.c_str())); //NOLINT
                                    break;
                                case Code_K::DOUBLE:
                                    str_kv[1] = new Double_K(atof(str.c_str())); //NOLINT
                                    break;
                                default:
                                    return 0;
                            }
                            object->l_insert(new Key_Value_K<Object_K,Hickey>(str_kv[0],str_kv[1]));
                        }
                        key_or_value = true;
                        str.clear();
                        type = Code_K::INT;
                        str_kv[0] = nullptr;
                        str_kv[1] = nullptr;
                    } else if ('{' == *cit) {
                        level = level + 1;
                        if (level != 1 && !key_or_value) {
                            str.clear();
                            auto* lok = new L_Object_K<Key_Value_K<Object_K,Hickey>>();
                            stack_object->push(lok);
                            object = lok;
                            stack_string->push(str_kv[0]);
                            str_kv[0] = nullptr;
                            str_kv[1] = nullptr;
                            key_or_value = true;
                        }
                        std::string s = std::to_string(level);
                        s.append("<{>");
                        stack->push(new String_K(s.c_str()));
                        auto* ite = stack->iter();
                        top = (String_K*)ite->next();
                        delete ite;
                        if (!String_K(s.c_str()).equals(top)) { return 0; }
                    } else if ('}' == *cit) {
                        std::string s = std::to_string(level);
                        s.append("<{>");
                        if (str.empty() && key_or_value) {
                            auto* tmp_object = new List_K<Key_Value_K<Object_K,Hickey>>();
                            str_kv[0] = new String_K();
                            auto* ite = stack_string->iter();
                            auto* iter = stack_object->iter();
                            for(;!ite->last();) { ite->next()->clone(reinterpret_cast<Hickey*&>(str_kv[0])); iter->next()->clone(reinterpret_cast<Hickey*&>(tmp_object)); break; }
                            delete ite;
                            delete iter;
                            stack_object->pop();
                            stack_string->pop();
                            object->l_insert(new Key_Value_K<Object_K,Hickey>(str_kv[0],tmp_object));
                        } else {
                            switch (type) {
                                case Code_K::STRING:
                                    str_kv[1] = new String_K(str.c_str());
                                    break;
                                case Code_K::INT:
                                    str_kv[1] = new Int_K(atoi(str.c_str())); //NOLINT
                                    break;
                                case Code_K::DOUBLE:
                                    str_kv[1] = new Double_K(atof(str.c_str())); //NOLINT
                                    break;
                                default:
                                    return 0;
                            }
                            object->l_insert(new Key_Value_K<Object_K,Hickey>(str_kv[0],str_kv[1]));
                        }
                        key_or_value = true;
                        str.clear();
                        type = Code_K::INT;
                        str_kv[0] = nullptr;
                        str_kv[1] = nullptr;
                        if (!String_K(s.c_str()).equals(top)) { return 0; }
                        level = level - 1;
                        stack->pop();
                        auto* ites = stack->iter();
                        for(;!ites->last();) { top = (String_K*)ites->next(); break; }
                        delete ites;
                        if (level == 0) { if ((cit + 1) != json_string.end()) { return 0; } } else {
                            auto* item = stack_object->iter();
                            item->next();
                            auto* ito = item->next();
                            delete item;
                            if(ito->sign() != Code_K::LIST) { return 0; }
                            object = (List_K<Key_Value_K<Object_K, Hickey>>*)ito;
                        }
                    } else if ('[' == *cit) {
                    level = level + 1;
                    if (level != 1 && !key_or_value) {
                        str.clear();
                        auto* lok = new L_Array_K<Key_Value_K<Object_K,Hickey>>();
                        stack_object->push(lok);
                        object = lok;
                        stack_string->push(str_kv[0]);
                        str_kv[0] = nullptr;
                        str_kv[1] = nullptr;
                        key_or_value = true;
                    }
                    std::string s = std::to_string(level);
                    s.append("<[>");
                    stack->push(new String_K(s.c_str()));
                    auto* ite = stack->iter();
                    top = (String_K*)ite->next();
                    delete ite;
                    if (!String_K(s.c_str()).equals(top)) { return 0; }
                } else if (']' == *cit) {
                    std::string s = std::to_string(level);
                    s.append("<[>");
                    if (str.empty() && key_or_value) {
                        auto* tmp_object = new List_K<Key_Value_K<Object_K,Hickey>>();
                        str_kv[0] = new String_K();
                        auto* ite = stack_string->iter();
                        auto* iter = stack_object->iter();
                        for(;!ite->last();) { ite->next()->clone(reinterpret_cast<Hickey*&>(str_kv[0])); iter->next()->clone(reinterpret_cast<Hickey*&>(tmp_object)); break; }
                        delete ite;
                        delete iter;
                        stack_object->pop();
                        stack_string->pop();
                        object->l_insert(new Key_Value_K<Object_K,Hickey>(str_kv[0],tmp_object));
                    } else {
                        switch (type) {
                            case Code_K::STRING:
                                str_kv[1] = new String_K(str.c_str());
                                break;
                            case Code_K::INT:
                                str_kv[1] = new Int_K(atoi(str.c_str())); //NOLINT
                                break;
                            case Code_K::DOUBLE:
                                str_kv[1] = new Double_K(atof(str.c_str())); //NOLINT
                                break;
                            default:
                                return 0;
                        }
                        object->l_insert(new Key_Value_K<Object_K,Hickey>(str_kv[0],str_kv[1]));
                    }
                    key_or_value = true;
                    str.clear();
                    type = Code_K::INT;
                    str_kv[0] = nullptr;
                    str_kv[1] = nullptr;
                    if (!String_K(s.c_str()).equals(top)) { return 0; }
                    level = level - 1;
                    stack->pop();
                    auto* ites = stack->iter();
                    for(;!ites->last();) { top = (String_K*)ites->next(); break; }
                    delete ites;
                    if (level == 0) { if ((cit + 1) != json_string.end()) { return 0; } } else {
                        auto* item = stack_object->iter();
                        item->next();
                        auto* ito = item->next();
                        delete item;
                        if(ito->sign() != Code_K::LIST) { return 0; }
                        object = (List_K<Key_Value_K<Object_K, Hickey>>*)ito;
                    }
                } else {
                        str.push_back(*cit);
                    }
                }
                cit++;
            }
            //回收
            delete stack;
            top = nullptr;
            object = nullptr;
            str_kv[0] = nullptr;
            str_kv[1] = nullptr;
            stack_object = nullptr;//不能回收但需要回收
            stack_string = nullptr;//不能回收但需要回收
            return 1;
        }
    }
}
#endif //true false KUU_ONLY
//====  ====  ====  ====  ====  ====  ====  ====  ====  ====  ====
#if KUU_TEST_CASE
namespace kuu {
    namespace json {
        int test() {
            auto* jo = new L_Object_K<Key_Value_K<Object_K,Hickey>>();
            int rst = analysis("{\"id\":{\"client\":1769477,\"expire\":165787.0099},\"token\":[\"id\":{\"name\":\"alice\"},\"id\":{\"name\":\"pop\"}]}", jo);
            auto* out = new System_Stream(1u,1u);
            jo->serialize(out);
            out->end();
            delete jo;
            delete out;
            return 1;
        }
    }
}

int run_test_case_or_example() {
    kuu::json::test();
    return 0;
}
#endif //true false KUU_TEST_CASE
//====  ====  ====  ====  ====  ====  ====  ====  ====  ====  ====
#endif //KUU_JSON_H
