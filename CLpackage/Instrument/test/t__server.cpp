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
static rbt* pool_kv = nullptr;

static volatile int k_current_number = 0;

class server final : public kcp {
public:
    void handle(const char* message, int number) {
        printf("server ks:%s\n", message);
        char buf[buffer_length]{0};
        int len = sprintf(buf, "ack.%s", message);
        request(buf, len);
    }
};

void working_k(server* s) {
    k_current_number = 1;
    for(;;) {
        if (k_current_number == 0) { break; }
        current(1000);
        char recv_buffer[buffer_length]{0};
        int recv_length = 0;
        // style
        s->segregate_update();
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

class sukp final : public udp {
private:
    server* ikps[10] = {};
    const unsigned int k[10] = {0, 195341, 491741, 4894773, 1717, 6543, 841, 48964, 8974489, 49784};
public:
    void handle(const char* message, int number) {
        if (number < 24) {
            if (strcmp(message, "shake") == 0) {
                server* ikp = ikps[0];
                int index = 0;
                for (int i = 1; i < 10; i++) {
                    if (pool_kv->find(k[i]) == nullptr) {
                        ikp = ikps[i];
                        index = i;
                        break;
                    }
                }
                if ((void*)ikp == (void*)ikps) { return; }
                ikp = new server();
                index = static_cast<int>(k[index]);
                ikp->in_it(this, net_mode::udp, index);
                pool_kv->add_insert(index, ikp);
                auto* td = new std::thread(working_k, ikp);
                td->detach();

                char buf[buffer_length]{0};
                int len = sprintf(buf, "%d", index);
                request(buf, len);
            }
        } else {
            unsigned int topic = *(unsigned int*)message;
            ((server*)pool_kv->find(topic))->segregate_input(message, number);
        }
    }
};

static volatile int current_number = 0;

void working(sukp* s) {
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
    auto* s = new sukp();
    if (pool_kv == nullptr) { pool_kv = new rbt(); }
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
#endif

class udp_slave final : public udp {};
static udp_slave* slave = nullptr;
class kcp_slave final : public kcp {
public:
    void handle(const char* message, int number) {
        printf("server:%s\n", message);
        char buf[buffer_length]{0};
        int len = sprintf(buf, "ack.%s", message);
        request(buf, len);
    }
};

static volatile int k_current_number = 0;

void working_k(kcp_slave* s) {
    k_current_number = 1;
    for(;;) {
        if (k_current_number == 0) { break; }
        current(1000);
        char recv_buffer[buffer_length]{0};
        int recv_length = 0;
        // style
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

class udp_master final : public udp {
private:
    const unsigned int k[10] = {0, 195341, 49174, 4894773, 1717, 64, 841, 48964, 8974489, 49784};
    rbt* pool_kv = new rbt();
    kcp_slave* ikps[10] = {};
    std::thread* tds[10] = {};
    unsigned int alive[10] = {};
public:
    void handle(const char* message, int number) {
        if (strcmp(message, "shake") == 0) {
            kcp_slave* ikp = ikps[0];
            int index = 0;
            for (int i = 1; i < 10; i++) {
                if (pool_kv->find(k[i]) == nullptr) {
                    ikp = ikps[i];
                    index = i;
                    break;
                }
            }
            if ((void*)ikp == (void*)ikps) { return; }
            ikp = new kcp_slave();
            std::thread* td = tds[index];
            alive[index] = (now() / 1000) - 1691547700;
            index = static_cast<int>(k[index]);
            ikp->in_it(slave, net_mode::udp, index);
            pool_kv->add_insert(index, ikp);
            if (td != nullptr) { fprintf(stderr, "warning %d thread", index); }
            td = new std::thread(working_k, ikp);
            td->detach();

            char buf[buffer_length]{0};
            int len = sprintf(buf, "%d", index);
            request(buf, len);
        } else if (number >= 10 && number < 20) {
            char c[10] = {};
            strncpy(c, message, 10);
            int ktpc = atoi(message + 10);
            fprintf(stdout, "info %d log %s\n", ktpc, message);
            if (strcmp(c, "keepalive:") == 0) {
                unsigned int j = (now() / 1000) - 1691547700;
                int index = 0;
                for (int i=1; i<10; i++) {
                    if (k[i] == ktpc) {
                        index = i;
                    }
                }
                if ((j - alive[index]) > 10) { fprintf(stderr, "warning %d dead", ktpc); } else {
                    alive[index] = j;
                }
            } else if (strcmp(c, "finish___:")) {
                void* pkvf = pool_kv->find(ktpc);
                void* ksf = nullptr;
                std::thread* td = nullptr;
                for (int i=1; i<10; i++) {
                    if (k[i] == ktpc) {
                        ksf = ikps[i];
                        ikps[i] = nullptr;
                        td = tds[i];
                        tds[i] = nullptr;
                        alive[i] = 0;
                    }
                }
                if (pkvf != ksf) { fprintf(stderr, "warning %d topic", ktpc); }
                pthread_cancel(td->native_handle());
                delete td;
                pool_kv->sub_delete(ktpc);
                static_cast<kcp_slave*>(pkvf)->un_it();
            }
        }
    }
    void check(unsigned int stamp) {
        unsigned int j = (stamp / 1000) - 1691547700;
        for (int i=0; i<10; i++) {
            if (alive[i] != 0) {
                if ((j - alive[i]) > 10) {
                    void* pkvf = pool_kv->find(k[i]);
                    void* ksf = ikps[i];
                    std::thread* td = tds[i];
                    ikps[i] = nullptr;
                    tds[i] = nullptr;
                    alive[i] = 0;
                    if (pkvf != ksf) { fprintf(stderr, "warning %d topic", k[i]); }
                    if (td != nullptr) {
                        pthread_cancel(td->native_handle());
                        delete td;
                    }
                    pool_kv->sub_delete(k[i]);
                    if (pkvf != nullptr) {
                        fprintf(stderr, "warning %d maybe dead", k[i]);
                        static_cast<kcp_slave *>(pkvf)->un_it();
                    }
                }
            }
        }
    }
};

static volatile int current_number = 0;

void working(udp_master* s) {
    current_number = 1;
    for(;;) {
        if (current_number == 0) { break; }
        current(1000);
        char recv_buffer[buffer_length]{0};
        int recv_length = 0;
        recv_length = s->response(recv_buffer, buffer_length);
        if (recv_length < 0) { s->check(now()); continue; }
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
    auto* s = new udp_master();
    if (slave == nullptr) { slave = new udp_slave(); slave->in_it(socket_mode::server, 10245); }
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
