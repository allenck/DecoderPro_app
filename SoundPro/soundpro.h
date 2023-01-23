#ifndef SOUNDPRO_H
#define SOUNDPRO_H

#include "apps.h"
#include "jpanel.h"

class Logger;
class JButton;
class SoundPro : public Apps
{
    Q_OBJECT
public:
    SoundPro(JFrame *frame, QWidget *parent = nullptr);
    /*public*/ static void main(char *args[]);
    QString getClassName() {return "apps.SoundPro";}
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

class SPWindowListener : public WindowListener
{
 Q_OBJECT
 JFrame* p;
 SoundPro* sp;

public:
 SPWindowListener(JFrame* p, SoundPro* sp);
 void windowClosing(QCloseEvent *e);

};
#endif // SOUNDPRO_H
