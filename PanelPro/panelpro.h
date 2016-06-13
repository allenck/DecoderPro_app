#ifndef PANELPRO_H
#define PANELPRO_H
#include "apps.h"

class PanelPro : public Apps
{
    Q_OBJECT
public:
    //explicit PanelPro(QObject *parent = 0);
    PanelPro(JFrame* p, QWidget *parent = 0);
    /*public*/ static void main(char *argv[]);

signals:

public slots:
    void handleQuit();
private:
    Logger* log;
protected:
    /*protected*/ QString logo();
    /*protected*/ QString mainWindowHelpID();
    /*protected*/ QString line1() ;
    /*protected*/ QString line2() ;
    /*protected*/ QWidget* statusPanel();
//    /*protected*/ void windowClosing(QCloseEvent *);

};

#endif // PANELPRO_H
