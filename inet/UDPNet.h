#pragma once

#include"INet.h"

class UdpNetMediator;
class UdpNet: public INet {

public:
	UdpNet(UdpNetMediator* p_UdpMed);
	~UdpNet();

	//初始化网络
	bool InitNet();
	static unsigned __stdcall recvDataThread(void* ignored);

	//接收数据
	bool SendData(char* sendData, int len, long ISend);

	//发送数据
	bool RecvData();

	//关闭网络
	bool UninitNet();
private:
	
	SOCKET sock;
	HANDLE hand;
	bool is_Stop;
};