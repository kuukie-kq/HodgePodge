#ifndef INSTRUMENT_TCP_H
#define INSTRUMENT_TCP_H

#include "skt.h"

static const unsigned int backlog = 10;

class tcp : protected net {
private:
    struct socket_h sock;
    char send_buffer[buffer_length] {};
    char recv_buffer[buffer_length] {};
public:
    int camp = 0;
    void in_it(socket_mode m = socket_mode::placeholder, int port = 10246);
    void un_it();
    int shake_hands();
    void wave_hands(int company);
    int response(char* c, int n);
    int request(const char* c, int n);
};

#endif //INSTRUMENT_TCP_H
