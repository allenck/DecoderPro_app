#include "mylayouteditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyLayoutEditor w;
    w.show();
    
    return a.exec();
}


