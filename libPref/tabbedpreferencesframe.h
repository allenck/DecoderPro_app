#ifndef TABBEDPREFERENCESFRAME_H
#define TABBEDPREFERENCESFRAME_H
#include "jmrijframe.h"
#include "libpref_global.h"

class TabbedPreferences;
class LIBPREFSHARED_EXPORT TabbedPreferencesFrame : public JmriJFrame
{
    Q_OBJECT
public:
    explicit TabbedPreferencesFrame(QWidget *parent = 0);
    /*public*/ void gotoPreferenceItem(QString item, QString sub);
    /*public*/ QString getTitle();
    /*public*/ bool isMultipleInstances() ;
    /*public*/ void windowClosing(QCloseEvent *e);


public slots:
private:
    static bool init;// = false;
    static int lastdivider;
    /*private*/ TabbedPreferences* getTabbedPreferences();

};

#endif // TABBEDPREFERENCESFRAME_H
