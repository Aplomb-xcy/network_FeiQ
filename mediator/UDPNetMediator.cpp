#include"UDPNetMediator.h"
#include"UDPNet.h"
UdpNetMediator::UdpNetMediator() {
	p_Net = new UdpNet(this);
}
UdpNetMediator::~UdpNetMediator() {
	delete p_Net;
	p_Net = nullptr;
}

//打开网络
bool UdpNetMediator::OpenNet() {
	return p_Net->InitNet();
}
//发送数据
bool UdpNetMediator::SendData(char* sendData, int len, long ISend) {
	return p_Net->SendData(sendData, len, ISend);
}
//处理数据
bool UdpNetMediator::DealData(char* recvData, int len, long ISend) {
	cout << "UdpNetMediator:: DealData : " << recvData << endl;
	return true;
}
//关闭网络
bool UdpNetMediator::CloseNet() {
	return p_Net->UninitNet();
}