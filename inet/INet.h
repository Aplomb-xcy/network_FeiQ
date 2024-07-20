#pragma once
#include<process.h>
#include<iostream>
#include<set>
#include<winsock2.h>
#include"config.h"

using namespace std;

#pragma comment (lib,"ws2_32.lib")
class INetMediator;
class INet {

public:
	INet() {};
	~INet() {};

	//初始化网络
	virtual bool InitNet() = 0;

	//接收数据
	virtual bool SendData(char* sendData, int len, long ISend) = 0;

	//发送数据
	virtual bool RecvData() = 0;

	//关闭网络
	virtual bool UninitNet() = 0;
	INetMediator* p_NetMed;

    //获取本地ip地址
    static std::set<long> getVailedIP(){
        set<long> ip_Set;
        char name[100]="";
        struct hostent *remoteHost;
        int i=0;
        //获取本地主机名
        gethostname(name,sizeof(name));
        //根据主机名获取ip地址放入set中
        remoteHost=gethostbyname(name);
        while (remoteHost->h_addr_list[i] != 0) {
            ip_Set.insert( *(u_long *) remoteHost->h_addr_list[i++]);
        }
        return ip_Set;
    }

    static std::string getIPString(long IP){
        sockaddr_in addr;
        addr.sin_addr.S_un.S_addr=IP;
        return inet_ntoa(addr.sin_addr);
    }
};
