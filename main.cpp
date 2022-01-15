//解释器 与 CPU连用
//#include <iostream>
//#include <string>
//#include <vector>
//
//using namespace std;
//
////字符串分割函数
//vector<string> split(string str,string pattern) {
//    string::size_type pos;
//    vector<string> result;
//    str+=pattern;  //扩展字符串以方便操作
//    int size=str.size();
//    for(int i=0;i<size;i++) {
//        pos=str.find(pattern,i);
//        if(pos<size) {
//            string s=str.substr(i,pos-i);
//            result.push_back(s);
//            i=pos+pattern.size()-1;
//        }
//    }
//    return result;
//}
//
////语法树
//class WordTree {
//public:
//    bool chunkStart,chunkEnd;//语句块开始结束
//    bool big,small,same;//大于小于等于
//    bool jump,branch;//分支
//    bool multiply,divide;//乘除
//    bool add,subtract;//加减
//    bool input,output;//输入输出
//public:
//    WordTree() {
//        chunkStart = chunkEnd = false;
//        big = small = same = false;
//        jump = branch = false;
//        multiply = divide = false;
//        add = subtract = false;
//        input = output = false;
//    }
//};
//
////语句列表（仅一行）
//class Takes {
//private:
//    string data;
//    Takes* next;
//public:
//    Takes() {
//        data = "";
//        next = nullptr;
//    }
//
//    Takes(string data) {
//        this->data = data.append("");
//        next = nullptr;
//    }
//    Takes(string data,Takes* next) {
//        this->data = data.append("");
//        this->next = next;
//    }
//    void setNext(Takes* t) {
//        next = t;
//    }
//    Takes* getNext() {
//        return next;
//    }
//    void setData(string data) {
//        this->data = data;
//    }
//    string getData() {
//        return data;
//    }
//};
//
////语法检测
//class Token {
//private:
//    WordTree* tree;
//public:
//    Token() {
//        tree = new WordTree();
//    }
//
//    void translation(string c) {
//        if (c == "<*>") {
//            tree->multiply = true;
//        } else if (c == "</>") {
//            tree->divide = true;
//        } else if (c == "<+>") {
//            tree->add = true;
//        } else if (c == "<->") {
//            tree->subtract = true;
//        } else if (c == "<-") {
//            tree->input = true;
//        } else if (c == "->") {
//            tree->output = true;
//        } else if (c == ">>>") {
//            tree->chunkStart = true;
//        } else if (c == "<<<") {
//            tree->chunkEnd = true;
//        } else if (c == "<?>") {
//            tree->branch = true;
//        } else if (c == "<>>") {
//            tree->jump = true;
//        } else if (c == "-<-") {
//            tree->small = true;
//        } else if (c == "->-") {
//            tree->big = true;
//        } else if (c == "-=-") {
//            tree->same = true;
//        } else {
//
//        }
//    }
//
//    bool getChunkStart() {
//        return tree->chunkStart;
//    }
//
//    bool getChunkEnd() {
//        return tree->chunkEnd;
//    }
//
//    bool getBranch() {
//        return tree->branch;
//    }
//
//    bool getBig() {
//        return  tree->big;
//    }
//
//    bool getSmall() {
//        return tree->small;
//    }
//
//    bool getSame() {
//        return tree->same;
//    }
//
//    bool getJump() {
//        return tree->jump;
//    }
//
//    bool getMultiply() {
//        return tree->multiply;
//    }
//
//    bool getDivide() {
//        return tree->divide;
//    }
//
//    bool getAdd() {
//        return tree->add;
//    }
//
//    bool getSubtract() {
//        return tree->subtract;
//    }
//
//    bool getInput() {
//        return tree->input;
//    }
//
//    bool getOutput() {
//        return tree->output;
//    }
//};
//
////变量寄存器
//class VariableMap {
//public:
//    string mapKey;
//    string mapValue;
//    VariableMap* mapNext;
//public:
//    VariableMap() {
//        mapKey = "";
//        mapValue = "";
//        mapNext = nullptr;
//    }
//};
//
////代码寄存器
//class CodeMap {
//public:
//    string mapName;
//    string mapMessage;
//    CodeMap* mapNext;
//public:
//    CodeMap() {
//        mapName = "";
//        mapMessage = "";
//        mapNext = nullptr;
//    }
//};
//
////对外运行
//class Interpreter {
//private:
//    string data;
//    VariableMap* map;
//public:
//    Interpreter() {
//        data = "main >>>\n"
//               "\t a <- 1\n"
//               "\t b <- 2\n"
//               "\t a <+> b ->\n"
//               "main <<<\n"
//               "c <- 1\n"
//               "c <- c <+> 3\n"
//               "d <- c <+> 2\n"
//               "c ->- d <?> main <>>\n"
//               "c <+> d ->\n";
//        map = new VariableMap();
//    }
//
//    Interpreter(string data) {
//        this->data = data.append("");
//        map = new VariableMap();
//    }
//
//    void run() {
//        CodeMap* code = new CodeMap();
//        Takes* head = new Takes();
//        CodeMap* f = nullptr;
//        vector<string> lines,words;
//        lines = split(data,"\n");
//        for(int i=0;i<lines.size();i++) {
//            Token* token = new Token();
//            words = split(lines[i]," ");
//            Takes* n = head;
//            for(int j=0;j<words.size();j++) {
//                n->setNext(new Takes(words[j]));
//                token->translation(words[j]);
//                n = n->getNext();
//            }
//
//            //大于小于等于，必须在判断之前
//            if(token->getBig() || token->getSmall() || token->getSame()) {
//                for(n=head->getNext();n->getNext()!=nullptr;n=n->getNext()) {
//                    if(n->getNext()!=nullptr) {
//                        if(n->getNext()->getData() == "-<-") {
//                            int a,b;
//                            bool isExistA = false,isExistB = false;
//                            for(VariableMap* m = map;m->mapNext != nullptr;m = m->mapNext) {
//                                if(n->getData() == m->mapKey) {
//                                    a = stoi(m->mapValue);
//                                    isExistA = true;
//                                }
//                                if(n->getNext()->getNext()->getData() == m->mapKey) {
//                                    b = stoi(m->mapValue);
//                                    isExistB = true;
//                                }
//                            }
//
//                            if(!isExistA)
//                                a = stoi(n->getData());
//                            if(!isExistB)
//                                b = stoi(n->getNext()->getNext()->getData());
//
//                            Takes* f = n->getNext()->getNext()->getNext();
//                            n->setData(to_string(a < b));
//                            n->setNext(f);
//                        }
//                    }
//                    if(n->getNext()!=nullptr) {
//                        if (n->getNext()->getData() == "->-") {
//                            int a,b;
//                            bool isExistA = false,isExistB = false;
//                            for(VariableMap* m = map;m->mapNext != nullptr;m = m->mapNext) {
//                                if(n->getData() == m->mapKey) {
//                                    a = stoi(m->mapValue);
//                                    isExistA = true;
//                                }
//                                if(n->getNext()->getNext()->getData() == m->mapKey) {
//                                    b = stoi(m->mapValue);
//                                    isExistB = true;
//                                }
//                            }
//
//                            if(!isExistA)
//                                a = stoi(n->getData());
//                            if(!isExistB)
//                                b = stoi(n->getNext()->getNext()->getData());
//
//                            Takes *f = n->getNext()->getNext()->getNext();
//                            n->setData(to_string(a > b));
//                            n->setNext(f);
//                        }
//                    }
//                    if(n->getNext()!=nullptr) {
//                        if(n->getNext()->getData() == "-=-") {
//                            int a,b;
//                            bool isExistA = false,isExistB = false;
//                            for(VariableMap* m = map;m->mapNext != nullptr;m = m->mapNext) {
//                                if(n->getData() == m->mapKey) {
//                                    a = stoi(m->mapValue);
//                                    isExistA = true;
//                                }
//                                if(n->getNext()->getNext()->getData() == m->mapKey) {
//                                    b = stoi(m->mapValue);
//                                    isExistB = true;
//                                }
//                            }
//
//                            if(!isExistA)
//                                a = stoi(n->getData());
//                            if(!isExistB)
//                                b = stoi(n->getNext()->getNext()->getData());
//
//                            Takes* f = n->getNext()->getNext()->getNext();
//                            n->setData(to_string(a == b));
//                            n->setNext(f);
//                        }
//                    }
//                }
//            }
//
//            //判断，必须在基本语法之前
//            if(token->getBranch()) {
//                bool f = true;
//                for(n=head->getNext();n->getNext()!=nullptr;n=n->getNext()) {
//                    if(n->getNext()!=nullptr) {
//                        if(n->getNext()->getData() == "<?>") {
//                            f = stoi(n->getData());
//                        }
//                    }
//                }
//                if(!f) continue;
//            }
//
//            //语句块，开始和结尾
//            if(token->getChunkStart() || token->getChunkEnd()) {
//                for(n=head->getNext();n->getNext()!=nullptr;n=n->getNext()) {
//                    if(n->getNext()!=nullptr) {
//                        if(n->getNext()->getData() == ">>>") {
//                            CodeMap* m = code;
//                            for(m = code;m->mapNext != nullptr;m = m->mapNext) {
//                                if(n->getData() == m->mapName) {
//                                    cerr << "There are some same name.";
//                                    return;
//                                }
//                            }
//                            m->mapNext = new CodeMap();
//                            m->mapName = n->getData();
//                            f = m;
//                        }
//                    }
//                    if(n->getNext()!=nullptr) {
//                        if(n->getNext()->getData() == "<<<" && n->getData() == f->mapName) {
//                            f = nullptr;
//                        }
//                    }
//                }
//                continue;
//            }
//
//            //语句块，中间部分
//            if(f != nullptr) {
//                f->mapMessage = f->mapMessage.append(lines[i]).append("\n");
//                continue;
//            }
//
//            //跳转
//            if(token->getJump()) {
//                for(n=head->getNext();n!=nullptr&&n->getNext()!=nullptr;n=n->getNext()) {
//                    if(n->getNext()!=nullptr) {
//                        if(n->getNext()->getData() == "<>>") {
//                            for(CodeMap* m = code;m->mapNext != nullptr;m = m->mapNext) {
//                                if(n->getData() == m->mapName) {
//                                    Interpreter* lin = new Interpreter(m->mapMessage);
//                                    lin->run();
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//
//            //乘除，必须在加减输入输出之前
//            if(token->getMultiply() || token->getDivide()) {
//                for(n=head->getNext();n->getNext()!=nullptr;n=n->getNext()) {
//                    if(n->getNext()!=nullptr) {
//                        if(n->getNext()->getData() == "<*>") {
//                            int a,b;
//                            bool isExistA = false,isExistB = false;
//                            for(VariableMap* m = map;m->mapNext != nullptr;m = m->mapNext) {
//                                if(n->getData() == m->mapKey) {
//                                    a = stoi(m->mapValue);
//                                    isExistA = true;
//                                }
//                                if(n->getNext()->getNext()->getData() == m->mapKey) {
//                                    b = stoi(m->mapValue);
//                                    isExistB = true;
//                                }
//                            }
//
//                            if(!isExistA)
//                                a = stoi(n->getData());
//                            if(!isExistB)
//                                b = stoi(n->getNext()->getNext()->getData());
//
//                            Takes* f = n->getNext()->getNext()->getNext();
//                            n->setData(to_string(a * b));
//                            n->setNext(f);
//                        }
//                    }
//                    if(n->getNext()!=nullptr) {
//                        if (n->getNext()->getData() == "</>") {
//                            int a,b;
//                            bool isExistA = false,isExistB = false;
//                            for(VariableMap* m = map;m->mapNext != nullptr;m = m->mapNext) {
//                                if(n->getData() == m->mapKey) {
//                                    a = stoi(m->mapValue);
//                                    isExistA = true;
//                                }
//                                if(n->getNext()->getNext()->getData() == m->mapKey) {
//                                    b = stoi(m->mapValue);
//                                    isExistB = true;
//                                }
//                            }
//
//                            if(!isExistA)
//                                a = stoi(n->getData());
//                            if(!isExistB)
//                                b = stoi(n->getNext()->getNext()->getData());
//
//                            Takes *f = n->getNext()->getNext()->getNext();
//                            n->setData(to_string(a / b));
//                            n->setNext(f);
//                        }
//                    }
//                }
//            }
//
//            //加减，必须在输入输出之前
//            if(token->getAdd() || token->getSubtract()) {
//                for(n=head->getNext();n!=nullptr&&n->getNext()!=nullptr;n=n->getNext()) {
//                    if(n->getNext()!=nullptr) {
//                        if(n->getNext()->getData() == "<+>") {
//                            int a,b;
//                            bool isExistA = false,isExistB = false;
//                            for(VariableMap* m = map;m->mapNext != nullptr;m = m->mapNext) {
//                                if(n->getData() == m->mapKey) {
//                                    a = stoi(m->mapValue);
//                                    isExistA = true;
//                                }
//                                if(n->getNext()->getNext()->getData() == m->mapKey) {
//                                    b = stoi(m->mapValue);
//                                    isExistB = true;
//                                }
//                            }
//
//                            if(!isExistA)
//                                a = stoi(n->getData());
//                            if(!isExistB)
//                                b = stoi(n->getNext()->getNext()->getData());
//
//                            Takes* f = n->getNext()->getNext()->getNext();
//                            n->setData(to_string(a + b));
//                            n->setNext(f);
//                        }
//                    }
//                    if(n->getNext()!=nullptr) {
//                        if(n->getNext()->getData() == "<->") {
//                            int a,b;
//                            bool isExistA = false,isExistB = false;
//                            for(VariableMap* m = map;m->mapNext != nullptr;m = m->mapNext) {
//                                if(n->getData() == m->mapKey) {
//                                    a = stoi(m->mapValue);
//                                    isExistA = true;
//                                }
//                                if(n->getNext()->getNext()->getData() == m->mapKey) {
//                                    b = stoi(m->mapValue);
//                                    isExistB = true;
//                                }
//                            }
//
//                            if(!isExistA)
//                                a = stoi(n->getData());
//                            if(!isExistB)
//                                b = stoi(n->getNext()->getNext()->getData());
//
//                            Takes* f = n->getNext()->getNext()->getNext();
//                            n->setData(to_string(a - b));
//                            n->setNext(f);
//                        }
//                    }
//                }
//            }
//
//            //输入输出
//            if(token->getInput() || token->getOutput()) {
//                for(n=head->getNext();n!=nullptr&&n->getNext()!=nullptr;n=n->getNext()) {
//                    if(n->getNext()!=nullptr) {
//                        if(n->getNext()->getData() == "<-") {
//                            bool isExist = false;
//                            VariableMap* m = map;
//                            for(;m->mapNext != nullptr;m = m->mapNext) {
//                                if(n->getData() == m->mapNext->mapKey)
//                                    isExist = true;
//                            }
//                            if(!isExist) {
//                                m->mapNext = new VariableMap();
//                                m->mapKey = n->getData();
//                                m->mapValue = n->getNext()->getNext()->getData();
//                            }
//                        }
//                    }
//                    if(n->getNext()!=nullptr) {
//                        if(n->getNext()->getData() == "->") {
//                            cout << n->getData() << endl;
//                        }
//                    }
//                }
//            }
//        }
//    }
//};
//
//int main() {
//    Interpreter i;
//    i.run();
//    return 0;
//}

//二叉树与栈
//#include <iostream>
//#include <cstring>
//
//class BinaryTree {
//private:
//    BinaryTree* left;
//    BinaryTree* right;
//    char data;
//public:
//    BinaryTree() {
//        left = nullptr;
//        right = nullptr;
//        data = 0;
//    }
//    void setLeft(BinaryTree *l) {
//        left = l;
//    }
//    void setRight(BinaryTree *r) {
//        right = r;
//    }
//    void setData(char d) {
//        data = d;
//    }
//    BinaryTree* getLeft() {
//        return left;
//    }
//    BinaryTree* getRight() {
//        return right;
//    }
//    char getData() {
//        return data;
//    }
//    void displayBefore() {
//        if(data != 0) {
//            std::cout << data << '\t';
//            if(left != nullptr)
//                left->displayBefore();
//            if(right != nullptr)
//                right->displayBefore();
//        }
//    }
//    void displayNow() {
//        if(data != 0) {
//            if(left != nullptr)
//                left->displayNow();
//            std::cout << data << '\t';
//            if(right != nullptr)
//                right->displayNow();
//        }
//    }
//    void displayAfter() {
//        if(data != 0) {
//            if(left != nullptr)
//                left->displayAfter();
//            if(right != nullptr)
//                right->displayAfter();
//            std::cout << data << '\t';
//        }
//    }
//
//};
//
//class Warehouse {
//private:
//    int data;
//    Warehouse* next;
//public:
//    Warehouse() {
//        data = 0;
//        next = nullptr;
//    }
//
//    Warehouse(int d) {
//        data = d;
//        next = nullptr;
//    }
//
//    void push(int d) {
//        if (next == nullptr)
//            next = new Warehouse(d);
//        else {
//            Warehouse* w = next;
//            next = new Warehouse(d);
//            next->next = w;
//        }
//    }
//
//    int drop() {
//        int a = 0;
//        if(next != nullptr) {
//            a = next->data;
//            next = next->next;
//        }
//        return a;
//    }
//};
//
//int operation(int leftNumber,int rightNumber,char op) {
//    //hash映射
//    if (op == '+') {
//        std::cout << leftNumber << "+" << rightNumber << "=" << leftNumber + rightNumber << std::endl;
//        return leftNumber + rightNumber;
//    } else if (op == '-') {
//        std::cout << leftNumber << "-" << rightNumber << "=" << leftNumber - rightNumber << std::endl;
//        return leftNumber - rightNumber;
//    } else if (op == '*') {
//        std::cout << leftNumber << "*" << rightNumber << "=" << leftNumber * rightNumber << std::endl;
//        return leftNumber * rightNumber;
//    } else if (op == '/') {
//        std::cout << leftNumber << "/" << rightNumber << "=" << leftNumber / rightNumber << std::endl;
//        return leftNumber / rightNumber;
//    } else
//        return 0;
//}
//
//Warehouse* display(BinaryTree* tree,Warehouse* warehouse) {
//    int (*op)(int,int,char) = operation;
//    if(tree->getData() != 0) {
//        if(tree->getLeft() != nullptr)
//            warehouse = display(tree->getLeft(),warehouse);
//        if(tree->getRight() != nullptr)
//            warehouse = display(tree->getRight(),warehouse);
//        if(tree->getData() == '+' || tree->getData() == '-' || tree->getData() == '*' || tree->getData() == '/')
//            warehouse->push((*op)(warehouse->drop(),warehouse->drop(),tree->getData()));
//        else
//            warehouse->push((int)tree->getData()-48);
//    }
//    return warehouse;
//}
//
//void autoBinaryTree(char* list) {
//    BinaryTree* tree = new BinaryTree();
//    //生成对应数字运算符数量的二叉树对象
//    BinaryTree b[strlen(list)];
//    for(int i=0;i<strlen(list);i++) {
//        b[i].setData(list[i]);
//    }
//    //为运算符的对象关联其前后两个数字对象为其左右子
//    for(int i=0;i<strlen(list);i++) {
//        if (i%2==1) {
//            b[i].setLeft(&b[i-1]);
//            b[i].setRight(&b[i+1]);
//        }
//    }
//    //将含有相同子的运算符对象合并（后者的左子为前者）
//    for(int i=1;i<=((strlen(list)-1)/2);i++) {
//        if (b[i * 2 - 1].getRight() == b[i * 2 + 1].getLeft())
//            b[i * 2 + 1].setLeft(&b[i * 2 - 1]);
//    }
//    //将具有高优先级的运算符移到低优先级运算符的右子
//    BinaryTree* a;
//    for(int i=1;i<=((strlen(list)-1)/2);i++) {
//        if (b[i * 2 - 1].getLeft()->getData() >= '0' && b[i * 2 - 1].getLeft()->getData() <= '9')
//            continue;
//        if (b[i * 2 - 1].getData() == '*' || b[i * 2 - 1].getData() == '/') {
//            if(b[i*2-1].getLeft()->getData() == '+' || b[i*2-1].getLeft()->getData() == '-') {
//                if (i * 2 + 1 < strlen(list)) {
//                    b[i*2+1].setLeft(b[i*2-1].getLeft());
//                }
//                a = b[i*2-1].getLeft()->getRight();
//                b[i*2-1].getLeft()->setRight(&b[i*2-1]);
//                b[i*2-1].setLeft(a);
//            }
//        } else {
//            tree = &b[i*2-1];
//        }
//    }
//    tree->displayAfter();
//    std::cout << std::endl;
//    //计算过程
//    Warehouse* warehouse = display(tree,new Warehouse());
//    std::cout << warehouse->drop() <<std::endl;
//}
//
//int main() {
//    autoBinaryTree("1*2+3+4*5-6/3");
//    return 0;
//}

//梳排序
//#include<iostream>
//
//void combSort(int* data,int n) {
//    const double shrink = 1.25;
//    int i,delta=n,noswap=0,lin;
//    while (!noswap) {
//        for (noswap=1,i=0;i+delta<n;i++) {
//            if(data[i]>data[i+delta]) {
//                lin = data[i+delta];
//                data[i+delta] = data[i];
//                data[i] = lin;
//                noswap = 0;
//            }
//        }
//        if(delta>1) {
//            delta /= shrink;
//            noswap = 0;
//        }
//    }
//}
//
//int main() {
//    int data[8]={8,4,3,7,6,5,2,1};
//    combSort(data,8);
//    for(int i : data) {
//        std::cout << i << "\t";
//    }
//    return 0;
//}

//KMP算法
//#include <iostream>
//#include<cstdio>
//#include<cstring>
//#include <string>
//using namespace std;
////未改进的KMP算法代码实现
//void get_next(int *next, char *T, int len) {
//    next[0] = -1;//-1代表没有重复子串
//    int k = -1;
//    for (int q = 1; q <= len; q++)
//    {
//        while (k > -1 && T[k+1] != T[q])//下一个元素不相等，把k向前回溯
//        {
//            k = next[k];
//        }
//        if (T[k+1] == T[q])//下一个元素相等，所以最长重复子串+1
//        {
//            k = k+1;
//        }
//        next[q] = k;//给next数组赋值
//    }
//}
//int KMP(char *s, int len, char *p, int plen) {//利用KMP算法匹配
//    int *next = new int(plen);
//    get_next(next, p, plen);
//    int k = -1;
//    for (int i = 0; i < len; i++) {
//        while (k > -1 && p[k+1]!=s[i]) {//两串下一个字符不相等，向前回溯（效率高就是在这里，每次匹配失败，k不用直接变为0，从第一个字符开始重新匹配，而是变为最长重复子串的下一个字符，从中间开始匹配即可）。
//            k = next[k];
//        }
//        if(p[k+1] == s[i]) {//两个串的字符相等，k+1来匹配子串的一个字符
//            k++;
//        }
//        if (k == plen-1) {//匹配成功，返回短串在长串的位置。
//            return i-plen+1;
//        }
//    }
//    return -1;
//}
//int main() {
//    char a[] = "bacbababadababacambabacaddababacasdsd";
//    char b[] = "ababaca";
//    int m = KMP(a,strlen(a),b,strlen(b));
//    printf("%d", m);
//    return 0;
//}

//指针
//#include <stdio.h>
//int main() {
//    short a[4] = { 0x6261, 0x6463, 0x6665, 0 };
//    char* b = (char*)a;
//    printf("%s", b);
//}

//函数指针
//#include <stdio.h>
//struct User;
//void display(User* user);
//struct User {
//    int id;
//    int num;
//    char* name;
//    void (*dp)(User*) = display;
//};
//void display(User* user) {
//    printf("User ID:%d\t",user->id);
//    printf("User Num:%d\t",user->num);
//    printf("User Name:%s\n",user->name);
//}
//int main() {
//    User user;
//    user.id = 1;
//    user.num = 1001;
//    user.name = "Alice";
//    user.dp(&user);
//    return 0;
//}
