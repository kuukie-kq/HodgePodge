#include <iostream>
#include "tcp.h"
#ifdef linux
#include <cstring> //memset
#endif

#ifdef WIN32
void tcp::in_it(socket_mode m, int port) {
    WSAData wsaData{};
    WSAStartup(MAKEWORD(2, 2), &wsaData); //NOLINT

    if ((sock.sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
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
        if (listen(sock.sock_fd, backlog) < 0) {
            fprintf(stderr, "socket listen error");
            return;
        }
    }

    sock.client_addr_length = sizeof(sock.client_addr);
    sock.send_line = send_buffer;
    sock.recv_line = recv_buffer;
    mode = m;
    camp = 0;
    memset(send_buffer, 0, buffer_length);
    memset(recv_buffer, 0, buffer_length);
}

void tcp::un_it() {
    closesocket(sock.sock_fd);
    WSACleanup();
    sock.send_line = nullptr;
    sock.recv_line = nullptr;
    mode = socket_mode::placeholder;
}
#endif

int tcp::shake_hands() { //NOLINT
    int company = 0;
    if ((company = accept(sock.sock_fd, nullptr, nullptr)) < 0) {
        fprintf(stderr, "socket listen error");
        return -1;
    }
    return company;
}

void tcp::wave_hands(int company) { //NOLINT
    closesocket(company);
}

int tcp::request(const char *c, int n) {
    memset(sock.send_line, 0, buffer_length);
    memcpy(sock.send_line, c, n);
    int len = 0;
    if (socket_mode::server == mode) {
        if (camp != 0) {
            len = send(camp, sock.send_line, n, 0);
            camp = 0;
        }
    } else if (socket_mode::client == mode) {
        len = send(sock.sock_fd, sock.send_line, n, 0);
    }
    if (len < 0) {
        fprintf(stderr, "socket request error");
        return -1;
    }
    return len;
}

int tcp::response(char *c, int n) {
    memset(sock.recv_line, 0, buffer_length);
    int len = 0;
    if (socket_mode::server == mode) {
        if (camp != 0) {
            len = recv(camp, sock.recv_line, buffer_length, 0);
            camp = 0;
        }
    } else if (socket_mode::client == mode) {
        len = recv(sock.sock_fd, sock.recv_line, buffer_length, 0);
    }
    if (len < 0) {
        fprintf(stderr, "socket response error");
        return -1;
    }
    memset(c, 0, n);
    memcpy(c, sock.recv_line, len);
    return len;
}
