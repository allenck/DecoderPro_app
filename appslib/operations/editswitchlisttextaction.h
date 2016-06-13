#ifndef EDITSWITCHLISTTEXTACTION_H
#define EDITSWITCHLISTTEXTACTION_H

#include "abstractaction.h"
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
  /*public*/ void actionPerformed(ActionEvent* e = 0);
  void common();
 private:
  EditSwitchListTextFrame* f;// = null;

 };
}
#endif // EDITSWITCHLISTTEXTACTION_H
