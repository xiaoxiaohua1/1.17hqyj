#ifndef RECV_H
#define RECV_H

#include <stdio.h>
#include <sys/types.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "sqlite.h"


#define ERR_MSG(msg) do{\
    printf("line = %d\n",__LINE__);\
    perror(msg);\
}while(0)

#define PORT 9999
#define IP "192.168.1.123"

struct CliMsg
{
    struct sockaddr_in cin;
    int newfd;
	sqlite3 *db;
};
//void* recv_cli_msg(void* arg)

int create_pthread_recv();
void* recv_cli_msg(void* arg);

#endif
