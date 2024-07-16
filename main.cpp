#include "imdialog.h"
#include "ckernel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //不在主函数中调用dialog，在kernel类中调用

    //IMDialog w;
   //w.show();
    CKernel *p_Kernel=new CKernel;

    return a.exec();
}
