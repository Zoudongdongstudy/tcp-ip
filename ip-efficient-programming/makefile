# 定义编译器
CC = gcc

# 定义编译选项
CFLAGS = -Wall -g

# 目标可执行文件
CLIENT = tcpclient
SERVER = tcpserver

# 默认目标，编译所有
all: $(CLIENT) $(SERVER)

# 规则：编译客户端
$(CLIENT): tcpclient.c
	$(CC) $(CFLAGS) -o $(CLIENT) tcpclient.c

# 规则：编译服务端
$(SERVER): tcpserver.c
	$(CC) $(CFLAGS) -o $(SERVER) tcpserver.c

# 清理生成的文件
clean:
	rm -f $(CLIENT) $(SERVER)
