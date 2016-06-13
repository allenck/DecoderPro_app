#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QApplication>
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT MyApplication : public QApplication
{
public:
    MyApplication(int &argc, char ** argv);

private:
    bool notify(QObject *receiver_, QEvent *event_);

};

#endif // MYAPPLICATION_H
