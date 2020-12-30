#ifndef TRANSFERACTIONLISTENER_H
#define TRANSFERACTIONLISTENER_H
#include "actionlistener.h"
#include "propertychangeevent.h"

class TransferActionListener : public ActionListener
{
  Q_OBJECT

 public:
  TransferActionListener(QObject* parent = nullptr);

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void actionPerformed(JActionEvent* e = 0);

 private:
  /*private*/ QWidget* focusOwner = nullptr;

};

#endif // TRANSFERACTIONLISTENER_H
