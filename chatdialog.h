#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QWidget>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();
    QString m_ip;

    //设置聊天窗口
    void setWindowInfo(QString ip);
    void setMessage(QString content);
signals:
    void SIG_sendMSG(QString ip,QString content);

private slots:
    void on_pb_send_clicked();

private:
    Ui::ChatDialog *ui;

};

#endif // CHATDIALOG_H
