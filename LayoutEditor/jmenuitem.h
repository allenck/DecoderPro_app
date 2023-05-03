#ifndef JMENUITEM_H
#define JMENUITEM_H

#include "jmriabstractaction.h"

class JMenuItem : public JmriAbstractAction
{
  Q_OBJECT
 public:
  explicit JMenuItem(QObject *parent);
  JMenuItem(QString text, QObject *parent);
  /*public*/ void addActionListener(JMenuItem *listener);
  /*public*/ void setActionCommand(QString cmd);
  /*public*/ QString getActionCommand();
  /*public*/ void setEnabled(bool b) override {QAction::setEnabled(b);}

  QObject* pself() override{return (QObject*)this;}


 public slots:
  // /*public*/ void actionPerformed(JActionEvent* e = 0)override;
 private:
  QString actionCommand;

};

#endif // JMENUITEM_H
