#include "jmenuitem.h"
#include "actionevent.h"

JMenuItem::JMenuItem(QObject *parent) : JmriAbstractAction(parent)
{
}

JMenuItem::JMenuItem(QString text, QObject *parent) : JmriAbstractAction(text, parent)
{
}

/*public*/ void JMenuItem::addActionListener(JMenuItem* listener)
{
 connect(listener, SIGNAL(triggered()), listener, SLOT(actionPerformed(JActionEvent*)));
}

/*public*/ void JMenuItem::setActionCommand(QString cmd)
{
 actionCommand = cmd;
}

/*public*/ QString JMenuItem::getActionCommand(){
 return actionCommand;
}
