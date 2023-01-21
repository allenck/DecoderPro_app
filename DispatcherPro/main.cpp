#include "dispatcherpro.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    DispatcherPro w;
//    w.show();
    DispatcherPro::main(argv);
    return a.exec();
}
