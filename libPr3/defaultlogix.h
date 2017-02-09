#ifndef DEFAULTLOGIX_H
#define DEFAULTLOGIX_H
#include "logix.h"
#include "libPr3_global.h"

class JmriSimplePropertyListener;
class LIBPR3SHARED_EXPORT DefaultLogix : public Logix
{
    Q_OBJECT
public:
    //explicit DefaultLogix(QObject *parent = 0);
    /*public*/ DefaultLogix(QString systemName, QString userName = "", QObject *parent = 0);
    /*public*/ int getNumConditionals();
    /*public*/ void swapConditional(int nextInOrder, int row) ;
    /*public*/ QString getConditionalByNumberOrder(int order) ;
    /*public*/ bool addConditional(QString systemName,int order);
    /*public*/ void setEnabled(bool state);
    /*public*/ bool getEnabled();
    /*public*/ QStringList* deleteConditional(QString systemName);
    /*public*/ void calculateConditionals();
    /*public*/ void activateLogix();
    /*public*/ void deActivateLogix();
    /*public*/ int getState();
    /*public*/ void setState(int state);

signals:

public slots:
private:
    /**
     *  Persistant instance variables (saved between runs)
     */
    QStringList* _conditionalSystemNames;// = new QStringList();
    QList <JmriSimplePropertyListener*>* _listeners;// = new QList<JmriSimplePropertyListener*>();

    /**
     *  Operational instance variables (not saved between runs)
     */
    /*private*/ bool mEnabled;// = true;

    /*private*/ bool _isActivated;// = false;
    /*private*/ void resetConditionals();
    /*private*/ void assembleListenerList();
    /*private*/ void startListener(JmriSimplePropertyListener* listener);
    /*private*/ void removeListener(JmriSimplePropertyListener* listener);
    Logger* log;
    /*private*/ int getPositionOfListener(int varListenerType, int varType, QString varName);

};

#endif // DEFAULTLOGIX_H
