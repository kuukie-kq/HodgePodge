#include <iostream>
#include <thread>
#include "../net/udp.h"
#include "../net/kcp.h"
#include "../sys/clock.h"
#ifdef linux
#include <cstring> //memset
#endif
#include "../sys/deal.h"

class c final : public udp {};
class client final : public kcp {
public:
    void handle(const char* message, int number) {
        printf("client:%s\n", message);
    }
};

static volatile int current_number = 0;

void working(client* s) {
    current_number = 1;
    for(;;) {
        if (current_number == 0) { break; }
        current(1000);
        char recv_buffer[buffer_length]{0};
        int recv_length = 0;
        // style
        recv_length = s->recv_input();
        if (recv_length < 0) { continue; }
        if (current_number != 0) { current_number++; }
        // TODO study
        for(;;) {
            memset(recv_buffer, 0, buffer_length);
            recv_length = s->response(recv_buffer, buffer_length);
            if (recv_length < 0) { break; }
            s->handle(recv_buffer, recv_length);
        }
    }
}

static client* cl = nullptr;

void terminal_s() {
    auto* ss = new c();
    ss->in_it(socket_mode::client, 10246);
    cl = new client();
    cl->in_it(ss, net_mode::udp, 102435);
    working(cl);
    cl->un_it();
    ss->un_it();
}

int main() {
    std::thread td(terminal_s);
    td.detach();
    for(;;) {
        std::string s;
        std::cin >> s;
        if ("exit" == s) { current_number = 0; current(1000); break; }
        if (cl == nullptr) { printf("c"); continue; }
        cl->request(s.c_str(), s.size());
    }
}
