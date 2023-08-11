#include <iostream>
#include <thread>
#include "../net/udp.h"
#include "../sys/clock.h"
#ifdef linux
#include <cstring> //memset
#endif
#include "../sys/deal.h"

class server final : public udp {
public:
    void handle(const char* message, int number) {
        if (mode != socket_mode::server) { return; }
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
        recv_length = s->response(recv_buffer, buffer_length);
        if (recv_length < 0) { continue; }
        if (current_number != 0) { current_number++; }
        s->handle(recv_buffer, recv_length);
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
    auto* s = new server();
    s->in_it(socket_mode::server, 10246);
    working(s);
    s->un_it();
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
