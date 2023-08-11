#include <iostream>
#include <thread>
#include "../net/udp.h"
#include "../sys/clock.h"
#ifdef linux
#include <cstring> //memset
#endif

class client final : public udp {
public:
    void handle(const char *message, int number) {
        if (mode != socket_mode::client) { return; }
        printf("client:%s\n", message);
    }
};

static volatile int current_number = 0;

void working(client* c) {
    current_number = 1;
    for(;;) {
        if (current_number == 0) { break; }
        current(1000);
        char recv_buffer[buffer_length]{0};
        int recv_length = 0;
        recv_length = c->response(recv_buffer, buffer_length);
        if (recv_length < 0) { continue; }
        if (current_number != 0) { current_number++; }
        c->handle(recv_buffer, recv_length);
        for(;;) {
            memset(recv_buffer, 0, buffer_length);
            recv_length = c->response(recv_buffer, buffer_length);
            if (recv_length < 0) { break; }
            c->handle(recv_buffer, recv_length);
        }
    }
}

static client* c = nullptr;

void terminal_s() {
    c = new client();
    c->in_it(socket_mode::client, 10246);
    working(c);
    c->un_it();
}

int main() {
    std::thread td(terminal_s);
    td.detach();
    for(;;) {
        std::string s;
        std::cin >> s;
        if ("exit" == s) { current_number = 0; current(1000); break; }
        if (c == nullptr) { printf("c"); continue; }
        c->request(s.c_str(), s.size());
    }
}
