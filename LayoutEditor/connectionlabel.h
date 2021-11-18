#ifndef CONNECTIONLABEL_H
#define CONNECTIONLABEL_H

#include <jlabel.h>
#include "propertychangelistener.h"

class ConnectionConfig;
class ConnectionLabel : public JLabel, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 public:
  ConnectionLabel(ConnectionConfig* connection, QWidget* parent =0);
  QObject* self() override {return (QObject*) this;}

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* evt) override;

 private:
  ConnectionConfig* connection;

 protected:
  /*protected*/ void update();

};

#endif // CONNECTIONLABEL_H
