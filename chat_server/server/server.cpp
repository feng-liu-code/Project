#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//最大客户端数量
#define MAX_CLIENTS 10
//端口号
#define PROT 8888
//消息缓冲区大小
#define BUFFER_SIZE 1024

//存储所有客户端的socket文件描述符
std::vector<int> client_sockets;
//互斥锁,保护客户端列表(多线程安全)
std::mutex client_mutex;

//广播消息给所有客户端
void broadcast_message(const char* message, int sender_socket) 
{
	//加锁,防止多线程同时修改客户端列表
	std::lock_guard<std::mutex> lock(client_mutex);

	//遍历所有客户端
	for(int client : client_sockets)
	{
		//不发送消息给发送者自己
		if(client != sender_socket)
		{
			send(client, message, strlen(message), 0);
		}
	}
}

//处理单个客户端的线程函数
void handle_client(int client_socket, struct sockaddr_in client_addr)
{
	char buffer[BUFFER_SIZE];
	std::string client_info = inet_ntoa(client_addr.sin_addr) + std::string(":") + std::to_string(ntohs(client_addr.sin_port));
	std::cout << "新客户端连接: " << client_info << std::endl;
	std::string welcome_message = "你已成功加入聊天室！";
	send(client_socket, welcome_message.c_str(), welcome_message.size(), 0);

	//循环接收客户端消息
	while(true)
	{
		memset(buffer, 0, BUFFER_SIZE);
		//读取客户端发送的消息
		ssize_t recv_len = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

		//如果recv返回0,表示客户端断开连接
		if(recv_len <= 0)
		{
			std::cout << "客户端断开连接: " << client_info << std::endl;
			break;
		}

		//拼接完整消息(IP: 端口 + 消息内容)
		std::string full_message = "[" + client_info + "] " + buffer;
		std::cout << "收到消息: " << full_message << std::endl;

		broadcast_message(full_message.c_str(), client_socket);
	}
	//从客户端列表中移除
	std::lock_guard<std::mutex> lock(client_mutex);
	for(auto it = client_sockets.begin(); it != client_sockets.end(); ++it)
	{
		if(*it == client_socket)
		{
			client_sockets.erase(it);
			break;
		}
	}
	close(client_socket);
}

int main()
{
	//1.创建服务器 socket
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd == -1)
	{
		perror("socket 创建失败");
		return -1;
	}

	//2.设置服务器地址结构体
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY; //监听所有网卡
	server_addr.sin_port = htons(PROT); //端口号

	//3.绑定 IP和端口
	if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
	{
		perror("bind 绑定失败");
		close(server_fd);
		return -1;
	}

	//4.开始监听
	if(listen(server_fd, MAX_CLIENTS) == -1)
	{
		perror("listen 监听失败");
		close(server_fd);
		return -1;
	}

	std::cout << "服务器已启动, 监听端口: " << PROT << std::endl;
	std::cout << "等待客户端连接..." << std::endl;

	//5.循环接受客户端连接
	while(true)
	{
		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(client_addr);

		//阻塞等待新客户端连接
		int client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
		if(client_socket == -1)
		{
			perror("accept 接受连接失败");
			continue; //继续等待下一个连接
		}
		//将新客户端加入列表
		std::lock_guard<std::mutex> lock(client_mutex);
		client_sockets.push_back(client_socket);

		//创建线程处理该客户端(分离线程，自动回收)
		std::thread(handle_client, client_socket, client_addr).detach();
	}

	//关闭服务器 socket(理论上不会执行到这里)
	close(server_fd);
	return 0;
}