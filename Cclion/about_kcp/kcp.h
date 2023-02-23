#ifndef __KCP_H
#define __KCP_H

#ifdef PLATFORM
#undef PLATFORM
#endif
#ifdef linux
#define PLATFORM 1
#else
#define PLATFORM 0
#endif

extern void kcp_server();
extern void kcp_client();

#endif //__KCP_H
