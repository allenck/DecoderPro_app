#ifndef ABSTRACTSERIALCONNECTIONCONFIG_H
#define ABSTRACTSERIALCONNECTIONCONFIG_H

#include "abstractconnectionconfig.h"
#include "logger.h"
#include <QStringList>
#include "libPr3_global.h"

class QSignalMapper;
class PortNameMapper;
class QComboBox;
class UserPreferencesManager;
class SerialPortAdapter;
class PortAdapter;
class LIBPR3SHARED_EXPORT AbstractSerialConnectionConfig : public AbstractConnectionConfig
{
    Q_OBJECT
public:
    //explicit AbstractSerialConnectionConfig(QObject *parent = 0);
    /*public*/ AbstractSerialConnectionConfig(PortAdapter* p, QObject *parent = 0);
    /*public*/ AbstractSerialConnectionConfig(SerialPortAdapter* p, QObject *parent = 0);
    /*public*/ PortAdapter* getAdapter() ;
    Q_INVOKABLE /*public*/ AbstractSerialConnectionConfig(QObject *parent = 0);
    /*public*/ void updateAdapter();
    /*public*/ QString getInfo();
    /*public*/ void refreshPortBox();
    /*public*/ void loadDetails(/*final*/ JPanel *details);
    /*public*/ bool isPortAdvanced();
    /*public*/ bool isBaudAdvanced();
    /*public*/ QString getManufacturer();
    /*public*/ void setManufacturer(QString manufacturer);
    /*public*/ bool getDisabled();
    /*public*/ void setDisabled(bool disabled);
    /*public*/ QString getConnectionName();
    /*public*/ void dispose();
    /*public*/ virtual QString name() {return "?";}

signals:

public slots:
    void On_baudBox_currentIndexChanged(QString);
    void On_systemPrefixField_editingFinished();
    void On_connectionNameField_editingFinished();
    void On_optionBox_currentIndexChanged(QString);
    void On_portBox_currentIndexChanged(QString);

private:
    /*protected*/ bool init = false;
    void common();
    Logger* log;
    //@SuppressWarnings("UseOfObsoleteCollectionType")
    QVector<QString>* v;
    //@SuppressWarnings("UseOfObsoleteCollectionType")
    QVector<QString>*  originalList;
    QString invalidPort;//=NULL;
    QString value;
    QSignalMapper* optionsMapper;

protected:
    /*protected*/ SerialPortAdapter* adapter;// = NULL;
    /*protected*/ /*final*/ void addToActionList();
    /*protected*/ void removeFromActionList();
    /*protected*/ void checkInitDone();
    UserPreferencesManager* p;// = InstanceManager.getDefault("UserPreferencesManager");
    ///*protected*/ JComboBox<String> portBox = new JComboBox<String>();
    QComboBox* portBox;// = new QComboBox();
    /*protected*/ QLabel* portBoxLabel;
    ///*protected*/ JComboBox<String> baudBox = new JComboBox<String>();
    QComboBox* baudBox;// = new QComboBox();
    /*protected*/ QLabel* baudBoxLabel;
    /*protected*/ QStringList baudList;
    /*protected*/ int addStandardDetails(bool incAdvanced, int i);
    /*protected*/ /*synchronized*/ static void updateSerialPortNames(QString portName, QComboBox/*<String>*/* portCombo, QVector<QString>* portList);
    /*protected*/ QVector<QString>* getPortNames();
    /*protected*/ virtual QStringList getPortFriendlyNames();
    /*abstract*/ /*protected*/ virtual void getInstance() {}
    // /*abstract*/ /*protected*/ virtual void _register() =0;

protected slots:
    /*protected*/ void showAdvancedItems();

};
class PortNameMapper
{
 //  /*private*/ static QMap<QString, SerialPortFriendlyName>* serialPortNames;// = new HashMap<String, SerialPortFriendlyName>();

 public:
    static QString getPortFromName(QString s) {return s;}
};

#endif // ABSTRACTSERIALCONNECTIONCONFIG_H
