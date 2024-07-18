#include"UDPNet.h"
#include"UDPNetMediator.h"

UdpNet::UdpNet(UdpNetMediator * p_UdpMed):hand(NULL),sock(NULL),is_Stop(0) {
    p_NetMed = p_UdpMed;
}
UdpNet::~UdpNet() {

}

//初始化网络
bool UdpNet::InitNet() {
	//加载库
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        return false;
    }

    /* Confirm that the WinSock DLL supports 2.2.*/
    /* Note that if the DLL supports versions greater    */
    /* than 2.2 in addition to 2.2, it will still return */
    /* 2.2 in wVersion since that is the version we      */
    /* requested.                                        */

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        printf("Could not find a usable version of Winsock.dll\n");
        return false;
    }
    else {
        printf("The Winsock 2.2 dll was found okay\n");
    }
	//创建套接字
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (INVALID_SOCKET == sock) {
        cout << "socket error   " << WSAGetLastError() << endl;
        return false;
    }
    else {
        cout << "socket success" << endl;
    }
    BOOL bval=TRUE;
    setsockopt(sock,SOL_SOCKET,SO_BROADCAST,(const char*)&bval,sizeof(bval));
	//绑定ip地址
    sockaddr_in sendAddr;
    sendAddr.sin_family = AF_INET;
    sendAddr.sin_port = htons(SEND_HOST);
    sendAddr.sin_addr.S_un.S_addr = INADDR_ANY;

    err = bind(sock, (sockaddr*)&sendAddr, sizeof(sendAddr));
    if (SOCKET_ERROR == err) {
        cout << "bind error   " << WSAGetLastError() << endl;
        return false;
    }
    else {
        cout << "bind success" << endl;
    }
	//创建接收数据的线程
    hand = (HANDLE)_beginthreadex(0, 0, &recvDataThread, this, 0, NULL);
    if (hand) {
        cout << "create thread success" << endl;
    }
    else {
        cout << "create thread error" << endl;
        return false;
    }

	return true;
}
unsigned __stdcall UdpNet::recvDataThread(void* ignored){
    //调用RecvData
    //RecvData();
    //通过this指针调用成员函数
    UdpNet* p_This = (UdpNet*)ignored;
    p_This->RecvData();
    return true;
}

//发送数据
bool UdpNet::SendData(char* sendData, int len, long ISend) {
    sockaddr_in sendAddr;
    sendAddr.sin_family = AF_INET;
    sendAddr.sin_port = htons(SEND_HOST);
    sendAddr.sin_addr.S_un.S_addr = ISend;
    if (SOCKET_ERROR == sendto(sock, sendData, len, 0, (sockaddr*)&sendAddr, sizeof(sendAddr))) {
        cout << "send error    " << WSAGetLastError() << endl;
        return false;
    }
    else {
        cout << "send success" << endl;
        return true;
    }
}

//接收数据
bool UdpNet::RecvData() {
    int RecvNum = 0;
    char RecvBuf[4096];
    sockaddr_in addr;
    int len = sizeof(addr);
    while (!is_Stop) {
        RecvNum = recvfrom(sock, RecvBuf, sizeof(RecvBuf), 0, (sockaddr*)&addr, &len);
        if (RecvNum > 0) {
            p_NetMed->DealData(RecvBuf, RecvNum, addr.sin_addr.S_un.S_addr);
        }
        else {
            cout << "RecvData error" <<WSAGetLastError() <<endl;
            return false;
            break;
        }
    }
    return true;
}

//关闭网络
bool UdpNet::UninitNet() {
    is_Stop = true;
    if (WAIT_TIMEOUT == WaitForSingleObject(hand, 500)) {
        TerminateThread(hand,-1);
        CloseHandle(hand);
    }
    //关闭套接字
    if (sock && sock != INVALID_SOCKET) {
        closesocket(sock);
    }
    WSACleanup();
    return true;
}
