#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

/// @brief 将sockaddr_in结构体清零，并将地址族设置为AF_INET
/// @param hname 
/// @param sname 
/// @param sap 
/// @param protocol 
static void set_address(char *hname, char *sname, struct sockaddr_in *sap, char *protocol);


#endif /* __TCP_SERVER_H__ */