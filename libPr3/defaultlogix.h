#ifndef DEFAULTLOGIX_H
#define DEFAULTLOGIX_H
#include "logix.h"
#include "libPr3_global.h"
#include <QRegExp>

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
    /*public*/ bool addConditional(QString systemName, int order);
    /*public*/ bool addConditional(QString systemName, Conditional* conditional);
    /*public*/ void setEnabled(bool state);
    /*public*/ bool getEnabled();
    /*public*/ QStringList* deleteConditional(QString systemName);
    /*public*/ void calculateConditionals();
    /*public*/ void activateLogix();
    /*public*/ void deActivateLogix();
    /*public*/ int getState();
    /*public*/ void setState(int state);
    /*public*/ Conditional* getConditional(QString systemName) ;
    /*public*/ void setGuiNames();
  /*public*/ QList<NamedBeanUsageReport*> getUsageReport(NamedBean* bean);

signals:

public slots:
 /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throw (PropertyVetoException)*/;

private:
    /**
     *  Persistant instance variables (saved between runs)
     */
    QStringList* _conditionalSystemNames;// = new QStringList();
    QList <JmriSimplePropertyListener*>* _listeners;// = new QList<JmriSimplePropertyListener*>();
    /**
     * Maintain a list of conditional objects.  The key is the conditional system name
     * @since 4.7.4
     */
    QMap<QString, Conditional*> _conditionalMap;// = new HashMap<>();
    /**
     *  Operational instance variables (not saved between runs)
     */
    /*private*/ bool mEnabled;// = true;
    /*private*/ bool _isActivated;// = false;
    /*private*/ bool _isGuiSet = false;
    /*private*/ void resetConditionals();
    /*private*/ void assembleListenerList();
    /*private*/ void startListener(JmriSimplePropertyListener* listener);
    /*private*/ void removeListener(JmriSimplePropertyListener* listener);
    Logger* log;
    /*private*/ int getPositionOfListener(int varListenerType, int varType, QString varName);
    static QRegExp NXUUID;//("^IN:[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$");

};

#endif // DEFAULTLOGIX_H
