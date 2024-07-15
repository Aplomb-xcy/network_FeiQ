#include "imdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IMDialog w;
    w.show();
    return a.exec();
}
