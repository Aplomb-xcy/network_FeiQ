#include "ckernel.h"
#include <QMessageBox>
#include "INet.h"
CKernel::CKernel(QObject *parent) : QObject(parent)
{
    //在kernel类中申请会话界面，并且显示出来
    qDebug()<<__func__;
    m_pImdialog=new IMDialog;
    m_pImdialog->show();

    //申请中介者类的空间
    m_pInetMed=new UdpNetMediator;

    //绑定信号和槽函数的位置：在接收数据的类中申请从那接受的类的new下边
    connect(m_pInetMed,SIGNAL(SIG_aboutData(char* , int , long )),this,SLOT(slot_aboutData(char* , int , long )));

    //初始化网络
    if(!m_pInetMed->OpenNet()){
        //初始化网络失败
        QMessageBox::about(m_pImdialog,"提示","打开网络失败");
    }


    //测试代码，发送数据
    m_pInetMed->SendData("你好，金琪瑞",sizeof("你好，金琪瑞"),INADDR_BROADCAST);
}

CKernel::~CKernel()
{
    qDebug()<<__func__;
}

void CKernel::slot_aboutData(char *recvData, int len, long ISend)
{
    qDebug()<<__func__;
    qDebug()<<recvData;
}
