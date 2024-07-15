#pragma once

#include"INetMediator.h"
class UdpNet;
class UdpNetMediator :public INetMediator {
public:
	UdpNetMediator();
	~UdpNetMediator();

	//打开网络
	 bool OpenNet();
	//发送数据
	 bool SendData(char* sendData, int len, long ISend);
	//处理数据
	 bool DealData(char* recvData, int len, long ISend);
	//关闭网络
	 bool CloseNet();


};