#ifndef INSTRUMENT_SKT_H
#define INSTRUMENT_SKT_H

static const unsigned int buffer_length = 1024;

#ifdef _WIN32
#include <winsock2.h>

struct socket_h {
    int sock_fd;
    int server_addr_length;
    int client_addr_length;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char* recv_line;
    char* send_line;
    socket_h() :
    sock_fd(0),
    server_addr_length(0),
    client_addr_length(0),
    server_addr(),
    client_addr(),
    recv_line(nullptr),
    send_line(nullptr) {}
};
#endif

#ifdef linux
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>

struct socket_h {
    int sock_fd;
    unsigned int server_addr_length;
    unsigned int client_addr_length;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char* recv_line;
    char* send_line;
    socket_h() :
    sock_fd(0),
    server_addr_length(0),
    client_addr_length(0),
    server_addr(),
    client_addr(),
    recv_line(nullptr),
    send_line(nullptr) {}
};
#endif

enum class socket_mode {
    server = 10,
    client = 11,
    placeholder //NOLINT
};

class net {
protected:
    socket_mode mode = socket_mode::placeholder;
};

enum class net_mode {
    udp = 1,
    tcp = 2,
    placeholder //NOLINT
};

class protocol {
protected:
    net_mode type = net_mode::placeholder;
};

#endif //INSTRUMENT_SKT_H
