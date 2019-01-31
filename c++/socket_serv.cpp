#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
	//创建嵌套字
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//将嵌套字和IP、端口绑定
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr)); //每个字节都用0填充
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(1234);
	bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	//进入监听状态，等待用户发起请求
	listen(serv_sock, 20);

	//接受客户端请求
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

	//向客户端发送数据
	char str[] = "hello world";
	write(clnt_sock, str, sizeof(str));

	//关闭嵌套字
	close(clnt_sock);
	close(serv_sock);

	return 0;

}
