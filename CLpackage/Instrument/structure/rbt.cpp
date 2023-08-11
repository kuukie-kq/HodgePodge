#include "rbt.h"

void rbt::left_rotate(node *pivot) {
    node* right = pivot->right;
    pivot->right = right->left;
    if (right->left != nullptr) { right->left->parent = pivot; }
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

void rbt::right_rotate(node *pivot) {
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

rbt::node* rbt::parent_node(node *child) const { //NOLINT
    if(child == nullptr) { return nullptr; }
    return static_cast<node*>(child->parent);
}

void rbt::fix_after_append(node *check) {
    for (; check != nullptr && root != check && parent_node(check)->flag == color::red;) {
        if (parent_node(check) == parent_node(parent_node(check))->left) {
            node* uncle = parent_node(parent_node(check))->right;
            if (uncle != nullptr && uncle->flag == color::red) {
                uncle->flag = color::black;
                parent_node(check)->flag = color::black;
                check = parent_node(parent_node(check));
                check->flag = color::red;
            } else {
                if (check == parent_node(check)->right) {
                    check = parent_node(check);
                    left_rotate(check);
                }
                parent_node(check)->flag = color::black;
                parent_node(parent_node(check))->flag = color::red;
                right_rotate(parent_node(parent_node(check)));
            }
        } else {
            node* uncle = parent_node(parent_node(check))->left;
            if (uncle != nullptr && uncle->flag == color::red) {
                uncle->flag = color::black;
                parent_node(check)->flag = color::black;
                check = parent_node(parent_node(check));
                check->flag = color::red;
            } else {
                if (check == parent_node(check)->left) {
                    check = parent_node(check);
                    right_rotate(check);
                }
                parent_node(check)->flag = color::black;
                parent_node(parent_node(check))->flag = color::red;
                left_rotate(parent_node(parent_node(check)));
            }
        }
    }
    root->flag = color::black;
}

rbt::node* rbt::found(unsigned int value) {
    node* current = root;
    for (; current != nullptr;) {
        if (current->value > value) {
            current = current->left;
        } else if (current->value < value) {
            current = current->right;
        } else {
            break;
        }
    }
    return current;
}

rbt::node* rbt::successor(node *check) const { //NOLINT
    node* most_left = check->right;
    for (; most_left != nullptr && most_left->left != nullptr;) {
        most_left = most_left->left;
    }
    return most_left;
}

void rbt::fix_after_subtract(node *check) {
    for (; check != root && color::black == check->flag;) {
        if (check == parent_node(check)->left) {
            node* sister = parent_node(check)->right;
            if (color::red == sister->flag) {
                sister->flag = color::black;
                parent_node(check)->flag = color::red;
                left_rotate(parent_node(check));
                sister = parent_node(check)->right;
            }
            if ((sister->left == nullptr || color::black == sister->left->flag) &&
                (sister->right == nullptr || color::black == sister->right->flag)) {
                sister->flag = color::red;
                check = parent_node(check);
            } else {
                if (sister->right == nullptr || color::black == sister->right->flag) {
                    sister->left->flag = color::black;
                    sister->flag = color::red;
                    right_rotate(sister);
                    sister = parent_node(check)->right;
                }
                sister->flag = parent_node(check)->flag;
                parent_node(check)->flag = color::black;
                if (sister->right != nullptr)
                    sister->right->flag = color::black;
                left_rotate(parent_node(check));
                check = root;
            }
        } else {
            node* sister = parent_node(check)->left;
            if (color::red == sister->flag) {
                sister->flag = color::black;
                parent_node(check)->flag = color::red;
                right_rotate(parent_node(check));
                sister = parent_node(check)->left;
            }
            if ((sister->left == nullptr || color::black == sister->left->flag) &&
                (sister->right == nullptr || color::black == sister->right->flag)) {
                sister->flag = color::red;
                check = parent_node(check);
            } else {
                if (sister->left == nullptr || color::black == sister->left->flag) {
                    sister->right->flag = color::black;
                    sister->flag = color::red;
                    left_rotate(sister);
                    sister = parent_node(check)->left;
                }
                sister->flag = parent_node(check)->flag;
                if (sister->left != nullptr)
                    sister->left->flag = color::black;
                parent_node(check)->flag = color::black;
                right_rotate(parent_node(check));
                check = root;
            }
        }
    }
    check->flag = color::black;
}

void rbt::pre_order(unsigned int index, const unsigned int offset, node *order, const unsigned int level) {
    if (order == nullptr) { return; }
    index = index * 2 + offset;
    pre_order(index, 1, order->left, level + 1);
    pre_order(index, 2, order->right, level + 1);
}

int rbt::add_insert(unsigned int value, void *o) {
    if(value == 0) { if (nullptr == o) { return -2; } return -1; }
    auto* new_node = new node();
    new_node->value = value;
    new_node->object = o;
    if (root == nullptr) {
        new_node->flag = color::black;
        root = new_node;
    }

    node* current = root;
    node* temp = current;
    for (; current != nullptr;) {
        temp = current;
        if (current->value > value) {
            current = current->left;
        } else if (current->value < value) {
            current = current->right;
        } else {
            return 0;
        }
    }

    if (temp->value > value) {
        temp->left = new_node;
    } else {
        temp->right = new_node;
    }
    new_node->parent = temp;
    fix_after_append(new_node);
    return 0;
}

int rbt::sub_delete(unsigned int value) {
    node* delete_node = found(value);
    if (delete_node == nullptr) { return 0; }
    if (delete_node->left != nullptr && delete_node->right != nullptr) {
        node* temp = successor(delete_node);
        delete_node->value = temp->value;
        if (detach != nullptr) { detach(delete_node->object); delete_node->object = nullptr; }
        delete_node->object = temp->object;
        delete_node = temp;
    }
    node* replacement = delete_node->left == nullptr ? delete_node->right : delete_node->left;
    if (replacement == nullptr) {
        if (delete_node->parent == nullptr) {
            root = nullptr;
        } else {
            if (color::black == delete_node->flag) {
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
        replacement->flag = color::black;
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

    delete delete_node;
    return 0;
}

void* rbt::find(unsigned int value) {
    node* new_node = found(value);
    if (new_node == nullptr) { return nullptr; }
    return new_node->object;
}
