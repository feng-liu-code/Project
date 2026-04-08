#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define PORT 6666

int main() {
    //创建socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("socket failed");
        return -1;
    }

    //服务器地址
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t len = sizeof(serv_addr);  // 必须初始化长度
    if (connect(sock, (struct sockaddr *)&serv_addr, len) < 0) {
        perror("connect failed");
        close(sock);
        return -1;
    }
    cout << "连接成功！！！" << endl;

    //收发消息
    char buffer[1024];
    while(true) {
        cout << "客户端: ";
        cin.getline(buffer, sizeof(buffer)-1);
        send(sock, buffer, strlen(buffer), 0);

        if(strcmp(buffer, "exit") ==0) {
            cout << "断开连接！！！" << endl;
            break;
        }
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer)-1, 0);
    cout << "服务端: " << buffer << endl;
    }
    close(sock);
    return 0;
}