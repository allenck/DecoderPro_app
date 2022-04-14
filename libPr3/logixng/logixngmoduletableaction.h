#ifndef LOGIXNGMODULETABLEACTION_H
#define LOGIXNGMODULETABLEACTION_H

#include "abstractlogixngtableaction.h"
#include "windowadapter.h"

class Module;
class LogixNGModuleTableAction : public AbstractLogixNGTableAction
{
  Q_OBJECT
 public:
  Q_INVOKABLE LogixNGModuleTableAction(QString s, QObject *parent= nullptr);
  Q_INVOKABLE /*public*/  LogixNGModuleTableAction(QObject *parent = nullptr);
  ~LogixNGModuleTableAction() {}
  LogixNGModuleTableAction(const LogixNGModuleTableAction&) : AbstractLogixNGTableAction(tr("LogixNGModuleTable")){}
  Q_INVOKABLE /*public*/  QString getClassDescription()override;

 private:
  static Logger* log;
  JComboBox/*<FemaleSocketManager.SocketType>*/* _femaleSocketType = new JComboBox();

 protected:
  /*protected*/ void setTitle()override;
  /*protected*/ AbstractLogixNGEditor/*<Module>*/* getEditor(BeanTableFrame/*<Module>*/* f, BeanTableDataModel/*<Module>*/* m, QString sName)override;
  /*protected*/ Manager/*<Module>*/* getManager()override;
  /*protected*/ void enableAll(bool enable)override;
  /*protected*/ void setEnabled(/*Module*/NamedBean* bean, bool enable)override;
  /*protected*/ bool isEnabled(/*Module*/NamedBean* bean)override;
  /*protected*/ /*Module*/NamedBean* createBean(QString userName)override;
  /*protected*/ /*Module*/NamedBean* createBean(QString systemName, QString userName)override;
  /*protected*/ void deleteBean(/*Module*/NamedBean* bean)override;
  /*protected*/ QString getBeanText(/*Module*/NamedBean* bean)override;
  /*protected*/ QString getAddTitleKey()override;
  /*protected*/ QString getCreateButtonHintKey()override;
  /*protected*/ QString helpTarget()override;
  /*protected*/ JPanel* makeAddFrame(QString titleId, QString startMessageId)override;
  /*protected*/ void getListenerRefsIncludingChildren(NamedBean* module, QList<QString> list)override;
  /*protected*/ bool hasChildren(/*Module*/NamedBean* module)override;


};
Q_DECLARE_METATYPE(LogixNGModuleTableAction)

class LogixNGModuleTableAction_WindowListener : public WindowAdapter
{
  LogixNGModuleTableAction* act;
 public:
  LogixNGModuleTableAction_WindowListener(LogixNGModuleTableAction* act) {this->act = act;}
  //@Override
  /*public*/  void windowClosing(QEvent* e)override{
      act->cancelAddPressed(nullptr);
  }

};

#endif // LOGIXNGMODULETABLEACTION_H
