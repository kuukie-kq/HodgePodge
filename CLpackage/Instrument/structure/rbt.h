#ifndef INSTRUMENT_RBT_H
#define INSTRUMENT_RBT_H


class rbt {
private:
    enum class color { red = 0, black = 1}; // 可藏入指针中，因指针的地址最低2位固定为0（4字节对齐）
    struct node final {
        void* object = nullptr;
        unsigned int value = 0;
        color flag = color::red;
        node* left = nullptr;
        node* right = nullptr;
        void* parent = nullptr;
    };
    void left_rotate(node* pivot);
    void right_rotate(node* pivot);
    node* parent_node(node* child) const;
    void fix_after_append(node* check);
    node* found(unsigned int value);
    node* successor(node* check) const;
    void fix_after_subtract(node* check);
    void pre_order(unsigned int index, const unsigned int offset, node* order, const unsigned int level); //NOLINT
    node* root = nullptr;
protected:
    using object_attach = void(*)();
    using object_detach = void(*)(void*);
    object_attach attach = nullptr;
    object_detach detach = nullptr;
public:
    int add_insert(unsigned int value, void* o = nullptr);
    int sub_delete(unsigned int value);
    void* find(unsigned int value);
};


#endif //INSTRUMENT_RBT_H
