#include "imdialog.h"
#include "ui_imdialog.h"

IMDialog::IMDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::IMDialog)
{
    qDebug()<<__func__;
    ui->setupUi(this);
}

//添加好友
void IMDialog::addFriend(QString ip, QString name)
{
    qDebug()<<__func__;
    //总行数+1
    ui->tw_friend->setRowCount(ui->tw_friend->rowCount()+1);
    //设置新增单元格内容
    QTableWidgetItem* itemIp=new QTableWidgetItem(ip);
    ui->tw_friend->setItem(ui->tw_friend->rowCount()-1,0,itemIp);
    QTableWidgetItem* itemName=new QTableWidgetItem(name);
    ui->tw_friend->setItem(ui->tw_friend->rowCount()-1,1,itemName);
}

//删除好友
void IMDialog::deleteFriend(QString ip)
{

}

IMDialog::~IMDialog()
{
    delete ui;
}


void IMDialog::on_tw_friend_cellDoubleClicked(int row, int column)
{
    qDebug()<<__func__;
    //获取点击的ip地址
    QString ip=ui->tw_friend->item(row,0)->text();
    //发送给kernel
    Q_EMIT SIG_userClicked(ip);
}

