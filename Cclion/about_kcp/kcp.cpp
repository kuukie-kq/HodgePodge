//
// Created by kuu-kie on 2023-02-23.
//

#include "kcp.h"

static const int max_buffer = 1024;
static const int kcp_topic = 10246;
static int current_number = 0;

#define IO_LEVEL 1

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <thread>
#if PLATFORM
// linux
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#else
#include <winsock2.h>
#endif
#include "ikcp.h"

#define NOW_TIME (std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count())
#define CLOCK (NOW_TIME & 0xFFFFFFFFul)

#define TIME_NOW (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
#define TIME_NO_NANO(time) ((int)(time / 1000000000))
#define TIME_SHOW(time) (printf("[%02d:%02d:%02d]", ((TIME_NO_NANO(time) / 3600 % 24) + 8) % 24, TIME_NO_NANO(time) / 60 % 60, TIME_NO_NANO(time) % 60))

struct SocketAddress{
    int sock_fd;
    #if PLATFORM
    unsigned int server_addr_length;
    unsigned int client_addr_length;
    #else
    int server_addr_length;
    int client_addr_length;
    #endif
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char* recv_line;
    char* send_line;
    SocketAddress() :
    sock_fd(0),
    server_addr_length(0),
    client_addr_length(0),
    recv_line(nullptr),
    send_line(nullptr),
    server_addr(),
    client_addr() {}
};

static void current(unsigned long long millisecond) {
    #if PLATFORM
    usleep((millisecond << 10u) - (millisecond << 4u) - (millisecond << 3u));
    #else
    Sleep(millisecond);
    #endif
}

enum class SocketMode {
    unknow = 0,
    server = 1,
    client = 2
};

struct Address {
    char* send;
    char* recv;
    ikcpcb* kcp;
    SocketMode mode;
    void* user;
    Address() :
    send(nullptr),
    recv(nullptr),
    kcp(nullptr),
    mode(SocketMode::unknow),
    user(nullptr) {}
};

class SocketBuffer {
private:
    SocketAddress sock;
    Address connect;
    char send_buffer[max_buffer]{0};
    char recv_buffer[max_buffer]{0};
    void tick_message(int length) const {
        switch (connect.mode) {
            case SocketMode::server:
                TIME_SHOW(TIME_NOW);
                std::cout << " [info] 服务器 recv " << length << std::endl;
                break;
            case SocketMode::client:
                TIME_SHOW(TIME_NOW);
                std::cout << " [info] 客户端 recv " << length << std::endl;
                break;
            default:
                std::cout << __FUNCTION__ << " [warning] recv package " << length << std::endl;
        }
    }
public:
    void s_in_it(SocketMode mode = SocketMode::unknow, const std::string& host = "127.0.0.1", int port = 10246) {
        #if !PLATFORM
        // windows网络通信组件初始化
        WSAData wsaData{};
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        #endif
        // 使用socket，生成套接字文件描述符
        if ((sock.sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
            std::cerr << __FUNCTION__ << " [error] 生成socket文件描述符" << std::endl;
            exit(1);
        }
        // 通过结构设置服务器地址和监听端口
        memset(&sock.server_addr, 0, sizeof(sock.server_addr));
        sock.server_addr.sin_family = AF_INET;
        #if PLATFORM
        sock.server_addr.sin_addr.s_addr =  htonl(INADDR_ANY);
        #else
        sock.server_addr.sin_addr.s_addr = inet_addr(host.c_str());
        #endif
        sock.server_addr.sin_port = htons(port);
        sock.server_addr_length = sizeof(sock.server_addr);
        // 使用bind绑定监听端口，将套接字文件描述符和地址类型变量绑定
        if (mode == SocketMode::server) {
            if (bind(sock.sock_fd, (struct sockaddr *) &sock.server_addr, sock.server_addr_length) < 0) {
                std::cerr << __FUNCTION__  << " [error] 绑定ip地址&端口" << std::endl;
                exit(1);
            }
        }

        #if !PLATFORM
        // linux 在接收数据的时候通过flag设置非阻塞
        // windows 非阻塞
        unsigned long on = 1;
        if (ioctlsocket(sock.sock_fd, FIONBIO, &on) < 0) {
            std::cerr << __FUNCTION__ << " [error] 设置非阻塞模式\n";
            exit(1);
        }
        #endif
        sock.client_addr_length = sizeof(sock.client_addr);
        sock.send_line = send_buffer;
        sock.recv_line = recv_buffer;
        connect.send = send_buffer;
        connect.recv = recv_buffer;
        connect.mode = mode;
        connect.user = this;
    }

    void s_un_it() {
        #if PLATFORM
        close(sock.sock_fd);
        #else
        closesocket(sock.sock_fd);
        WSACleanup();
        #endif
        sock.send_line = nullptr;
        sock.recv_line = nullptr;
        connect.send = nullptr;
        connect.recv = nullptr;
        connect.mode = SocketMode::unknow;
    }

    int s_recv(char* c, int l) {
        if (connect.mode == SocketMode::unknow) { return -1; }
        memset(sock.recv_line, 0, max_buffer);
        int len;
        #if PLATFORM
        if (connect.mode == SocketMode::server)
            len = recvfrom(sock.sock_fd, sock.recv_line, max_buffer, MSG_DONTWAIT, (struct sockaddr*)&sock.client_addr, &sock.client_addr_length);
        else if (connect.mode == SocketMode::client)
            len = recvfrom(sock.sock_fd, sock.recv_line, max_buffer, MSG_DONTWAIT, (struct sockaddr*)&sock.server_addr, &sock.server_addr_length);
        if(len < 0) {
            int err = errno;
            if (err == 11) { return -11; }
            std::cerr << __FUNCTION__  << " [error] 接收数据 errno:" << err << std::endl;
            exit(1);
        }
        #else
        if (connect.mode == SocketMode::server)
            len = recvfrom(sock.sock_fd, sock.recv_line, max_buffer, 0, (struct sockaddr*)&sock.client_addr, &sock.client_addr_length);
        else if (connect.mode == SocketMode::client)
            len = recvfrom(sock.sock_fd, sock.recv_line, max_buffer, 0, (struct sockaddr*)&sock.server_addr, &sock.server_addr_length);
        if(len < 0) {
            int err = WSAGetLastError();
            if (err == 10035 || err == 10022) { return -11; }
            std::cerr << __FUNCTION__  << " [error] 接收数据 errno:" << err << std::endl;
            exit(1);
        }
        #endif

        memset(c, 0, l);
        memcpy(c, sock.recv_line, len);
        return len;
    }

    int s_send(const char* c, int l) {
        if (connect.mode == SocketMode::unknow) { return -1; }
        memset(sock.send_line, 0, max_buffer);
        memcpy(sock.send_line, c, l);
        int len = 0;
        if (connect.mode == SocketMode::server)
            len = sendto(sock.sock_fd, sock.send_line, l, 0, (struct sockaddr*)&sock.client_addr, sock.client_addr_length);
        else if (connect.mode == SocketMode::client)
            len = sendto(sock.sock_fd, sock.send_line, l, 0, (struct sockaddr*)&sock.server_addr, sock.server_addr_length);
        if(len < 0) {
            std::cerr << __FUNCTION__  << " [error] 发送数据" << std::endl;
            exit(1);
        }
        return len;
    }

    void s_tick(const char* c, int l) const {
        #if IO_LEVEL
        tick_message(l);
        #endif
        if (l <= 0 || connect.mode == SocketMode::unknow) { return; }
        if (connect.mode == SocketMode::server) {
            if (strcmp(c, "SYN") == 0) {
                std::string response = "SYN&ACK";
                ikcp_send(connect.kcp, response.c_str(), response.size());
            } else {
                char response[max_buffer]{0};
                int length = sprintf(response, "[*][work]%s!", c);
                ikcp_send(connect.kcp, response, length);
            }
        } else if (connect.mode == SocketMode::client) {
            std::cout << "client " << l << " : " << c << std::endl;
        }
    }

    Address* get_address() { return &connect; }
};

static int kcp_output(const char *buf, int len, ikcpcb *kcp, void *user) {
    #if IO_LEVEL > 2
    std::cout << __FUNCTION__ << len << std::endl;
    #endif
    auto* output = (SocketBuffer*)user;
    return output->s_send(buf, len);
}

void working(SocketBuffer* sc) {
    current_number = 1;
    for(;;) {
        current(100);
        ikcp_update(sc->get_address()->kcp, ikcp_check(sc->get_address()->kcp, CLOCK));
        char server_recv_buffer[max_buffer]{0};
        int recv_length = 0, kcp_length = 0;

        recv_length = sc->s_recv(server_recv_buffer, max_buffer);
        if (recv_length < 0) { continue; }

        #if IO_LEVEL > 1
        std::cout << "udp sock package size " << recv_length << std::endl;
        #endif
        ikcp_input(sc->get_address()->kcp, server_recv_buffer, recv_length);

        memset(server_recv_buffer, 0, max_buffer);
        for(;;) {
            kcp_length = ikcp_recv(sc->get_address()->kcp, server_recv_buffer, max_buffer);
            if (kcp_length < 0) { break; }
            sc->s_tick(server_recv_buffer, kcp_length);
        }

        if (current_number == 0) break;
    }
}

void terminal_kcp_s() {
    auto* server = new SocketBuffer();
    server->s_in_it(SocketMode::server);

    ikcpcb* kcp = ikcp_create(kcp_topic, server);
    kcp->output = kcp_output;
    ikcp_wndsize(kcp, 128, 128);
    ikcp_nodelay(kcp, 0, 10, 0, 1);

    server->get_address()->kcp = kcp;

    working(server);

    server->get_address()->kcp = nullptr;
    ikcp_release(kcp);
    server->s_un_it();
}
void kcp_server() {
    std::thread td(terminal_kcp_s);
    td.detach();
    for(;;) {
        std::string s;
        std::cin >> s;
        if ("exit" == s) { current_number = 0; pthread_cancel(td.native_handle()); break; }
    }
}

static Address* client_address = nullptr;
void terminal_kcp_c() {
    auto* client = new SocketBuffer();
    client->s_in_it(SocketMode::client);

    ikcpcb* kcp = ikcp_create(kcp_topic, client);
    kcp->output = kcp_output;
    ikcp_wndsize(kcp, 128, 128);
    ikcp_nodelay(kcp, 0, 10, 0, 1);

    client->get_address()->kcp = kcp;
    client_address = client->get_address();

    std::string syn = "SYN";
    ikcp_send(client->get_address()->kcp, syn.c_str(), syn.size());

    working(client);

    client_address = nullptr;
    client->get_address()->kcp = nullptr;
    ikcp_release(kcp);
    client->s_un_it();
    printf("end");
}

void kcp_client() {
    std::thread td(terminal_kcp_c);
    td.detach();
    for(;;) {
        if (client_address == nullptr) continue;
        std::string s;
        std::cin >> s;
        if ("exit" == s) { current_number = 0; pthread_cancel(td.native_handle()); break; }
        ikcp_send(client_address->kcp, s.c_str(), s.size());
    }
}
