#ifndef DCCADDRESSVARHANDLER_H
#define DCCADDRESSVARHANDLER_H

#include <QObject>
#include "logger.h"

class MyDccAddressVarHandler;
class DccAddressPanel;
class JTextField;
class VariableValue;
class EnumVariableValue;
class DccAddressVarHandler : public QObject
{
    Q_OBJECT
public:
    //explicit DccAddressVarHandler(QObject *parent = 0);
    /*public*/ DccAddressVarHandler(VariableValue* primaryAddr, VariableValue* extendAddr, EnumVariableValue* addMode, JTextField* val, QObject *parent = 0);

signals:

public slots:
    void exec();

private:
    VariableValue* primaryAddr;
    VariableValue* extendAddr;
    EnumVariableValue* addMode;
    JTextField* val;
    Logger* log;
protected:
    /*protected*/virtual  void doPrimary();
    /*protected*/virtual  void doExtended();
 friend class MyDccAddressVarHandler1;
 friend class MyDccAddressVarHandler2;
 friend class MyDccAddressVarHandler;
 friend class DccAddressPanel;
 friend class PPD3DccAddressVarHandler;
};

#endif // DCCADDRESSVARHANDLER_H
