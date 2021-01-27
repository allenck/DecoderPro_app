#ifndef DISPATCHERACTION_H
#define DISPATCHERACTION_H
#include "abstractaction.h"

class DispatcherFrame;
class DispatcherAction : public AbstractAction
{
  Q_OBJECT
public:
 DispatcherAction(QObject* parent);
 DispatcherAction(QString s, QObject* parent);

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 DispatcherFrame* f;// = null;

};

#endif // DISPATCHERACTION_H
