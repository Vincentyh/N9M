#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

//hhh

class ServerSocket
{
public:
    ServerSocket(string input_ip, unsigned short input_port);
    virtual ~ServerSocket();
    virtual void creat_socket();//默认创建tcp类型的socket
    void set_socket_bind();
    void set_listen();
    void set_accept();
    int msg_send(const char *buf, int len); //tcp发送数据
    int msg_rev(char *buf, int len);     //tcp接收数据
    int msg_sendto(const char *buf, int len);  //udp发送数据
    int msg_revfrom(char *buf, int lens);     //udp接收数据
    void handle();  //处理数据

protected:
    string ip;
    unsigned short port;
    int sockfd;
    int client_fd;
    struct sockaddr_in my_addr; //以太网套接字地址结构
    struct sockaddr_in client_addr;   //客户端连接的地址信息
    struct sockaddr_in their_addr;
};

class TCPserver:public ServerSocket
{
public:
    void creat_socket();
};

class UDPserver:public ServerSocket
{
public:
    void creat_socket();
};

#endif // SERVERSOCKET_H
