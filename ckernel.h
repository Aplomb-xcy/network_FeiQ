#ifndef CKERNEL_H
#define CKERNEL_H

#include "imdialog.h"
#include <QObject>
#include "UDPNetMediator.h"

class CKernel : public QObject
{
    Q_OBJECT
public:
    explicit CKernel(QObject *parent = nullptr);
    ~CKernel();
    IMDialog* m_pImdialog;
    INetMediator* m_pInetMed;
public slots:
    void slot_aboutData(char* recvData, int len, long ISend);

signals:

};

#endif // CKERNEL_H
