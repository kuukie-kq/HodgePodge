#include <iostream>
#include <thread>
#include "../net/udp.h"
#include "../net/kcp.h"
#include "../sys/clock.h"
#ifdef linux
#include <cstring> //memset
#endif
#include "../sys/deal.h"

class s final : public udp {};
class server final : public kcp {
public:
    void handle(const char* message, int number) {
        printf("server:%s\n", message);
        char buf[buffer_length]{0};
        int len = sprintf(buf, "ack.%s", message);
        request(buf, len);
    }
};

static volatile int current_number = 0;

void working(server* s) {
    current_number = 1;
    for(;;) {
        if (current_number == 0) { break; }
        current(1000);
        char recv_buffer[buffer_length]{0};
        int recv_length = 0;
        // style
        recv_length = s->recv_input();
        if (recv_length < 0) { if (recv_length == -5) continue; else break; }
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

void terminal_s() {
    auto* ss = new s();
    ss->in_it(socket_mode::server, 10246);
    auto* se = new server();
    se->in_it(ss, net_mode::udp, 102435);
    working(se);
    se->un_it();
    ss->un_it();
}

int main() {
    std::thread td(terminal_s);
    td.detach();
    for(;;) {
        std::string s;
        std::cin >> s;
        if ("exit" == s) { current_number = 0; current(1000); break; }
    }
}
