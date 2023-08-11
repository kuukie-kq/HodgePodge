#include <cstdio>
#include <cstdarg>
#include "deal.h"

void deal::handle_arguments(const char *format, ...) { //NOLINT
    char buffer[1024] = {0};
    va_list args;
    va_start(args, format);
    int length = vsnprintf(buffer, 1024, format, args);
    if (length < 0) {
        fprintf(stderr, "vsn printf error");
    }
    // TODO json analysis
    va_end(args);
}
