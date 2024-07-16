#pragma once
#include <QObject>
class INet;
class INetMediator:public QObject
{
    Q_OBJECT
public:
    INetMediator();
    ~INetMediator() ;

	//打开网络
	virtual bool OpenNet() = 0;
	//发送数据
	virtual bool SendData(char* sendData, int len, long ISend) = 0;
	//处理数据
	virtual bool DealData(char* recvData, int len, long ISend) = 0;
	//关闭网络
	virtual bool CloseNet() = 0;
	INet* p_Net;
};
