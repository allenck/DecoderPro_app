#ifndef LOGIXNGTABLEACTION_H
#define LOGIXNGTABLEACTION_H

#include "abstractlogixngtableaction.h"
#include "windowadapter.h"

class LogixNGTableAction : public AbstractLogixNGTableAction
{
  Q_OBJECT
 public:
  explicit /*public*/  LogixNGTableAction(QObject* parent);
  LogixNGTableAction(QString s, QObject *parent );
  /*public*/  void deleteBean(NamedBean* logixNG);

 private:
  static Logger* log;
 protected:
  /*protected*/ AbstractLogixNGEditor/*<LogixNG>*/* getEditor(BeanTableFrame/*<LogixNG>*/* f, BeanTableDataModel/*<LogixNG>*/* m, QString sName);
  /*protected*/ Manager/*<LogixNG>*/* getManager()override;
  /*protected*/ void setEnabled(NamedBean* logixNG, bool enable)override;
  /*protected*/ bool isEnabled(NamedBean* logixNG) override;
  /*protected*/ void enableAll(bool enable)override;
  /*protected*/ NamedBean* createBean(QString userName)override;
  /*protected*/ NamedBean* createBean(QString systemName, QString userName)override;
  /*protected*/ QString getBeanText(NamedBean* e)override;
  /*protected*/ QString getAddTitleKey()override;
  /*protected*/ QString getCreateButtonHintKey()override;
  /*protected*/ JPanel* makeAddFrame(QString titleId, QString startMessageId)override;
  /*protected*/ void getListenerRefsIncludingChildren(NamedBean* logixNG,QList<QString> list)override;
  /*protected*/ bool hasChildren(NamedBean* logixNG)override;

  friend class LNGTE_windowListener;
};
class LNGTE_windowListener : public WindowAdapter
{
 Q_OBJECT
 LogixNGTableAction* act;
 public:
 LNGTE_windowListener(LogixNGTableAction* act) {this->act = act;}
 /*public*/  void windowClosing(QCloseEvent*e)override {
     act->cancelAddPressed(nullptr);
 }
};
#endif // LOGIXNGTABLEACTION_H
