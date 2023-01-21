#include "soundpro.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    SoundPro w;
//    w.show();
    SoundPro::main(argv);
    return a.exec();
}
