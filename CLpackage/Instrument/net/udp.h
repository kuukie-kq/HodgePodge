#ifndef INSTRUMENT_UDP_H
#define INSTRUMENT_UDP_H

#include "skt.h"

class udp : protected net {
private:
    struct socket_h sock;
    char send_buffer[buffer_length] {};
    char recv_buffer[buffer_length] {};
public:
    void in_it(socket_mode m = socket_mode::placeholder, int port = 10246);
    void un_it();
    int response(char* c, int n);
    int request(const char* c, int n);
};

#endif //INSTRUMENT_UDP_H
