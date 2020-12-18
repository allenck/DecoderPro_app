#ifndef CTCEDITORACTION_H
#define CTCEDITORACTION_H
#include "jmriabstractaction.h"

class CtcEditorAction : public JmriAbstractAction
{
  Q_OBJECT
 public:
  CtcEditorAction(QObject* parent);
  /*public*/ CtcEditorAction(QString s, QObject* parent);
  /*public*/ JmriPanel* makePanel()override;

 public slots:
  /*public*/ void actionPerformed(/*ActionEvent e*/);

};

#endif // CTCEDITORACTION_H
