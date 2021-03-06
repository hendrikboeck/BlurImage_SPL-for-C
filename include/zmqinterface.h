#ifndef _zmqinterface_h
#define _zmqinterface_h

#include "cslib.h"
#include "strlib.h"

typedef unsigned char byte;
typedef struct ZMQInterfaceCDT *ZMQInterface;

ZMQInterface newZMQInterface(int port_recv, int port_send);
void updateClientPort(ZMQInterface iface, int port_send);
void freeZMQInterface(ZMQInterface iface);
void sendString(ZMQInterface iface, string str, bool last);
string recvString(ZMQInterface iface, int buffer_len);
void sendIntArray(ZMQInterface iface, int *arr, int len, bool last);
void recvIntArray(ZMQInterface iface, int **arr);
void sendConfirmationReply(ZMQInterface iface);

#endif