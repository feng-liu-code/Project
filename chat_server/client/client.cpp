#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>

#define BUFFER_SIZE 1024

//接收服务器消息的线程
void receive_messages(int sock)
{
	char buffer[BUFFER_SIZE];
	while (true)
	{
		memset(buffer, 0, BUFFER_SIZE);
		ssize_t recv_len = recv(sock, buffer, BUFFER_SIZE - 1, 0);
		if(recv_len <= 0)
		{
			std::cout << "\n与服务器断开连接" << std::endl;
			break;
		}
		std::cout << "\n服务器: " << buffer << "\n你: " << std::flush;
	}
	close(sock);
	exit(0);
}

int main()
{
	//创建客户端socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		perror("socket 创建失败");
		return -1;
	}
	//服务器地址(修改为你的服务器IP)
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);
	if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
	{
		perror("无效的服务器地址");
		return -1;
	}
	//连接服务器
	if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
	{
		perror("连接服务器失败");
		return -1;
	}
	std::cout << "成功链接到聊天室！" << std::endl;
	std::cout << "输入消息发送,输入quit退出" << std::endl;

	std::thread(receive_messages, sock).detach();

	//发送消息
	char buffer[BUFFER_SIZE];
	while (true)
	{
		std::cout << "你: " << std::flush;
		fgets(buffer, BUFFER_SIZE, stdin);
		
		buffer[strcspn(buffer, "\n")] = 0; //去掉换行符

		if(strcmp(buffer, "quit") == 0)
		{
			break;
		}
		send(sock, buffer, strlen(buffer), 0);
	}
	close(sock);
	return 0;
}