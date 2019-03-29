#ifndef TURNOUTEDITACTION_H
#define TURNOUTEDITACTION_H
#include "beaneditaction.h"
#include "actionlistener.h"

class FlowLayout;
class TurnoutOperation;
class JTextField;
class TurnoutOperationConfig;
class QComboBox;
class JmriBeanComboBox;
class QCheckBox;
class TurnoutEditAction : public BeanEditAction
{
 Q_OBJECT
public:
 TurnoutEditAction(QModelIndex index, QObject* parent = 0);
 /*public*/ QString helpTarget();

 public slots:
  /*public*/ void actionPerformed(ActionEvent*  e = 0);
 /*public*/ QString getBeanType();
 void updateFeedbackOptions();
 /*public*/ NamedBean* getByUserName(QString name);

  private:
 JmriBeanComboBox* reporterField;
 QCheckBox* useCurrent;// = new JCheckBox();

 QCheckBox* inverted;// = new JCheckBox();
 BeanItemPanel* basicDetails();
 JmriBeanComboBox* sensorFeedBack1Field;
 JmriBeanComboBox* sensorFeedBack2Field;
 QComboBox* modeBox;
 QComboBox* automationBox;
 QString useBlockSpeed;// = "Use Block Speed";//IN18N
 TurnoutOperationConfig* config;
 BeanItemPanel* _feedback;
 QWidget* turnoutOperation;// = new QWidget();
 FlowLayout* turnoutOperationLayout;
 QString userDefinedOperation ;//= "";
 BeanItemPanel* feedback();
 QString oldModeSelection;
 TurnoutOperation* oldAutomationSelection;
 TurnoutOperation* currentOperation;
 JTextField* operationsName;// = new JTextField(10);
 void updateAutomationOptions();
 ActionListener* automationSelectionListener;
 QString bothText;// = "Both";
 QString cabOnlyText;// = "Cab only";
 QString pushbutText;// = "Pushbutton only";
 QString noneText;// = "None";

 QComboBox* lockBox;
 QComboBox* lockOperationBox;
 BeanItemPanel* lock();
 /*private*/ QVector<QString> speedListClosed;// = new QVector<QString>();
 /*private*/ QVector<QString> speedListThrown;// = new QVector<QString>();

 QComboBox* closedSpeedBox;
 QComboBox* thrownSpeedBox;
 QString defaultThrownSpeedText;
 QString defaultClosedSpeedText;
 BeanItemPanel* speed();
 QModelIndex index;
protected:
  /*protected*/ void initPanels();
protected slots:
 /*protected*/ void saveBasicItems(ActionEvent* e = 0);
 /*protected*/ void resetBasicItems(ActionEvent* e = 0);
 /*protected*/ void cancelButtonAction(ActionEvent* e = 0);
 void On_lockBox_currentIndex_changed(QString);
 friend class FeedbackSaveItemListener;
 friend class FeedbackResetItemListener;
 friend class SpeedSaveItemListener;
 friend class SpeedResetItemListener;
 friend class LockSaveItemListener;
 friend class LockResetItemListener;
 friend class AutomationSelectionListener;
};

class FeedbackSaveItemListener : public ActionListener
{
 Q_OBJECT
 TurnoutEditAction* act;
public:
 FeedbackSaveItemListener(TurnoutEditAction* act);
public slots:
 void actionPerformed(ActionEvent* = 0);
};

class FeedbackResetItemListener : public ActionListener
{
 Q_OBJECT
 TurnoutEditAction* act;
public:
 FeedbackResetItemListener(TurnoutEditAction* act);
public slots:
 void actionPerformed(ActionEvent* = 0);
};
class AutomationSelectionListener : public ActionListener
{
 Q_OBJECT
 TurnoutEditAction* act;
public:
 AutomationSelectionListener(TurnoutEditAction* act);
public slots:
 void actionPerformed(ActionEvent* = 0);
};
class LockSaveItemListener : public ActionListener
{
 Q_OBJECT
 TurnoutEditAction* act;
public:
 LockSaveItemListener(TurnoutEditAction* act);
public slots:
 void actionPerformed(ActionEvent* = 0);
};
class LockResetItemListener : public ActionListener
{
 Q_OBJECT
 TurnoutEditAction* act;
public:
 LockResetItemListener(TurnoutEditAction* act);
public slots:
 void actionPerformed(ActionEvent* = 0);
};
class SpeedSaveItemListener : public ActionListener
{
 Q_OBJECT
 TurnoutEditAction* act;
public:
 SpeedSaveItemListener(TurnoutEditAction* act);
public slots:
 void actionPerformed(ActionEvent* = 0);
};
class SpeedResetItemListener : public ActionListener
{
 Q_OBJECT
 TurnoutEditAction* act;
public:
 SpeedResetItemListener(TurnoutEditAction* act);
public slots:
 void actionPerformed(ActionEvent* = 0);
};

#endif // TURNOUTEDITACTION_H
