#ifndef ABSTRACTCONNECTIONCONFIG_H
#define ABSTRACTCONNECTIONCONFIG_H

#include "connectionconfig.h"
#include <QHash>
#include "libPr3_global.h"

class LocobufferConnectionConfig;
class PortAdapter;
class QGridLayout;
class GridBagConstraints;
class Option;
class QCheckBox;
class QLabel;
class JTextField;
class DefaultUserMessagePreferences;
class LIBPR3SHARED_EXPORT AbstractConnectionConfig : public ConnectionConfig
{
    Q_OBJECT
public:
    explicit AbstractConnectionConfig(QObject *parent = 0);
    /*abstract*/ /*public*/ virtual void updateAdapter();
    /*public*/ bool isDirty();
    /*public*/ bool isRestartRequired();
    /*abstract*/ /*public*/ virtual QString getInfo();
    /*abstract*/ /*public*/ virtual void loadDetails(/*final*/ QWidget* details);
    /*abstract*/ /*public*/ virtual QString getManufacturer();
    /*abstract*/ /*public*/ virtual void setManufacturer(QString manufacturer);
    /*abstract*/ /*public*/ virtual QString getConnectionName();
    /*abstract*/ /*public*/ virtual bool getDisabled();
    /*abstract*/ /*public*/ virtual void setDisabled(bool disable);
    /*protected*/ /*static*/ class Option
    {

        QString optionDisplayName;
        QWidget* optionSelection;
        bool advanced;// = true;
        QLabel* label;// = NULL;
     public:
        /*public*/ Option(QString name, QWidget* optionSelection, bool advanced);
        /*protected*/ QString getDisplayName() ;
        /*public*/ QLabel* getLabel() ;
        /*public*/ QWidget* getComponent() ;
        /*protected*/ bool isAdvanced();
        /*protected*/ void setAdvanced(bool boo);
        /*public*/ QString getItem();
    };
signals:

public slots:
private:
    /*abstract*/ virtual void checkInitDone();
    /*abstract*/ virtual void showAdvancedItems();

protected:
    /*protected*/ /*final*/ DefaultUserMessagePreferences* pref;// = InstanceManager.getDefault(UserPreferencesManager.class);
     /*protected*/ int NUMOPTIONS;// = 2;
    /*protected*/ QCheckBox* showAdvanced;// = new JCheckBox("Additional Connection Settings");

    /*protected*/ QLabel* systemPrefixLabel;// = new JLabel("Connection Prefix");
    /*protected*/ QLabel* connectionNameLabel;// = new JLabel("Connection Name");
    /*protected*/ JTextField* systemPrefixField;// = new JTextField(10);
    /*protected*/ JTextField* connectionNameField;// = new JTextField(15);
    /*protected*/ QString systemPrefix;
    /*protected*/ QString connectionName;
    /*protected*/ QWidget* _details;
    /*protected*/ QHash<QString, AbstractConnectionConfig::Option*> options;// = new Hashtable<>();
    virtual /*abstract*/ /*protected*/ void setInstance();
    /*protected*/ QList<QWidget*>* additionalItems;// = new QList<QWidget*>();
    /*protected*/ QGridLayout* gbLayout;// = new QGridLayout();
    /*protected*/ GridBagConstraints* cL;// = new GridBagConstraints();
    /*protected*/ GridBagConstraints* cR;// = new GridBagConstraints();
    /*protected*/ int addStandardDetails(PortAdapter* adapter, bool incAdvanced, int i);
friend class ASCCActionListener;

};

#endif // ABSTRACTCONNECTIONCONFIG_H
