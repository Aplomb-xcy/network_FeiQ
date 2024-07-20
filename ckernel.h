#ifndef CKERNEL_H
#define CKERNEL_H

#include "imdialog.h"
#include <QObject>
#include "UDPNetMediator.h"
#include<QMap>
#include"chatdialog.h"

class CKernel : public QObject
{
    Q_OBJECT
public:
    explicit CKernel(QObject *parent = nullptr);
    ~CKernel();
    IMDialog* m_pImdialog;
    INetMediator* m_pInetMed;
    QMap<long,ChatDialog*> map_ipTodlg;

public slots:
    //处理数据的槽函数
    void slot_aboutData(char* recvData, int len, long ISend);
    //用户双击的槽函数
    void solt_userClicked(QString ip);
    //处理发送消息的槽函数
    void slot_sendMSG(QString ip,QString content);

public:
    //处理上线请求
    void dealOnlinRq(char* recvData, int len, long ISend);

    //处理上线回复
    void dealOnlinRs(char* recvData, int len, long ISend);

    //处理聊天请求
    void dealChatRq(char* recvData, int len, long ISend);

    //处理下线请求
    void dealOfflineRq(char* recvData, int len, long ISend);



signals:

};

#endif // CKERNEL_H
