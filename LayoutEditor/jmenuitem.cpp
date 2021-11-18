#include "jmenuitem.h"

JMenuItem::JMenuItem(QObject *parent) : JmriAbstractAction(parent)
{
}

JMenuItem::JMenuItem(QString text, QObject *parent) : JmriAbstractAction(text, parent)
{
}

/*public*/ void JMenuItem::addActionListener(ActionListener*)
{

}
