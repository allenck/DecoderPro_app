#ifndef TABBEDPREFERENCESACTION_H
#define TABBEDPREFERENCESACTION_H

#include "jmriabstractaction.h"
#include "logger.h"
#include "tabbedpreferencesframe.h"
#include "runnable.h"
#include "libpref_global.h"

class WindowInterface;
class JmriPanel;
class LIBPREFSHARED_EXPORT TabbedPreferencesAction : public JmriAbstractAction
{
    Q_OBJECT
public:
    explicit TabbedPreferencesAction(QObject *parent = 0 );
    /*public*/ TabbedPreferencesAction(QString s, QString category, QString subCategory, QObject *parent );
    /*public*/ TabbedPreferencesAction(QString s, QString category, QObject *parent );
    /*public*/ TabbedPreferencesAction(QString s, QObject* parent) ;
    /*public*/ TabbedPreferencesAction(QString s, QIcon i, WindowInterface* wi) ;

    /*public*/ TabbedPreferencesAction(QString s, WindowInterface* wi, QString category, QString subCategory) ;
    /*public*/ TabbedPreferencesAction(QString s, QIcon i, WindowInterface* wi, QString category) ;
 ~TabbedPreferencesAction() {}
 TabbedPreferencesAction(const TabbedPreferencesAction& other) : JmriAbstractAction(other.parent()) {}
    /*public*/ JmriPanel* makePanel();
private:
private slots:
    /*private*/ void showPreferences();
    /*synchronized*/ static void setWait(bool boo);
 /*public*/ void actionPerformed(ActionEvent* /*e*/);


signals:
public slots:
    virtual /*public*/ void actionPerformed();

private:
    static TabbedPreferencesFrame* f;
    QString preferencesItem;// = null;
    QString preferenceSubCat;// = null;
    static bool inWait;// = false;
    Logger* log;
    void setTitle(); //Note required as sub-panels will set them
    QString helpTarget();
    void common();
 friend class TPRunnable;
};

class TPRunnable : public Runnable
{
 Q_OBJECT
    TabbedPreferencesAction* parent;
 public:
    TPRunnable(TabbedPreferencesAction* parent) {this->parent = parent;}
    void run();
 signals:
    void waitChange(bool bWait);
    void showPreferences();
};
Q_DECLARE_METATYPE(TabbedPreferencesAction)
#endif // TABBEDPREFERENCESACTION_H
