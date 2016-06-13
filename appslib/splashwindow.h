#ifndef SPLASHWINDOW_H
#define SPLASHWINDOW_H

#include "jframe.h"
#include "appslib_global.h"

class QImage;
class APPSLIBSHARED_EXPORT SplashWindow : public JFrame
{
    Q_OBJECT
public:
    //explicit SplashWindow(QWidget *parent = 0);
    /*public*/ SplashWindow(QWidget *parent = 0) ;
    /*public*/ SplashWindow(QWidget* splashMsg, QWidget *parent = 0) ;
    /*public*/ void splashWindowDisplay(QWidget* splashMsg);
    signals:

public slots:
private:
    QImage splashIm;

};

#endif // SPLASHWINDOW_H
