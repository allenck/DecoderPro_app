#include "jmenuitem.h"

JMenuItem::JMenuItem(QObject *parent) : JmriAbstractAction(parent)
{
}

JMenuItem::JMenuItem(QString text, QObject *parent) : JmriAbstractAction(text, parent)
{
}

/*public*/ void JMenuItem::addActionListener(ActionListener* listener)
{
 connect(listener->self(), SIGNAL(triggered()), listener->self(), SLOT(actionPerformed()));
}
