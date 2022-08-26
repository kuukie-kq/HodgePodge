//
// Created by kuu-kie on 2022/8/25.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream> //输入输出
#include <sstream> //输入输出缓冲
#include <cstdarg> //不定参数处理
#include <chrono> //时间戳
#include <string> //字符串类
#include <vector> //不定数组，字符串分割

namespace kuu {
    //
    class hickey {
    private:
        // 禁用拷贝构造函数
        hickey& operator=(hickey&) = default;
        hickey(hickey&) = default;
        // 禁用赋值运算符
        hickey& operator=(hickey&&) = default;
        hickey(hickey&&) = default;
    protected:
        // 禁用构造函数，也不算禁用，就是无法正常使用，防止产生实例
        // 不过，存在纯虚函数，就产生不了实例
        hickey() = default;
    public:
        virtual ~hickey() = default;
        virtual unsigned int sign() const;
        virtual bool equals(const hickey* target) = 0;
        virtual int clone(hickey*& target) = 0; // 注意，使用深拷贝，另外注意参数的传递，可能会出现内存无法回收的情况
        virtual int hash() = 0;
    };

    namespace {
        //
        // 对于一些很难受的警告可以使用注释 //NOLINT 来消除
        // 明知代码没有问题，规范上也说得过去
        //
        class utils final {
        private:
            utils() = default;
            ~utils() = default;
            utils& operator=(utils&)  = default;
            utils(const utils&) = default;
            utils& operator=(utils&&)  = default;
            utils(utils&&) = default;
            static utils* u;
        public:
            static utils* signal() { return u; }
            inline unsigned int hash_code(const char* key) const { //NOLINT
                unsigned int result;
                unsigned char* byte;
                for (result = 0, byte = (unsigned char*)key; *byte; byte++) {
                    result = result * 31 + *byte;
                }
                return result;
            }
            inline std::vector<std::string> spilt(std::string str, const std::string& pattern) const { //NOLINT
                std::string::size_type pos;
                std::vector<std::string> result;
                str += pattern;
                unsigned int size = str.size();
                for (unsigned int i = 0; i < size; i++) {
                    pos = str.find(pattern, i);
                    if (pos < size) {
                        std::string s = str.substr(i, pos - i);
                        result.push_back(s);
                        i = pos + pattern.size() - 1;
                    }
                }
                return result;
            }
            inline unsigned int encode(const char* key) const { //NOLINT
                // 由于数据大小的限制，27进制最大只能存7位
                // 4294967295
                // b28jpdl  标准编码数
                // 为下划线和26个字母，对应应用于类的标识，由于类名一般不短，需摘要部分
                // 固，保证全覆盖，key只能为6位，且不允许下划线开头
                unsigned int result;
                unsigned char* byte;
                for (result = 0, byte = (unsigned char*)key; *byte; byte++) {
                    if ((*byte - 96) > 0 && (*byte - 96) < 27 ) {
                        result = result * 27 + *byte - 96;
                    } else if (*byte == 95) {
                        result = result * 27;
                    } else {
                        return 0;
                    }
                }
                return result;
            }
            inline int decode(unsigned int secret, std::string* key) const { //NOLINT
                int stack[6];
                for (int& i : stack) { i = -1; }
                if (secret == 0) { return 0; }
                int s = 0;
                for(unsigned int i = secret; i > 0; i = i / 27) {
                    stack[s++] = static_cast<int>(i % 27u);
                }
                for(s--; s >= 0; s--) {
                    if(stack[s] == 0) {
                        key->append("_");
                    } else {
                        key->push_back(static_cast<char>(stack[s] + 96));
                    }
                }
                return 1;
            }
        };
        #ifdef COMPONENT_H
        #define UTL ({ utils::signal(); })
            utils* utils::u = new utils(); //NOLINT
        #endif //COMPONENT_H
    }

    unsigned int hickey::sign() const {
        return UTL->encode("hickey");
    }

    class system_stream : public hickey {
    private:
        const static int MAX_LENGTH = 1024;
        const static int BUFFER_SIZE = 1048575; // 2^20 - 1
        class time_stamp {
            //long long 64位
            //18446744073709551616 2^64 20位
            //9999999999000000000 纳秒时间戳 2286-11-21 1:46:39 最大？
            //unsigned long long 目前够用
        private:
            std::chrono::nanoseconds start_stamp = std::chrono::nanoseconds::zero();
        public:
            time_stamp() {
                start_stamp = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::system_clock::now().time_since_epoch()
                );
            }
            ~time_stamp() {
                start_stamp = std::chrono::nanoseconds::zero();
            }
            unsigned long long time_line_passed() {
                std::chrono::nanoseconds now = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::system_clock::now().time_since_epoch()
                );
                unsigned long long passed = now.count() - start_stamp.count();
                if (passed > 0) {
                    return (passed);
                }
                return 0;
            }
            unsigned long long time_start() {
                return start_stamp.count();
            }
            static unsigned long long time_now() {
                std::chrono::nanoseconds now = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::system_clock::now().time_since_epoch()
                );
                unsigned long long passed = now.count();
                return passed;
            }
        };
        time_stamp* time;
        unsigned int on_or_off;
        unsigned int level;
        static inline unsigned int time_nano(unsigned long long stamp) {
            unsigned int re = stamp % 1000;
            return re;
        }
        static inline unsigned int time_milli(unsigned long long stamp) {
            unsigned int re = stamp / 1000 % 1000;
            return re;
        }
        static inline unsigned int time_micro(unsigned long long stamp) {
            unsigned int re = stamp / 1000000 % 1000;
            return re;
        }
        static inline unsigned int time_second(unsigned long long stamp) {
            unsigned int re = stamp / 1000000000 % 60;
            return re;
        }
        static inline unsigned int time_minute(unsigned long long stamp) {
            unsigned int re = stamp / 1000000000 / 60 % 60;
            return re;
        }
        static inline unsigned int time_hour(unsigned long long stamp) {
            unsigned int re = stamp / 1000000000 / (60 * 60) % 24;
            return re + 8;// UTC+8 (GMT)
        }
        virtual void step() const {
            if (buff->rdbuf()->in_avail() > BUFFER_SIZE) {
                std::cout << buff->str();
                buff->clear();
                buff->str("");
            }
            unsigned long long tmp = time_stamp::time_now();
            *buff << "<  \t"
                  << time_hour(tmp) << ":" << time_minute(tmp) << "  " << time_second(tmp) << "s "
                  << time_micro(tmp) << "ms " << time_milli(tmp) << "us " << time_nano(tmp) << "ns\n"
                  << ss->str() << " ->\n";
        }
        virtual void log() const {
            if (buff->rdbuf()->in_avail() > 0) {
                std::cout << buff->str();
                buff->clear();
                buff->str("");
            }
            unsigned long long tmp = time_stamp::time_now();
            std::cout << "<  \t"
                      << time_hour(tmp) << ":" << time_minute(tmp) << "  " << time_second(tmp) << "s "
                      << time_micro(tmp) << "ms " << time_milli(tmp) << "us " << time_nano(tmp) << "ns\n"
                      << ss->str() << " *>" << std::endl;
        }
        virtual void warning() const {
            unsigned long long tmp = time_stamp::time_now();
            std::cout << ">  \t"
                      << time_hour(tmp) << ":" << time_minute(tmp) << "  " << time_second(tmp) << "s "
                      << time_micro(
                              tmp) << "ms " << time_milli(tmp) << "us " << time_nano(tmp) << "ns\n"
                      << ss->str() << " -<" << std::endl;
        }
        virtual void error() const {
            unsigned long long tmp = time_stamp::time_now();
            std::cerr << ">  \t"
                      << time_hour(tmp) << ":" << time_minute(tmp) << "  " << time_second(tmp) << "s "
                      << time_micro(
                              tmp) << "ms " << time_milli(tmp) << "us " << time_nano(tmp) << "ns\n"
                      << ss->str() << " *<" << std::endl;
        }
        std::stringstream* ss;
        std::stringstream* buff;
    public:
        explicit system_stream(unsigned int ooo = 1u, unsigned int mode = 0) {
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
            time = new time_stamp();
        }
        ~system_stream() override {
            delete time;
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
                char *buffer = (char *) malloc(MAX_LENGTH);
                va_list args;
                va_start(args, format);
                int length = vsnprintf(buffer, MAX_LENGTH, format, args);
                (length >= MAX_LENGTH) ? *ss << length << "- format and args too long" : *ss << buffer;
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
            unsigned long stamp = time->time_line_passed();
            unsigned long stamp_ms = stamp % 1000000000 / 1000000;
            unsigned long stamp_us = stamp % 1000000 / 1000;
            unsigned long stamp_ns = stamp % 1000;
            append("%llu[%d s %d ms %d us %d ns]", stamp, stamp / 1000000000, stamp_ms, stamp_us, stamp_ns);
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
        unsigned int sign() const override {
            return UTL->encode("system");
        }
        int hash() override { return static_cast<int>(time->time_start()); }
        bool equals(const hickey* target) override {
            if (target->sign() != sign()) {
                return false;
            }
            return ((system_stream *) target)->ss->str() == ss->str() &&
                   ((system_stream *) target)->buff->str() == buff->str();
        }
        int clone(hickey*& target) override {
            if (target == nullptr) { return 0; }
            if (target == this) {
                target = new system_stream(on_or_off, level);
                return 2;
            } else {
                delete target;
                target = new system_stream(on_or_off, level);
                return 1;
            }
        }
    };

    class error : public hickey {
    public:
        system_stream* err;
        error() { err = new system_stream(1u,1u); }
        ~error() override { delete err; }
        bool equals(const hickey* target) override { return false; }
        int hash() override { return err->hash(); }
        unsigned int sign() const override { return UTL->encode("error"); }
        int clone(hickey*& target) override { return 0; }
        error(error const& eor) {
            err = new system_stream();
            eor.err->clone(reinterpret_cast<hickey*&>(err));
        }
    };

    int component_run_main() {
        try {
            auto* out = new system_stream(7u, 4u);
            out->append("hash code [%d]\n", UTL->hash_code("system_stream"));
            auto* str = new std::string();
            UTL->decode(out->sign(), str);
            out->append("decode [%c]\n", str->c_str());
            UTL->spilt(*str, "t");
            auto* war = new system_stream(3u);
            war->start(2u);
            war->append("a");
            war->end();
            war->maybe(1u);
            war->append("b e [%d]", war->equals(out));
            war->end();
            out->end();
            delete war;
            delete str;
            delete out;
            auto* e = new error();
            e->err->append("test error\nequals [%d]\n", out->equals(e));
            throw e; //NOLINT
        } catch (error* e) { //NOLINT
            e->err->end();
            delete e;
        }
        return 0;
    }
}

#endif //COMPONENT_H
