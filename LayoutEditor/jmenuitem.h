#ifndef JMENUITEM_H
#define JMENUITEM_H

#include "jmriabstractaction.h"
#include "actionlistener.h"

class JMenuItem : public JmriAbstractAction
{
 public:
  explicit JMenuItem(QObject *parent);
  JMenuItem(QString text, QObject *parent);
  /*public*/ void addActionListener(ActionListener* listener);
};

#endif // JMENUITEM_H
