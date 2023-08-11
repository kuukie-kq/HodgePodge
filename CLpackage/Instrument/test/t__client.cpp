#include <iostream>
#include <thread>
#include "../net/udp.h"
#include "../net/kcp.h"
#include "../sys/clock.h"
#include "../structure/rbt.h"
#ifdef linux
#include <cstring> //memset
#endif
#include "../sys/deal.h"

#if false
static volatile int k_current_number = 0;

class client_kcp final : public kcp {
public:
    void handle(const char* message, int number) {
        printf("client ks:%s\n", message);
    }
};

static client_kcp* ck = nullptr;

void working_k(client_kcp* s) {
    k_current_number = 1;
    for(;;) {
        if (k_current_number == 0) { break; }
        current(1000);
        s->segregate_update();
        char recv_buffer[buffer_length]{0};
        int recv_length = 0;
        if (k_current_number != 0) { k_current_number++; }
        // TODO study
        for(;;) {
            memset(recv_buffer, 0, buffer_length);
            recv_length = s->response(recv_buffer, buffer_length);
            if (recv_length < 0) { break; }
            s->handle(recv_buffer, recv_length);
        }
    }
}

class client final : public udp {
public:
    void handle(const char *message, int number) {
        if (mode != socket_mode::client) { return; }
        printf("client:%d\n", number);
        if (number >= 24) {
            ck->segregate_input(message, number);
        } else {
            int topic = atoi(message);
            if (ck != nullptr) { delete ck; ck = nullptr; }
            ck = new client_kcp();
            ck->in_it(this, net_mode::udp, topic);
            auto* td = new std::thread(working_k, ck);
            td->detach();
        }
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



void terminal_s() {
    auto* c = new client();
    c->in_it(socket_mode::client, 10246);
    std::string s = "shake";
    c->request(s.c_str(), s.size());
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
        if (ck == nullptr) { printf("ck"); continue; }
        ck->request(s.c_str(), s.size());
    }
}
#endif

class client_udp final : public udp {};
class client_kcp final : public kcp {
public:
    void handle(const char* message, int number) {
        printf("client ks:%s\n", message);
    }
};

static volatile int k_current_number = 0;

void working_k(client_kcp* s) {
    k_current_number = 1;
    for(;;) {
        if (k_current_number == 0) { break; }
        current(1000);
        char recv_buffer[buffer_length]{0};
        int recv_length = 0;
        recv_length = s->recv_input();
        if (recv_length < 0) { if (recv_length == -5) continue; else break; }
        if (k_current_number != 0) { k_current_number++; }
        // TODO study
        for(;;) {
            memset(recv_buffer, 0, buffer_length);
            recv_length = s->response(recv_buffer, buffer_length);
            if (recv_length < 0) { break; }
            s->handle(recv_buffer, recv_length);
        }
    }
}

static client_udp* cu = nullptr;
static client_kcp* ck = nullptr;

class client final : public udp {
private:
    int tp = 0;
public:
    void shake_hand(const char* message, int number) {
        printf("client shake hand:%s\n", message);
        int topic = atoi(message);
        if (ck != nullptr) { delete ck; ck = nullptr; }
        ck = new client_kcp();
        ck->in_it(cu, net_mode::udp, topic);
        tp = topic;
        auto* td = new std::thread(working_k, ck);
        td->detach();
    }

    void keep_alive(unsigned int flag = 0) {
        if (tp != 0 && flag == 0) {
            char c[20] = {};
            sprintf(c, "keepalive:%d", tp);
            std::string s = c;
            request(s.c_str(), s.size());
        }
        if (flag != 0) {
            char c[20] = {};
            sprintf(c, "finish___:%d", tp);
            std::string s = c;
            request(s.c_str(), s.size());
        }
    }
};

static volatile int current_number = 0;

void working(client* c) {
    current_number = 1;
    for(;;) {
        if (current_number == 0) { break; }
        c->keep_alive();
        current(1000);
        char recv_buffer[buffer_length]{0};
        int recv_length = 0;
        recv_length = c->response(recv_buffer, buffer_length);
        if (recv_length < 0) { continue; }
        if (current_number != 0) { current_number++; }
        c->shake_hand(recv_buffer, recv_length);
        for(;;) {
            memset(recv_buffer, 0, buffer_length);
            recv_length = c->response(recv_buffer, buffer_length);
            if (recv_length < 0) { break; }
            c->shake_hand(recv_buffer, recv_length);
        }
    }
}

void terminal_s() {
    auto* c = new client();
    if (cu == nullptr) { cu = new client_udp(); cu->in_it(socket_mode::client, 10245); }
    c->in_it(socket_mode::client, 10246);
    std::string s = "shake";
    c->request(s.c_str(), s.size());
    working(c);
    c->keep_alive(1);
    c->un_it();
}

int main() {
    std::thread td(terminal_s);
    td.detach();
    for(;;) {
        std::string s;
        std::cin >> s;
        if ("exit" == s) { current_number = 0; current(1000); break; }
        if (ck == nullptr) { printf("ck"); continue; }
        ck->request(s.c_str(), s.size());
    }
}
