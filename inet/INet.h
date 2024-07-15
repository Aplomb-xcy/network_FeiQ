#pragma once
#include<process.h>
#include<iostream>
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
};