//
// Created by kuukie on 2021/7/24.
//

#ifndef XTEST_RPCSC_H
#define XTEST_RPCSC_H

#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
using namespace std;

#define MAX 1024
#define PORT 8558

//字符串分割函数
vector<string> split(string str,string pattern) {
    string::size_type pos;
    vector<string> result;
    str+=pattern;  //扩展字符串以方便操作
    int size=str.size();
    for(int i=0;i<size;i++) {
        pos=str.find(pattern,i);
        if(pos<size) {
            string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

class RpcService {
private:
    int serverSockfd;
    unsigned int server_addr_length;
    unsigned int client_addr_length;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    char recvline[MAX];
    char sendline[MAX];
public:
    int server() {
        //使用socket，生成套接字文件描述符
        if((serverSockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0) {
            cerr << "server first socket error\n";
            exit(1);
        }
        //通过sockaddr_in结构设置服务器地址和监听端口
        bzero(&serveraddr,sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serveraddr.sin_port = htons(PORT);
        server_addr_length = sizeof(serveraddr);
        //使用bind绑定监听端口，将套接字文件描述符和地址类型变量绑定
        if(bind(serverSockfd,(struct sockaddr*)&serveraddr,server_addr_length) < 0) {
            cerr << "server first bind error\n";
            exit(1);
        }

        //请求数据
        client_addr_length = sizeof(sockaddr_in);
        int recv_length = 0;
        recv_length = recvfrom(serverSockfd,recvline,sizeof(recvline),0,(struct sockaddr*)&clientaddr,&client_addr_length);
        if(recv_length < 0) {
            cerr << "server recvfrom error\n";
        }


        //自定义业务部分
        string request = recvline;
        cout << request << "\n";
        vector<string> words = split(request,"-");
        for(int i=0;i<words.size();i++) {
            if(words[i] == "login" && i == 0 && words.size() == 3)
                sprintf(sendline,"%d",login(atoi(words[1].c_str()),atoi(words[2].c_str())));
        }

        //响应数据
        int send_length = 0;
        cout << sendline << endl;
        send_length = sendto(serverSockfd,sendline,sizeof(sendline),0,(struct sockaddr*)&clientaddr,client_addr_length);
        if(send_length < 0) {
            cerr << "server sendto error\n";
        }

        close(serverSockfd);//析构
        return 0;
    }

    //自定义业务部分
    int login(int name,int password) {
        cout << "logging ...\n";
        sleep(2);//查找数据库
        return 123;
    }
};

class RpcCustomer {
private:
    int customerSockfd;
    unsigned int server_addr_length;
    struct sockaddr_in serveraddr;
    char recvline[MAX];
    char sendline[MAX];
public:
    int client(char* &data) {
        //使用socket，生成套接字文件描述符
        if((customerSockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0) {
            cerr << "client first socket error\n";
            exit(1);
        }
        //通过sockaddr_in结构设置服务器地址和监听端口
        bzero(&serveraddr,sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serveraddr.sin_port = htons(PORT);
        server_addr_length = sizeof(serveraddr);
        //数据请求
        int send_length = 0;
        sprintf(sendline,"%s", data);
        send_length = sendto(customerSockfd,sendline,sizeof(sendline),0,(struct sockaddr*)&serveraddr,server_addr_length);
        if(send_length < 0) {
            cerr << "client sendto error\n";
            exit(1);
        }
        //数据响应
        int recv_length = 0;
        recv_length = recvfrom(customerSockfd,recvline,sizeof(recvline),0,(struct sockaddr*)&serveraddr,&server_addr_length);
        if(recv_length < 0) {
            cerr << "client recvfrom error\n";
            exit(1);
        }
        cout << recvline << endl;
        string response = recvline;
        data = (char*)response.c_str();
        printf("data:%s\n",data);
        close(customerSockfd);
        return 0;
    }

    //自定义业务部分
    int login(int name,int password) {
        char data[MAX];
        sprintf(data,"login-%d-%d",name,password);
        char* request = data;
        client(request);
        //解返回数据
        int re = atoi(((string)request).c_str());
        cout << re <<endl;
        return re;
    }
};

//rpc工具自动生成//^

void server() {
    RpcService* rpcService = new RpcService();
    for(int i=0;i<3;i++)
        rpcService->server();
}

void client() {
    RpcCustomer* rpcCustomer = new RpcCustomer();
    int l = rpcCustomer->login(123,123);
    cout << l << "The End\n";
}

#endif //XTEST_RPCSC_H
