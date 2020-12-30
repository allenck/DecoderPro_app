#ifndef COMBOCHECKBOX_H
#define COMBOCHECKBOX_H

#include <QCheckBox>
#include <QComboBox>
#include "actionevent.h"
#include "propertychangeevent.h"
#include "actionlistener.h"
#include "propertychangelistener.h"
#include "enumvariablevalue.h"

class EnumVariableValue;
class LIBPR3SHARED_EXPORT ComboCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    //explicit ComboCheckBox(QObject *parent = 0);
    ComboCheckBox(QComboBox* box, EnumVariableValue* var);
    //void thisActionPerformed(ActionEvent* /*e*/);
    //void originalActionPerformed(ActionEvent* /*e*/);
    void originalPropertyChanged(PropertyChangeEvent* e);
    /*public*/ void dispose();
    QColor getBackground();
    void setBackground( QColor c );

signals:

public slots:
    void originalActionPerformed(JActionEvent* e = NULL);
    void thisActionPerformed(JActionEvent* e = NULL);

private:
//    /*transient*/ ActionListener* l1;
//    /*transient*/ ActionListener* l2;
    /*transient*/ PropertyChangeListener* p1;

    EnumVariableValue* _var;// = NULL;
    QComboBox* _box ;//= NULL;
    Logger* log;
};

#endif // COMBOCHECKBOX_H
