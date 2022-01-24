#ifndef SENSORDEBOUNCEEDITACTION_H
#define SENSORDEBOUNCEEDITACTION_H
#include "beaneditaction.h"
#include "abstractaction.h"
#include "libtables_global.h"

class QCheckBox;
class LIBTABLESSHARED_EXPORT SensorDebounceEditAction : public BeanEditAction
{
 Q_OBJECT
public:
 explicit SensorDebounceEditAction(QObject *parent = 0);
 /*public*/ QString helpTarget();
 /*public*/ QString getBeanType();
 /*public*/ NamedBean* getByUserName(QString name);
 /*public*/ void setBean(NamedBean* bean);
 /*public*/ BeanItemPanel* sensorDebounce(BeanItemPanel* basic);
 /*public*/ void enabled(bool boo);

signals:

public slots:
 void on_sensorDebounceGlobalCheck_clicked();
private:
 JTextField* sensorDebounceInactiveField;//= new JTextField(5);
 JTextField* sensorDebounceActiveField;//= new JTextField(5);
 QCheckBox* sensorDebounceGlobalCheck;// = new JCheckBox();

protected:
 /*protected*/ void initPanels();

protected slots:
 /*protected*/ void saveDebounceItems(ActionEvent* e = 0);
 /*protected*/ void resetDebounceItems(ActionEvent* e = 0);
 friend class SaveItemAction;
 friend class ResetItemAction;
 friend class OBTResetItemAction1;
 friend class OBlockEditAction;

};
class SaveItemAction : public AbstractAction
{
 Q_OBJECT
 SensorDebounceEditAction* action;
public:
 SaveItemAction(SensorDebounceEditAction* action) {this->action = action;}
public slots:
 void actionPerformed(JActionEvent * = 0)
 {
  action->saveDebounceItems();
 }
};
class ResetItemAction : public AbstractAction
{
 Q_OBJECT
 SensorDebounceEditAction* action;
public:
 ResetItemAction(SensorDebounceEditAction* action) {this->action = action;}
public slots:
 void actionPerformed(JActionEvent * = 0)
 {
  action->resetDebounceItems();
 }
};

#endif // SENSORDEBOUNCEEDITACTION_H
