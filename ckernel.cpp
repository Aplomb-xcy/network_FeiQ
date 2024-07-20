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
    long IP=inet_addr(ip.toStdString().c_str());
    if(map_ipTodlg.count(IP)){
        ChatDialog* p_chat=map_ipTodlg[IP];
        p_chat->showNormal();
    }
}

void CKernel::slot_sendMSG(QString ip, QString content)
{
    qDebug()<<__func__;
    //根据ip找到聊天窗口
    long LIP=inet_addr(ip.toStdString().c_str());
    if(map_ipTodlg.count(LIP)>0){
        ChatDialog* p_chat=map_ipTodlg[LIP];
        p_chat->setMessage(content);
        p_chat->showNormal();
    }

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
    m_pImdialog->addFriend(INet::getIPString(ISend).c_str(),online_RQ->name);
    //创建聊天窗口
    ChatDialog* p_chatdlg=new ChatDialog;
    p_chatdlg->setWindowInfo(INet::getIPString(ISend).c_str());

    connect(p_chatdlg,SIGNAL(SIG_sendMSG(QString,QString )),this,SLOT(slot_sendMSG(QString,QString )));

    //将聊天窗口放到map中，key是ip，value是聊天窗口
    map_ipTodlg[ISend]=p_chatdlg;
    //判断是不是自己发送的广播

    set<long> ip_Set=INet::getVailedIP();
    if(ip_Set.count(ISend)>0){
        return;
    }
    //不是自己，发送一个上线回复
    struct STRU_UDP_ONLINE online_rs;
    online_rs.type=_DEF_UDP_ONLINE_RS;
    gethostname(online_rs.name,sizeof(online_rs.name));
    m_pInetMed->SendData((char*)&online_rs,sizeof(online_rs),ISend);
}
//处理上线回复
void CKernel::dealOnlinRs(char *recvData, int len, long ISend)
{
    qDebug()<<__func__;
    //拆包
    struct STRU_UDP_ONLINE* online_RQ=(struct STRU_UDP_ONLINE*)recvData;
    qDebug()<<online_RQ->name;
    qDebug()<<online_RQ->type;
    //将该好友添加到聊天列表中
    m_pImdialog->addFriend(INet::getIPString(ISend).c_str(),online_RQ->name);
    //创建聊天窗口
    ChatDialog* p_chatdlg=new ChatDialog;
    p_chatdlg->setWindowInfo(INet::getIPString(ISend).c_str());

    connect(m_pImdialog,SIGNAL(SIG_sendMSG(QString,QString )),this,SLOT(slot_sendMSG(QString,QString )));

    //将聊天窗口放到map中，key是ip，value是聊天窗口
    map_ipTodlg[ISend]=p_chatdlg;
}
//处理聊天请求
void CKernel::dealChatRq(char *recvData, int len, long ISend)
{
    qDebug()<<__func__;
    struct STRU_UDP_CHAT_RQ* chat_rq=(struct STRU_UDP_CHAT_RQ*)recvData;
    if(map_ipTodlg.count(ISend)<=0)return;
    ChatDialog* p_chat=map_ipTodlg[ISend];
    p_chat->setMessage(chat_rq->content);
    p_chat->showNormal();
    qDebug()<<__func__;
}
//处理下线请求
void CKernel::dealOfflineRq(char *recvData, int len, long ISend)
{
    qDebug()<<__func__;
}
