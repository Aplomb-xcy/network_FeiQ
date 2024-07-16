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
    ~IMDialog();

private:
    Ui::IMDialog *ui;
};
#endif // IMDIALOG_H
