#ifndef TRANSFERACTIONLISTENER_H
#define TRANSFERACTIONLISTENER_H
#include "actionlistener.h"
#include "propertychangeevent.h"

class TransferActionListener : public QObject, public ActionListener
{
  Q_OBJECT
  Q_INTERFACES(ActionListener)
 public:
  TransferActionListener(QObject* parent = nullptr);

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void actionPerformed(JActionEvent* e = 0);

 private:
  /*private*/ QWidget* focusOwner = nullptr;

};

#endif // TRANSFERACTIONLISTENER_H
