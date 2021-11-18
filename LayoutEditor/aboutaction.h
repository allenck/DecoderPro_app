#ifndef ABOUTACTION_H
#define ABOUTACTION_H

#include "jmriabstractaction.h"

class AboutAction : public JmriAbstractAction
{
  Q_OBJECT
 public:
  /*public*/ AboutAction(QString s, WindowInterface* wi);
  /*public*/ AboutAction(QString s, QIcon i, WindowInterface* wi);
  /*public*/ AboutAction(QObject* parent) ;
  /*public*/ JmriPanel* makePanel() override;
 public slots:
  /*public*/ void actionPerformed(JActionEvent* e =0)override;

};

#endif // ABOUTACTION_H
