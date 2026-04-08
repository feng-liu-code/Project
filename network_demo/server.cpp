#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


using namespace std;

#define PORT 6666

int main() {
    //创建socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) {
        perror("socket failed");
        return -1;
    }

    //配置地址
    sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr =htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    //绑定
    if(bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind faild");
        close(server_fd);
        return -1;
    }

    //监听
    if(listen(server_fd, 5) < 0) {
        perror("listen faild");
        close(server_fd);
        return -1;
    }

    cout << "服务端已启动，等待客户端进行连接..." << endl;

    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);  // 必须正确初始化！
    memset(&client_addr, 0, sizeof(client_addr));

    int new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (new_socket < 0) {
        perror("accept failed");
        close(server_fd);
        return -1;
    }

    cout << "客户端已连接！！！" << endl;

    //收发消息
    char buffer[1024];
    while(true) {
        memset(buffer, 0, sizeof(buffer));
        int ret = recv(new_socket, buffer, sizeof(buffer)-1, 0);
        if(ret <= 0 || strcmp(buffer, "exit") == 0) {
            cout << "客户端已断开连接" << endl;
            break;
        }
    cout << "客户端: " << buffer << endl;
    cout << "服务端: ";
    cin.getline(buffer, sizeof(buffer)-1);
    send(new_socket, buffer, strlen(buffer), 0);

    if(strcmp(buffer, "exit") == 0) {
        cout << "服务端断开连接" << endl;
        break;;
    }
    }

    close(new_socket);
    close(server_fd);
    return 0;

}