#include "ckernel.h"
#include <QMessageBox>
#include"config.h"
#include "INet.h"
CKernel::CKernel(QObject *parent) : QObject(parent)
{
    //在kernel类中申请会话界面，并且显示出来
    qDebug()<<__func__;
    m_pImdialog=new IMDialog;
    m_pImdialog->show();
    connect(m_pImdialog,SIGNAL(SIG_userClicked(QString)),this,SLOT(solt_userClicked(QString)));

    //申请中介者类的空间
    m_pInetMed=new UdpNetMediator;

    //绑定信号和槽函数的位置：在接收数据的类中申请从那发送的类的new下边
    connect(m_pInetMed,SIGNAL(SIG_aboutData(char* , int , long )),this,SLOT(slot_aboutData(char* , int , long )));

    //初始化网络
    if(!m_pInetMed->OpenNet()){
        //初始化网络失败
        QMessageBox::about(m_pImdialog,"提示","打开网络失败");
    }

    //m_pInetMed->SendData("你好，金琪瑞",sizeof("你好，金琪瑞"),INADDR_BROADCAST);
    //测试广播，告知上线，发送数据
    struct STRU_UDP_ONLINE onlin_rq;
    onlin_rq.type=_DEF_UDP_ONLINE_RQ;
    gethostname(onlin_rq.name,sizeof(onlin_rq.name));
    m_pInetMed->SendData((char*)&onlin_rq,sizeof(onlin_rq),INADDR_BROADCAST);
}

CKernel::~CKernel()
{
    qDebug()<<__func__;
}

void CKernel::slot_aboutData(char *recvData, int len, long ISend)
{

    qDebug()<<__func__;
    //qDebug()<<recvData;
    //发送的广播，自己也能收到
    int type=*(int*)recvData;
    switch(type){
    case _DEF_UDP_ONLINE_RQ:{
        dealOnlinRq(recvData,  len,  ISend);
        break;
    }
    case _DEF_UDP_ONLINE_RS:{
        dealOnlinRs(recvData,  len,  ISend);
        break;
    }
    case _DEF_UDP_CHAT_RQ:{
        dealChatRq(recvData,  len,  ISend);
        break;
    }
    case _DEF_UDP_OFFLINE_RQ:{
        dealOfflineRq(recvData,  len,  ISend);
        break;
    }
    }

}
//处理用户双击的槽函数
void CKernel::solt_userClicked(QString ip)
{
    qDebug()<<__func__;
}
//处理上线请求
void CKernel::dealOnlinRq(char *recvData, int len, long ISend)
{
    qDebug()<<__func__;
    //拆包
    struct STRU_UDP_ONLINE* online_RQ=(struct STRU_UDP_ONLINE*)recvData;
    qDebug()<<online_RQ->name;
    qDebug()<<online_RQ->type;
    //将该好友添加到聊天列表中
    m_pImdialog->addFriend("192.168.1.5",online_RQ->name);
    //创建聊天窗口

    //将聊天窗口放到map中，key是ip，value是聊天窗口

    //判断是不是自己发送的广播

    //不是自己，发送一个上线回复

}
//处理上线回复
void CKernel::dealOnlinRs(char *recvData, int len, long ISend)
{
    qDebug()<<__func__;
}
//处理聊天请求
void CKernel::dealChatRq(char *recvData, int len, long ISend)
{
    qDebug()<<__func__;
}
//处理下线请求
void CKernel::dealOfflineRq(char *recvData, int len, long ISend)
{
    qDebug()<<__func__;
}
