#ifndef TRANSFERACTIONLISTENER_H
#define TRANSFERACTIONLISTENER_H
#include "actionlistener.h"

class PropertyChangeEvent;
class JComponent;
class TransferActionListener : public ActionListener
{
 Q_OBJECT
public:
 TransferActionListener();

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);
 /*public*/ void actionPerformed(JActionEvent* e);

private:
 /*private*/ JComponent* focusOwner = nullptr;

};

#endif // TRANSFERACTIONLISTENER_H
