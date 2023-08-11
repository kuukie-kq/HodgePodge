#include <iostream>
#include "udp.h"
#ifdef linux
#include <cstring> //memset

void udp::in_it(socket_mode m, int port) {
    if ((sock.sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        fprintf(stderr, "socket error");
        return;
    }
    memset(&sock.server_addr, 0, sizeof(sock.server_addr));
    sock.server_addr.sin_family = AF_INET;
    sock.server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock.server_addr.sin_port = htons(port);
    sock.server_addr_length = sizeof(sock.server_addr);

    if (socket_mode::server == m) {
        if (bind(sock.sock_fd, (struct sockaddr*)&sock.server_addr, sock.server_addr_length) < 0) {
            fprintf(stderr, "socket bind error");
            return;
        }
    }

    sock.client_addr_length = sizeof(sock.client_addr);
    sock.send_line = send_buffer;
    sock.recv_line = recv_buffer;
    mode = m;
    memset(send_buffer, 0, buffer_length);
    memset(recv_buffer, 0, buffer_length);
}

void udp::un_it() {
    close(sock.sock_fd);
    sock.send_line = nullptr;
    sock.recv_line = nullptr;
    mode = socket_mode::placeholder;
}
#endif

#ifdef _WIN32
void udp::in_it(socket_mode m, int port) {
    WSAData wsaData{};
    WSAStartup(MAKEWORD(2, 2), &wsaData); //NOLINT

    if ((sock.sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        fprintf(stderr, "socket error");
        return;
    }
    memset(&sock.server_addr, 0, sizeof(sock.server_addr));
    sock.server_addr.sin_family = AF_INET;
    // TODO change
    sock.server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sock.server_addr.sin_port = htons(port);
    sock.server_addr_length = sizeof(sock.server_addr);

    if (socket_mode::server == m) {
        if (bind(sock.sock_fd, (struct sockaddr*)&sock.server_addr, sock.server_addr_length) < 0) {
            fprintf(stderr, "socket bind error");
            return;
        }
    }

    unsigned long on = 1;
    if (ioctlsocket(sock.sock_fd, FIONBIO, &on) < 0) { //NOLINT
        fprintf(stderr, "socket non-blocking error");
        return;
    }

    sock.client_addr_length = sizeof(sock.client_addr);
    sock.send_line = send_buffer;
    sock.recv_line = recv_buffer;
    mode = m;
    memset(send_buffer, 0, buffer_length);
    memset(recv_buffer, 0, buffer_length);
}

void udp::un_it() {
    closesocket(sock.sock_fd);
    WSACleanup();
    sock.send_line = nullptr;
    sock.recv_line = nullptr;
    mode = socket_mode::placeholder;
}
#endif

int udp::request(const char *c, int n) {
    memset(sock.send_line, 0, buffer_length);
    memcpy(sock.send_line, c, n);
    int len = 0;
    if (socket_mode::server == mode) {
        len = sendto(sock.sock_fd, sock.send_line, n, 0, (struct sockaddr*)&sock.client_addr, sock.client_addr_length);
    } else if (socket_mode::client == mode) {
        len = sendto(sock.sock_fd, sock.send_line, n, 0, (struct sockaddr*)&sock.server_addr, sock.server_addr_length);
    }
    if (len < 0) {
        fprintf(stderr, "socket request error");
        return -1;
    }
    return len;
}

int udp::response(char *c, int n) {
    memset(sock.recv_line, 0, buffer_length);
    int len = 0;
#ifdef linux
    if (socket_mode::server == mode) {
        len = recvfrom(sock.sock_fd, sock.recv_line, buffer_length, MSG_DONTWAIT, (struct sockaddr*)&sock.client_addr, &sock.client_addr_length);
    } else if (socket_mode::client == mode) {
        len = recvfrom(sock.sock_fd, sock.recv_line, buffer_length, MSG_DONTWAIT, (struct sockaddr*)&sock.server_addr, &sock.server_addr_length);
    }
    if (len < 0) {
        int error_num = errno;
        if (11 == error_num) { return -11; }
        fprintf(stderr, "socket recv error");
        return -1;
    }
#else
    if (socket_mode::server == mode) {
        len = recvfrom(sock.sock_fd, sock.recv_line, buffer_length, 0, (struct sockaddr*)&sock.client_addr, &sock.client_addr_length);
    } else if (socket_mode::client == mode) {
        len = recvfrom(sock.sock_fd, sock.recv_line, buffer_length, 0, (struct sockaddr*)&sock.server_addr, &sock.server_addr_length);
    }
    if (len < 0) {
        int error_num = WSAGetLastError();
        if (10035 == error_num || 10022 == error_num) { return -11; }
        fprintf(stderr, "socket response error");
        return -1;
    }
#endif
    memset(c, 0, n);
    memcpy(c, sock.recv_line, len);
    return len;
}
