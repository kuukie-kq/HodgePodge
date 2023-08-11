#include <iostream>
#ifdef linux
#include <cstring>
#endif
#include "../plugin/ikcp.h"
#include "kcp.h"
#include "../sys/clock.h"

static int kcp_output(const char* buf, int len, ikcpcb* k, void* user) {
    k; //NOLINT
    auto* output = static_cast<kcp*>(user);
    return output->send_output(buf, len);
}

// static_cast 隐式类型转换 显式
// dynamic_cast 动态类型检查 多继承
// const_cast 无法去除变量的常量性
// reinterpret_cast 对bit数据重新解释

void kcp::in_it(void* s, net_mode t, int topic) {
    if (s == nullptr) {
        fprintf(stderr, "net error");
        return;
    }
    type = t;
    skt = s;
    ikp = ikcp_create(topic, this);
    static_cast<ikcpcb*>(ikp)->output = kcp_output;
    ikcp_wndsize(static_cast<ikcpcb*>(ikp), 128, 128);
    ikcp_nodelay(static_cast<ikcpcb*>(ikp), 0, 10, 0, 1);
}

void kcp::un_it() {
    type = net_mode::placeholder;
    skt = nullptr;
    ikcp_release(static_cast<ikcpcb*>(ikp));
}

int kcp::request(const char* c, int n) {
    return ikcp_send(static_cast<ikcpcb*>(ikp), c, n);
}

int kcp::response(char* c, int n) {
    char recv_buffer[buffer_length] = {0};
    int kcp_length = ikcp_recv(static_cast<ikcpcb*>(ikp), recv_buffer, n);
    if (kcp_length < 0) { return -2; }
    memset(c, 0, n);
    memcpy(c, recv_buffer, kcp_length);
    return kcp_length;
}

int kcp::recv_input() {
    if (type == net_mode::placeholder) { return -4; }
    ikcp_update(static_cast<ikcpcb*>(ikp), ikcp_check(static_cast<ikcpcb*>(ikp), now()));
    char recv_buffer[buffer_length] = {0};
    int recv_length = 0;
    if (type == net_mode::udp) {
        recv_length = (static_cast<udp*>(skt))->response(recv_buffer, buffer_length);
    } else if (type == net_mode::tcp) {}
    if (recv_length < 0) { return -5; }
    return ikcp_input(static_cast<ikcpcb*>(ikp), recv_buffer, recv_length);
}

int kcp::send_output(const char *c, int n) {
    if (type == net_mode::placeholder) { return -1; }
    if (type == net_mode::udp) {
        (static_cast<udp*>(skt))->request(c, n);
    } else if (type == net_mode::tcp) {
        (static_cast<tcp*>(skt))->request(c, n);
    }
}

void kcp::segregate_update() {
    ikcp_update(static_cast<ikcpcb*>(ikp), ikcp_check(static_cast<ikcpcb*>(ikp), now()));
}

void kcp::segregate_input(const char* recv_buffer, int recv_length) {
    ikcp_input(static_cast<ikcpcb*>(ikp), recv_buffer, recv_length);
}
