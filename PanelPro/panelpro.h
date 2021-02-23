#ifndef PANELPRO_H
#define PANELPRO_H
#include "apps.h"
#include "windowlistener.h"

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
    /*protected*/ QString logo() override;
    /*protected*/ QString mainWindowHelpID();
    /*protected*/ QString line1() override;
    /*protected*/ QString line2() override;
    /*protected*/ QWidget* statusPanel() override;
//    /*protected*/ void windowClosing(QCloseEvent *);

};

class PPWindowListener : public WindowListener
{
 Q_OBJECT
 JFrame* p;
 PanelPro* pp;

public:
 PPWindowListener(JFrame* p, PanelPro* pp);
 void windowClosing(QCloseEvent *e);

};

#endif // PANELPRO_H
