#ifndef PANELPRO_H
#define PANELPRO_H
#include "apps.h"
#include "windowlistener.h"

class JButton;
class PanelPro : public Apps
{
    Q_OBJECT
public:
    PanelPro(JFrame* p, QWidget *parent = nullptr);
    /*public*/ static void main(char *argv[]);
    QString getClassName() {return "apps.PanelPro";}
    QObject* pself() override {return (QObject*)this;}
signals:

public slots:
    void handleQuit();
private:
    static Logger* log;
    JButton* h1;

protected:
    /*protected*/ QString logo() override;
    /*protected*/ QString mainWindowHelpID();
    /*protected*/ QString line1() override;
    /*protected*/ QString line2() override;
    /*protected*/ JPanel *statusPanel() override;
    /*protected*/ void attachHelp();

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
