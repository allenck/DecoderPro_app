#ifndef JMENUITEM_H
#define JMENUITEM_H

#include "jmriabstractaction.h"
#include "actionlistener.h"

class JMenuItem : public JmriAbstractAction
{
  Q_OBJECT
 public:
  explicit JMenuItem(QObject *parent);
  JMenuItem(QString text, QObject *parent);
  /*public*/ void addActionListener(JMenuItem *listener);
 public slots:
  // /*public*/ void actionPerformed(JActionEvent* e = 0)override;
};

#endif // JMENUITEM_H
