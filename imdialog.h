#ifndef IMDIALOG_H
#define IMDIALOG_H

#include <QDialog>
#include <QObject>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class IMDialog; }
QT_END_NAMESPACE

class IMDialog : public QDialog
{
    Q_OBJECT

public:
    IMDialog(QWidget *parent = nullptr);
    //添加好友
    void addFriend(QString ip,QString name);
    //删除好友
    void deleteFriend(QString ip);

    ~IMDialog();

signals:
    void SIG_userClicked(QString ip);

private slots:
    void on_tw_friend_cellDoubleClicked(int row, int column);

private:
    Ui::IMDialog *ui;
};
#endif // IMDIALOG_H
