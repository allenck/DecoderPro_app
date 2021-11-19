#ifndef TRANSFERACTIONLISTENER_H
#define TRANSFERACTIONLISTENER_H
#include "actionlistener.h"

class PropertyChangeEvent;
class JComponent;
class TransferActionListener : public QObject, public ActionListener
{
 Q_OBJECT
  Q_INTERFACES(ActionListener)
public:
 TransferActionListener();

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);
 /*public*/ void actionPerformed(JActionEvent* e =0)override;

private:
 /*private*/ JComponent* focusOwner = nullptr;

};

#endif // TRANSFERACTIONLISTENER_H
