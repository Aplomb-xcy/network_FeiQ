#include "chatdialog.h"
#include "ui_chatdialog.h"
#include<QTime>
#include<QDebug>

ChatDialog::ChatDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::setWindowInfo(QString ip)
{
    qDebug()<<__func__;
    m_ip=ip;
    setWindowTitle(QString("与【%1】的聊天").arg(m_ip));
}

void ChatDialog::setMessage(QString content)
{
    qDebug()<<__func__;
    ui->tb_chat->append(QString("【%1】%2").arg(m_ip).arg(QTime::currentTime().toString("hh.mm.ss")));
    ui->tb_chat->append(content);
}

void ChatDialog::on_pb_send_clicked()
{
    qDebug()<<__func__;
    //检验是否合法
    QString content=ui->te_chat->toPlainText();
    if(content.isEmpty()||content.remove(" ").isEmpty()){
        return ;
    }

    //获取用户输入的内容，清空编辑窗口
    content=ui->te_chat->toHtml();
    ui->te_chat->clear();
    //将用户输入的内容放到浏览窗口哦
    ui->tb_chat->append(QString("【我】 %1").arg(QTime::currentTime().toString("hh:mm:ss")));
    ui->tb_chat->append(content);
    //通过信号发给对端
    Q_EMIT SIG_sendMSG(m_ip,content);
}

