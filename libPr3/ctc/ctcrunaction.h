#ifndef CTCRUNACTION_H
#define CTCRUNACTION_H
#include "jmriabstractaction.h"

class CtcRunAction : public JmriAbstractAction
{
  Q_OBJECT
 public:
  CtcRunAction(QWidget* parent);
  /*public*/ CtcRunAction(QString s, QWidget *parent);
  /*public*/ JmriPanel* makePanel();

 public slots:
  void actionPerformed();
};

#endif // CTCRUNACTION_H
