#ifndef ABSTRACTSIMULATORCONNECTIONCONFIG_H
#define ABSTRACTSIMULATORCONNECTIONCONFIG_H
#include "abstractconnectionconfig.h"
#include "logger.h"
#include <QStringList>
#include "actionlistener.h"
#include "libPr3_global.h"

class SerialPortAdapter;
class LIBPR3SHARED_EXPORT AbstractSimulatorConnectionConfig : public AbstractConnectionConfig
{
    Q_OBJECT
public:
    explicit AbstractSimulatorConnectionConfig(QObject *parent = 0);
    /*public*/ AbstractSimulatorConnectionConfig(SerialPortAdapter* p,QObject *parent = 0);
    /*public*/ PortAdapter* getAdapter() override;
    /*public*/ void updateAdapter();
    /*public*/ QString getInfo();
    /*public*/ void loadDetails(/*final*/ JPanel *details);
    /*public*/ QString getManufacturer();
    /*public*/ void setManufacturer(QString manufacturer);
    /*public*/ QString getConnectionName() ;
    /*public*/ bool getDisabled() ;
    /*public*/ void setDisabled(bool disabled);
    /*public*/ void dispose();
signals:

public slots:
    void On_systemPrefixField_editingFinished();
    void On_connectionNameField_editingFinished();
//    void On_comboBox_currentIndexChanged(QString);
private:
    Logger* log;
protected:
    /*protected*/ QStringList baudList;
    /*protected*/ SerialPortAdapter* adapter;// = NULL;

    /*protected*/ QString systemPrefix;
    /*protected*/ QString connectionName;
    /*protected*/ bool init;// = false;
    /*protected*/ void checkInitDone();
    /*abstract*/ /*protected*/ virtual void setInstance();
protected slots:
    /*protected*/ void showAdvancedItems();

friend class ASCCActionListener;
};
class ASCCActionListener : public ActionListener
{
 Q_OBJECT
 AbstractSimulatorConnectionConfig* parent;
 QString item;
public:
 ASCCActionListener(QString item, AbstractSimulatorConnectionConfig* parent);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};

#endif // ABSTRACTSIMULATORCONNECTIONCONFIG_H
