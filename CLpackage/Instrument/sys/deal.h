#ifndef INSTRUMENT_DEAL_H
#define INSTRUMENT_DEAL_H

class deal {
protected:
    void handle_arguments(const char* format, ...); // 采用json字符串存储不定参数信息
public:
    virtual void handle() = 0;
};

#endif //INSTRUMENT_DEAL_H
