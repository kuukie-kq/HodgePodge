//
// Created by kuu-kie on 2022/8/23.
//

#ifndef DESIGN_PATTERN_H
#define DESIGN_PATTERN_H

#include <iostream> //输入输出
#include <sstream> //输入输出缓冲
#include <cstdarg> //不定参数处理
#include <cstring> //不定参数处理

namespace {
    //匿名命名空间，仅在本文件中使用
    class system_stream_io {
    private:
        unsigned int on_or_off;
        unsigned int level;

        void step() const {
            if (buff->rdbuf()->in_avail() > 1048575) {
                std::cout << buff->str();
                buff->clear();
                buff->str("");
            }
            *buff << "<->" << ss->str() << "\n";
        }

        void log() const {
            if (buff->rdbuf()->in_avail() > 0) {
                std::cout << buff->str();
                buff->clear();
                buff->str("");
            }
            std::cout << "<*>" << ss->str() << std::endl;
        }

        void warning() const {
            std::cout << ">-<" << ss->str() << std::endl;
        }

        void error() const {
            std::cerr << ">*<" << ss->str() << std::endl;
        }

        std::stringstream *ss;
        std::stringstream *buff;
    public:
        explicit system_stream_io(unsigned int ooo = 1u, unsigned int mode = 0) {
            //如果仅仅作为局部变量，输出完就释放内存
            //可以将第二个参数填上
            //不需要进行start或者maybe即可输出
            //
            //作为频繁的步骤，输出很影响性能
            //不完全数据
            //100040002次循环
            //中间过程不输出2s完成
            //中间过程全部每次输出900~1000s完成
            //加入buff缓冲，全输出但并不是实时的依据设置的大小不同400~700s完成
            //所以，保留buff
            ss = new std::stringstream();
            buff = new std::stringstream();
            on_or_off = ooo;
            level = mode;
        }

        ~system_stream_io() {
            delete ss;
            delete buff;
        }

        void clear() {
            ss->clear();
            ss->str("");
            level = 0;
        }

        void start(unsigned int mode) {
            //当对象为全局的时候，输出的起始
            //作为不频繁申请内存
            if (ss->rdbuf()->in_avail() > 0) {
                clear();
            }
            level = mode;
        }

        void maybe(unsigned int mode) {
            //局部时，可能不确定在那一个地方进行了设置
            //但又不想在正常情况下输出空行
            level = mode;
        }

        void append(const char *format, ...) const {
            //不定参数的一种实现
            //目前来说比较方便的
            if (level & on_or_off) {
                char *buffer = (char *) malloc(1024);
                va_list args;
                va_start(args, format);
                int length = vsnprintf(buffer, 1024, format, args);
                (length >= 1024) ? *ss << length << "- format and args too long" : *ss << buffer;
                va_end(args);
                delete buffer;
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
    };
}

namespace plant {
    //23种设计模式中的工厂模式
    class gun {
        //接口 枪接口
    private:
        gun& operator=(gun&)  = default;
        gun(const gun&) = default;
    protected:
        gun() = default;
        ~gun() = default;
    public:
        virtual void play() = 0;
    };

    class pistol : public gun {
    private:
        system_stream_io* ooo;
        char code;
        int version;
    public:
        explicit pistol(char code = 'A', int version = 0, system_stream_io* ooo = new system_stream_io(15u, 4u)) : code(code), version(version), ooo(ooo) {}
        ~pistol() {
            delete ooo;
        }
        void play() override {
            ooo->append("手枪 %c-%d 瞄准 开枪 [8/8]", code, version);
            ooo->end();
        }
    };

    class machine_gun : public gun {
    private:
        system_stream_io* ooo;
        char code;
        int version;
    public:
        explicit machine_gun(char code = 'R', int version = 0, system_stream_io* ooo = new system_stream_io(15u, 4u)) : code(code), version(version), ooo(ooo) {}
        ~machine_gun() {
            delete ooo;
        }
        void play() override {
            ooo->append("机枪 %c-%d 瞄准 开枪 [100/100]", code, version);
            ooo->end();
        }
    };

    class gun_factory {
    private:
        static char* names[2];
    public:
        static gun* create(char* name, char code, int version) {
            if (strcmp(names[0], name) == 0) {
                return new pistol(code, version);
            } else if (strcmp(names[1], name) == 0) {
                return new machine_gun(code, version);
            } else {
                return nullptr;
            }
        }
    };
    char* gun_factory::names[2] = {"pistol", "machine"};
}

namespace abstract_plant {
    //23种设计模式中的抽象工厂模式
    class gun {
        //接口 枪接口
    private:
        gun& operator=(gun&)  = default;
        gun(const gun&) = default;
    protected:
        gun() = default;
        ~gun() = default;
    public:
        virtual void play() = 0;
    };

    class pistol : public gun {
    private:
        system_stream_io* ooo;
        char code;
        int version;
    public:
        explicit pistol(char code = 'A', int version = 0, system_stream_io* ooo = new system_stream_io(15u, 4u)) : code(code), version(version), ooo(ooo) {}
        ~pistol() {
            delete ooo;
        }
        void play() override {
            ooo->append("手枪 %c-%d 瞄准 开枪 [8/8]", code, version);
            ooo->end();
        }
    };

    class machine_gun : public gun {
    private:
        system_stream_io* ooo;
        char code;
        int version;
    public:
        explicit machine_gun(char code = 'R', int version = 0, system_stream_io* ooo = new system_stream_io(15u, 4u)) : code(code), version(version), ooo(ooo) {}
        ~machine_gun() {
            delete ooo;
        }
        void play() override {
            ooo->append("机枪 %c-%d 瞄准 开枪 [100/100]", code, version);
            ooo->end();
        }
    };

    class factory {
        //工厂
    private:
        static char* names[2];
        factory& operator=(factory&)  = default;
        factory(const factory&) = default;
    protected:
        factory() = default;
        ~factory() = default;
    public:
        static factory* instance(char* name);
        virtual void* create(char* name, char code, int version) = 0;
    };

    class gun_factory : public factory {
    private:
        char* names[2]{};
    public:
        gun_factory() {
            names[0] = "pistol";
            names[1] = "machine";
        }
        void* create(char* name, char code, int version) override {
            if (strcmp(names[0], name) == 0) {
                return new pistol(code, version);
            } else if (strcmp(names[1], name) == 0) {
                return new machine_gun(code, version);
            } else {
                return nullptr;
            }
        }
    };

    class gale {
        //接口 枪接口
    private:
        gale& operator=(gale&)  = default;
        gale(const gale&) = default;
    protected:
        gale() = default;
        ~gale() = default;
    public:
        virtual void shot() = 0;
    };

    class knife : public gale {
    private:
        system_stream_io* ooo;
        char code;
        int length;
    public:
        explicit knife(char code = 'A', int length = 0, system_stream_io* ooo = new system_stream_io(15u, 4u)) : code(code), length(length), ooo(ooo) {}
        ~knife() {
            delete ooo;
        }
        void shot() override {
            ooo->append("小刀 %c 攻击 [%d]", code, length);
            ooo->end();
        }
    };

    class grenade : public gale {
    private:
        system_stream_io* ooo;
        char code;
        int length;
    public:
        explicit grenade(char code = 'A', int length = 0, system_stream_io* ooo = new system_stream_io(15u, 4u)) : code(code), length(length), ooo(ooo) {}
        ~grenade() {
            delete ooo;
        }
        void shot() override {
            ooo->append("手雷 %c 投掷 [%d]", code, length);
            ooo->end();
        }
    };

    class gale_factory : public factory {
    private:
        char* names[2]{};
    public:
        gale_factory() {
            names[0] = "knife";
            names[1] = "grenade";
        }
        void* create(char* name, char code, int version) override {
            if (strcmp(names[0], name) == 0) {
                return new knife(code, version);
            } else if (strcmp(names[1], name) == 0) {
                return new grenade(code, version);
            } else {
                return nullptr;
            }
        }
    };

    char* factory::names[2] = {"gun", "gale"};
    factory* factory::instance(char *name)  {
        if (strcmp(names[0], name) == 0) {
            return new gun_factory();
        } else if (strcmp(names[1], name) == 0) {
            return new gale_factory();
        } else {
            return nullptr;
        }
    }
}

namespace constructor {
    //23种设计模式中的建造者模式
    class build {
        //接口 构造过程（3步）
    private:
        build& operator=(build&)  = default;
        build(const build&) = default;
    protected:
        build() = default;
    public:
        virtual ~build() = default;
        virtual void first() = 0;
        virtual void second() = 0;
        virtual void third() = 0;
    };

    class project_c : public build {
    private:
        system_stream_io* ooo;
    public:
        explicit project_c(system_stream_io* ooo = new system_stream_io(15u)) : ooo(ooo) {}
        ~project_c() override { delete ooo; }
        void first() override {
            ooo->start(8u);
            ooo->append("准备gcc g++编译器及编译环境");
            ooo->end();
        }
        void second() override {
            ooo->start(8u);
            ooo->append("准备clion编辑器，也可以不准备，直接写文件（代码）");
            ooo->end();
        }
        void third() override {
            ooo->start(4u);
            ooo->append("编译运行，得到结果（c/c++）");
            ooo->end();
        }
    };

    class project_j : public build {
    private:
        system_stream_io* ooo;
    public:
        explicit project_j(system_stream_io* ooo = new system_stream_io(15u)) : ooo(ooo) {}
        ~project_j() override { delete ooo; }
        void first() override {
            ooo->start(8u);
            ooo->append("准备jdk编译器及jre编译环境和jvm运行环境");
            ooo->end();
        }
        void second() override {
            ooo->start(8u);
            ooo->append("准备idea编辑器，也可以不准备，直接写文件（代码）");
            ooo->end();
        }
        void third() override {
            ooo->start(4u);
            ooo->append("编译运行，得到结果（java）");
            ooo->end();
        }
    };

    class project_p : public build {
    private:
        system_stream_io* ooo;
    public:
        explicit project_p(system_stream_io* ooo = new system_stream_io(15u, 4u)) : ooo(ooo) {}
        ~project_p() override { delete ooo; }
        void first() override {
            ooo->start(8u);
            ooo->append("准备anaconda集成开发环境");
            ooo->end();
        }
        void second() override {
            ooo->start(8u);
            ooo->append("准备pycharm编辑器，也可以不准备，直接写文件（代码）");
            ooo->end();
        }
        void third() override {
            ooo->start(4u);
            ooo->append("解释运行，得到结果（python）");
            ooo->end();
        }
    };

    class builder {
    private:
        build* bud;
    public:
        explicit builder(build* bud) : bud(bud) {}
        ~builder() { delete bud; }
        void run() {
            bud->first();
            bud->second();
            bud->third();
        }
    };
}

namespace proto {
    //23种设计模式中的原型模式
    class cloneable {
        //接口 对象复制
    private:
        cloneable& operator=(cloneable&)  = default;
        cloneable(const cloneable&) = default;
    protected:
        cloneable() = default;
    public:
        virtual ~cloneable() = default;
        virtual void clone_unused(const void*& target) = 0;
        virtual void clone(const void* target) = 0;
    };

    class color : cloneable {
    public:
        enum name { RED = 0, BLUE = 1 };
        name n;
        int rgb;
        int hsl;
        explicit color(name n = RED, int rgb = 0xFF0000, int hsl = 360100050) : n(n), rgb(rgb), hsl(hsl) {}
        ~color() override = default;
        void clone_unused(const void*& target) override {
            if (target != nullptr) { delete (color*)target; }
            target = new color(n);
            ((color*)target)->rgb = rgb;
            ((color*)target)->hsl = hsl;
        }
        void clone(const void* target) override {
            if (target != nullptr) { delete (color*)target; } else { return; }
            target = new color(n);
            ((color*)target)->rgb = rgb;
            ((color*)target)->hsl = hsl;
        }
    };

    class warehouse {
    private:
        static color* cs[2];
    public:
        static void add(int index_positive, color* c) {
            cs[index_positive - 1] = c;
        }
        static color* get_clone(int index_positive) {
            auto* ret = new color();
            cs[index_positive - 1]->clone(ret);
            return ret;
        }
    };
    color* warehouse::cs[2] = {nullptr, nullptr};
}

namespace singleton {
    //23种设计模式中的单例模式
    class utils {
    private:
        static utils* us;
        explicit utils(int id = 0) : id(id) {}
        ~utils() = default;
        utils& operator=(utils&)  = default;
        utils(const utils&) = default;
    public:
        int id;
        static utils* get_instance() { return us; }
    };

    utils* utils::us = new utils();
}

namespace adapter {
    //23种设计模式中的适配器模式
    class dumpling {
    protected:
        system_stream_io* ooo;
    public:
        explicit dumpling(system_stream_io* ooo = new system_stream_io(4u,4u)) : ooo(ooo) {}
        void run() {
            ooo->append("烧水，下锅，吃");
            ooo->end();
        }
    };

    class boiled_dumpling : public dumpling {
    public:
        void run_boiled() {
            ooo->append("饺子皮，包饺子");
            run();
        }
    };
}

namespace bridge {
    //23种设计模式中的桥接模式
    class brand {
    private:
        brand& operator=(brand&)  = default;
        brand(const brand&) = default;
    protected:
        brand() = default;
    public:
        virtual ~brand() = default;
        virtual void sale() = 0;
    };

    class lenovo : public brand {
    private:
        system_stream_io* ooo;
    public:
        explicit lenovo(system_stream_io* ooo = new system_stream_io(4u)) : ooo(ooo) {}
        ~lenovo() override = default;
        void sale() override {
            ooo->start(4u);
            ooo->append("联想品牌");
            ooo->end();
        }
    };

    class dell : public brand {
    private:
        system_stream_io* ooo;
    public:
        explicit dell(system_stream_io* ooo = new system_stream_io(4u)) : ooo(ooo) {}
        ~dell() override = default;
        void sale() override {
            ooo->start(4u);
            ooo->append("戴尔品牌");
            ooo->end();
        }
    };

    class computer {
    private:
        computer& operator=(computer&)  = default;
        computer(const computer&) = default;
    protected:
        brand* b;
        explicit computer(brand* b) : b(b) {}
    public:
        virtual ~computer() = default;
        virtual void sale() = 0;
    };

    class desktop : public computer {
    private:
        system_stream_io* ooo;
    public:
        explicit desktop(brand* b, system_stream_io* ooo = new system_stream_io(4u)) : computer(b),ooo(ooo) {}
        ~desktop() override = default;
        void sale() override {
            ooo->start(4u);
            ooo->append("台式电脑大甩卖");
            ooo->end();
            b->sale();
        }
    };
}

namespace composite {
    //23种设计模式中的组合模式
    class group {
    private:
        group& operator=(group&)  = default;
        group(const group&) = default;
    protected:
        explicit group() = default;
    public:
        virtual ~group() = default;
        virtual void print_local(const std::string& local) = 0;
        virtual void add(group* g) = 0;
    };

    class text : public group {
    private:
        system_stream_io* ooo;
        char name;
    public:
        explicit text(char name, system_stream_io* ooo = new system_stream_io(4u)) : name(name), ooo(ooo) {}
        ~text() override = default;
        void print_local(const std::string& local) override {
            ooo->start(4u);
            ooo->append("%s/%c.txt", local.c_str(), name);
            ooo->end();
        }
        void add(group *g) override {}
    };

    class directory : public group {
    private:
        system_stream_io* ooo;
        char name;
        group* gs[5]{};
    public:
        explicit directory(char name, system_stream_io* ooo = new system_stream_io(4u)) : name(name), ooo(ooo) { for (group*& g : gs) { g = nullptr; } }
        ~directory() override = default;
        void print_local(const std::string& local) override {
            ooo->start(4u);
            std::string a = local;
            a.append("/");
            a.append(&name);
            ooo->append("%s", a.c_str());
            ooo->end();
            for (group*& g : gs) {
                if (g != nullptr) {
                    g->print_local(a.c_str());
                }
            }
        }
        void add(group* g) override {
            for (group*& gp : gs) {
                if (gp == nullptr) {
                    gp = g;
                    break;
                }
            }
        }
    };
}

namespace decorator {
    //23种设计模式中的装饰器模式
    class designer {
    private:
        designer& operator=(designer&)  = default;
        designer(const designer&) = default;
    protected:
        explicit designer() = default;
    public:
        virtual ~designer() = default;
        virtual void print_append(system_stream_io* out) = 0;
    };

    class file : public designer {
    private:
        std::string* name;
    public:
        explicit file(std::string* name) : name(name) {}
        void print_append(system_stream_io *out) override {
            out->append("%s", name->c_str());
        }
    };

    class directory : public designer {
    private:
        designer* d;
    public:
        explicit directory(designer* d) : d(d) {}
        void print_append(system_stream_io *out) override {
            out->append("{ ");
            d->print_append(out);
            out->append(" }");
        }
    };
}

namespace facade {
    //23种设计模式中的外观模式
    class process {
    private:
        process& operator=(process&)  = default;
        process(const process&) = default;
    protected:
        explicit process() = default;
    public:
        virtual ~process() = default;
        virtual void run() = 0;
    };

    class interface {
    private:
        process* p;
    public:
        explicit interface(process* p) : p(p) {}
        ~interface() { delete p; }
        void run() {
            p->run();
        }
        static void display() {
            auto* ooo = new system_stream_io(4u, 4u);
            ooo->append("供其他调用的上层接口（对于将功能的调用顺序进行高度封装形成黑盒）");
            ooo->end();
        }
    };
}

//main函数写法，既示例
int design_run_main() {
    return 0;
}

#endif //DESIGN_PATTERN_H
