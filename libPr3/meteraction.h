#ifndef METERACTION_H
#define METERACTION_H
#include "abstractaction.h"

class MeterAction : public AbstractAction
{
  Q_OBJECT
 public:
  MeterAction(QObject* parent);
  /*public*/ MeterAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(/*ActionEvent e*/);

};

#endif // METERACTION_H
