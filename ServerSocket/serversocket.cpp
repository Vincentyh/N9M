#include "serversocket.h"

using namespace std;

ServerSocket::ServerSocket(string input_ip,unsigned short input_port):ip(input_ip),port(input_port)
{
    cout << this->ip << endl;
    cout << this->port << endl;
}

ServerSocket::~ServerSocket()
{
    cout << "socket已销毁" << endl;
    close(sockfd);
	close(client_fd);
}

void ServerSocket::set_socket_bind()
{
    memset(&my_addr, 0, sizeof(struct sockaddr_in));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = inet_addr((char*)ip.c_str());

    if(bind(sockfd, (struct sockaddr *)&my_addr,
            sizeof(struct sockaddr)) == -1)
    {
        perror("绑定失败");
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::creat_socket()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sockfd)
    {
        perror("创建socket失败");
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::set_listen()
{
    if(listen(sockfd, 5) == -1)
    {
        perror("监听socket失败");
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::set_accept()
{
    socklen_t len = sizeof(struct sockaddr_in);
    client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &len);
    if(-1 == client_fd)
    {
        perror("接收socket失败");
        exit(EXIT_FAILURE);
    }
	cout << "client connected, client from" << inet_ntoa(client_addr.sin_addr) << endl;
}

int ServerSocket::msg_send(const char *buf, int len)
{
    int res = send(client_fd, buf, len, 0);
    if(-1 == res)
    {
        perror("msg_send error");
    }
    return res;
}

int ServerSocket::msg_sendto(const char *buf, int len)
{
    int res = sendto(sockfd, buf, len, 0,
                 (struct sockaddr *)&their_addr,sizeof(struct sockaddr));
    if(-1 == res)
    {
        perror("msg_sendto error");
    }
    return res;
}

int ServerSocket::msg_rev(char *buf, int len)
{
    int res = recv(client_fd, buf, len, 0);
    if(-1 == res)
    {
        perror("msg_rev error");
    }
    return res;
}

int ServerSocket::msg_revfrom(char *buf, int len)
{
    int res;
    socklen_t addr_len = sizeof(client_addr);
    res = recvfrom(sockfd,buf,len,0,(struct sockaddr *)&client_addr,&addr_len);
    if(-1 == res)
    {
        perror("msg_revfrom error");
    }
    return res;
}

void TCPserver::creat_socket()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sockfd)
    {
        perror("创建socket失败");
        exit(EXIT_FAILURE);
    }
}

void UDPserver::creat_socket()
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(-1 == sockfd)
    {
        perror("创建socket失败");
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::handle()
{
	cout << "client from" << inet_ntoa(client_addr.sin_addr) << endl;
	char buf[512];
	ssize_t n;
	while((n = msg_rev(buf, 512)) > 0)
	{
		buf[n] = '\0';
		cout << "client:" << buf << endl;
		cout << "length:" << strlen(buf) << endl;
		bzero(&buf, sizeof(buf));
	}
	
}


int main()
{

    ServerSocket tcp_server("192.168.150.21", 245);
	tcp_server.creat_socket();
	tcp_server.set_socket_bind();
	tcp_server.set_listen();
	tcp_server.set_accept();
	tcp_server.handle();

    return 0;

}
