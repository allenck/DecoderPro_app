#ifndef DISPATCHERPRO_H
#define DISPATCHERPRO_H

#include <QWidget>
#include "apps.h"

class JButton;
class JFrame;
class Logger;
class DispatcherPro : public Apps
{
 Q_OBJECT

public:
    DispatcherPro(JFrame* p, QWidget *parent = nullptr);
    ~DispatcherPro();
    /*public*/ static void main(char * args[]);

private:
    static Logger* log;
    /**
     * Help button on Main Screen.
     */
    /*private*/ JButton* h1;

protected:
    /*protected*/ QString logo();
    /*protected*/ QString mainWindowHelpID();
    /*protected*/ QString line1();
    /*protected*/ QString line2();
    /*protected*/ JPanel* statusPanel();
    /*protected*/ void attachHelp();

};

class DPWindowListener : public WindowListener
{
 Q_OBJECT
 JFrame* p;
 DispatcherPro* pp;

public:
 DPWindowListener(JFrame* p, DispatcherPro* pp);
 void windowClosing(QCloseEvent *e);

};

#endif // DISPATCHERPRO_H
