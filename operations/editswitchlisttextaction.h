#ifndef EDITSWITCHLISTTEXTACTION_H
#define EDITSWITCHLISTTEXTACTION_H

#include "abstractaction.h"
#include "editswitchlisttextframe.h"
#include <QPointer>

namespace Operations
{
 class EditSwitchListTextFrame;
 class EditSwitchListTextAction : public AbstractAction
 {
  Q_OBJECT
 public:
  EditSwitchListTextAction(QObject* parent);
  EditSwitchListTextAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0)override;
  void common();
 private:
  QPointer<EditSwitchListTextFrame> f;// = null;

 };
}
#endif // EDITSWITCHLISTTEXTACTION_H
