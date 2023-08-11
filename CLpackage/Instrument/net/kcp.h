#ifndef INSTRUMENT_KCP_H
#define INSTRUMENT_KCP_H

#include "skt.h"
#include "udp.h"
#include "tcp.h"

class kcp : public protocol {
protected:
    void* skt = nullptr;
    void* ikp = nullptr;
public:
    void in_it(void* s = nullptr, net_mode t = net_mode::placeholder, int topic = 102435);
    void un_it();
    int response(char* c, int n);
    int request(const char* c, int n);
    int recv_input();
    int send_output(const char* c, int n);
    void segregate_update();
    void segregate_input(const char* recv_buffer, int recv_length);
};

#endif //INSTRUMENT_KCP_H
