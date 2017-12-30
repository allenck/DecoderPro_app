#ifndef INSTALLTEST_H
#define INSTALLTEST_H
#include "apps.h"
#include "abstractaction.h"

class InstallTest : public Apps
{
    Q_OBJECT
public:
    InstallTest(JFrame* p);
    // Main entry point
    /*public*/ static void main(char *args[]);

private:

protected:
    /*protected*/ QString logo();
    /*protected*/ QString mainWindowHelpID();
    /*protected*/ QString line1();
    /*protected*/ QString line2();
    /*protected*/ QWidget* statusPanel();
};
class InstallTestQuitAction : public AbstractAction
{
 Q_OBJECT
 public:
    InstallTestQuitAction(QString s, QObject* p) : AbstractAction(s,p) {}
 public slots:
    /*public*/ void actionPerformed();
};

class ITWindowListener : public WindowListener
{
 Q_OBJECT
 JFrame* p;
 InstallTest* pp;

public:
 ITWindowListener(JFrame* p, InstallTest* pp);
 void windowClosing(QCloseEvent *e);

};

#endif // INSTALLTEST_H
