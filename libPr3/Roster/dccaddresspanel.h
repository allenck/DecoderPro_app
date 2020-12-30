#ifndef DCCADDRESSPANEL_H
#define DCCADDRESSPANEL_H

#include <QWidget>
#include <QLineEdit>
#include "logger.h"
#include "dccaddressvarhandler.h"
#include "libPr3_global.h"

class VariableValue;
class EnumVariableValue;
class VariableTableModel;
class PropertyChangeListener;
class PropertyChangeEvent;
class JTextField;
class JActionEvent;
class LIBPR3SHARED_EXPORT DccAddressPanel : public QWidget
{
    Q_OBJECT
public:
    //explicit DccAddressPanel(QWidget *parent = 0);
//    /*public*/ DccAddressPanel(VariableTableModel* mod, QWidget *parent = 0);
    /*public*/ DccAddressPanel(VariableTableModel* mod, QString label= tr("Active DCC Address:"), QWidget *parent = 0);

    void enterField();
    void exitField();
    void updateDccAddress();
    //void actionPerformed(ActionEvent* /*e*/);

signals:

public slots:
    void propertyChange(PropertyChangeEvent* e);
    void actionPerformed();
    void valueChanged();
    void focusGained();
    void focusLost();
private:
    JTextField* val;// = new QLineEdit(6);

    VariableValue* primaryAddr;// = NULL;
    VariableValue* extendAddr;// = NULL;
    EnumVariableValue* addMode;// = NULL;

    VariableTableModel* variableModel;// = NULL;
    QString oldContents;// = "";
    Logger* log;
};

class MyDccAddressVarHandler1 : public DccAddressVarHandler
{
 Q_OBJECT
public:
 MyDccAddressVarHandler1(VariableValue* primaryAddr, VariableValue* extendAddr, EnumVariableValue* addMode, JTextField* val)
     : DccAddressVarHandler(primaryAddr, extendAddr, addMode, val) {}
 protected:
  void doPrimary();
  void doExtended();
};
class MyDccAddressVarHandler2 : public DccAddressVarHandler
{
 Q_OBJECT
public:
 MyDccAddressVarHandler2(VariableValue* primaryAddr, VariableValue* extendAddr, EnumVariableValue* addMode, JTextField* val)
     : DccAddressVarHandler(primaryAddr, extendAddr, addMode, val) {}
protected:
 void doPrimary();
 void doExtended();
};

#endif // DCCADDRESSPANEL_H
